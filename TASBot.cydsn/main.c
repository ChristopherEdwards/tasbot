/* ========================================
 * TAS NES/NES Replay Device for the PSoC5
 * ========================================
 */

#include <main.h>
#define USBUART_BUFFER_SIZE (64u)

volatile int sent = 0;
volatile int playing = 0;
volatile uint16 data[6] = {0, 0, 0, 0, 0, 0};
volatile uint16 input[6][INPUT_BUF_SIZE];
volatile int input_ptr = 0;
volatile int buf_ptr = 0;
volatile int count = 0;
volatile int ready = 0;
volatile int timer_ready = 0;
volatile int use_timer = 0;
volatile int ports = 0;
volatile int lines = 0;
volatile int databits = 0;
volatile int request = 0;
volatile int disable_timer = 0;
volatile int bytes = 0;
volatile int window_off = -1;
volatile int latches = 0;
volatile int async = 0;
volatile int autolatch = 0;
volatile int autofilled = 0;
volatile int autobits = 16;

int main()
{
    uint8 buffer[USBUART_BUFFER_SIZE];
    uint8 cmd;
    uint16 tmp = 0;
    int i = 0, j = 0, k = 0, p = 0, d = 0, blocksize = 0;
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    USBUART_Start(0, USBUART_5V_OPERATION);
    

    /* Start registers and timers */
    ConsolePort_1_RegD0_Start();
    ConsolePort_1_RegD1_Start();
    ConsolePort_1_WinTimer_Start();
    ConsolePort_1_ClockTimer_Start();

    ConsolePort_2_RegD0_Start();
    ConsolePort_2_RegD1_Start();
    ConsolePort_2_ClockTimer_Start();    

    input_ptr = 0;
    buf_ptr = 0;
    playing = 0;
    count = 0;
    latches = 0;
    async = 0;
    blocksize = 0;
    autofilled = 0;
    autolatch = 0;
    
    P1_IRQ_Stop();
    P1_TimerIRQ_Stop();
    
    /* reset autolatcher */
    ClockCounter_Stop();
    ClockCounter_IRQ_Stop();
    ClockCounter_WritePeriod(16);
    ClockCountSel_Write(0);
    
    /* Reset timers to default */
    ConsolePort_1_ClockTimer_WritePeriod(2);
    ConsolePort_2_ClockTimer_WritePeriod(2);                        
    ConsolePort_1_WinTimer_WritePeriod(2500);
    ConsolePort_2_WinTimer_WritePeriod(2500);
    
    disable_timer = 0;
    use_timer = 0;
    timer_ready = 0;
    window_off = -1;

    for(i = 0; i < INPUT_BUF_SIZE; i++)
    {
        for(j = 0; j < 6; j++)
        {
            input[j][i] = 0;
        }
    }
    
    ConsolePort_1_RegD0_WriteRegValue(0xFFFF);
    ConsolePort_1_RegD1_WriteRegValue(0xFFFF);
    ConsolePort_2_RegD0_WriteRegValue(0xFFFF);
    ConsolePort_2_RegD1_WriteRegValue(0xFFFF);
    
    for(;;)    
    {      

        if(playing && request == 0)
        {
            i = (INPUT_BUF_SIZE - 1) - ((buf_ptr - input_ptr)&(INPUT_BUF_SIZE - 1));
			if(i != (INPUT_BUF_SIZE - 1) && i > 65)
			{
                if (0u != USBUART_GetConfiguration())
                {
                    while (0u == USBUART_CDCIsReady()) { }
                    USBUART_PutChar(0xF);
                    request = 1;
                }
            }
        }           
        
        if (0u != USBUART_IsConfigurationChanged())
        {
            if (0u != USBUART_GetConfiguration())
            {
                USBUART_CDC_Init();
            }
        }        
        
        if (0u != USBUART_GetConfiguration())
        {
            if (0u != USBUART_DataIsReady())
            {
                /* Read received data and re-enable OUT endpoint. */
                bytes = USBUART_GetAll(buffer);
                cmd = buffer[0];
                
                switch(cmd)
                {
                    case 0:
                    {
                        input_ptr = 0;
                        buf_ptr = 0;
                        playing = 0;
                        count = 0;
                        latches = 0;
                        async = 0;
                        blocksize = 0;
                        autofilled = 0;
                        autolatch = 0;
                        
                        P1_IRQ_Stop();
                        P1_TimerIRQ_Stop();

                        /* reset autolatcher */
                        ClockCounter_Stop();
                        ClockCounter_IRQ_Stop();
                        ClockCounter_WritePeriod(16);
                        ClockCountSel_Write(0);
                        
                        /* Reset timers to default */
                        ConsolePort_1_ClockTimer_WritePeriod(2);
                        ConsolePort_2_ClockTimer_WritePeriod(2);                        
                        ConsolePort_1_WinTimer_WritePeriod(2500);
                        ConsolePort_2_WinTimer_WritePeriod(2500);
                        
                        disable_timer = 0;
                        use_timer = 0;
                        timer_ready= 0;
                        window_off = -1;

                        for(i = 0; i < INPUT_BUF_SIZE; i++)
                        {
                            for(j = 0; j < 6; j++)
                            {
                                input[j][i] = 0;
                            }
                        }
                        
                        ConsolePort_1_RegD0_WriteRegValue(0xFFFF);
                        ConsolePort_1_RegD1_WriteRegValue(0xFFFF);
                        ConsolePort_2_RegD0_WriteRegValue(0xFFFF);
                        ConsolePort_2_RegD1_WriteRegValue(0xFFFF);
                        
                        break;
                    }
                    case 1:
                    {
                        databits = buffer[1];
                        ports = buffer[2];
                        lines = buffer[3];
                        use_timer = buffer[4];
                        
                        buf_ptr = 0;
                        playing = 0;
                        sent = 0;
                        count = 0;
                        latches = 0;
                        autofilled = 0;
                        
                        blocksize = ports * databits * lines;
                        
                        for(k = 0; k < 4 * blocksize; k++)
                        {
                            while (0u == USBUART_CDCIsReady()) { }
                            USBUART_PutChar(0x0F);
                            
                            while(USBUART_DataIsReady() == 0) { }
                            bytes = USBUART_GetAll(buffer);
                            
                            for(j = 1; j < bytes; j+= blocksize)
                            {
                                for(p = 0; p < ports; p++)
                                {
                                    for(d = 0; d < lines; d++)
                                    {
                                        
                                        tmp = 0;
                                        if(databits > 1)
                                        {
                                            for(i = 0; i < databits; i++)
                                            {
                                                tmp = (tmp<<8) + buffer[j+(p*(databits*lines))+(d*databits)+i];
                                            }
                                        } 
                                        else 
                                        {
                                            tmp = buffer[j+(p*(databits*lines))+(d*databits)] << 8;
                                        }
                                        
                                        input[(p*3) + d][buf_ptr] = tmp;
                                    }
                                }
            					buf_ptr = (buf_ptr+1) % INPUT_BUF_SIZE;
                            }
                        }
                        
                        input_ptr = 0;
                        
                        data[0] = input[0][0];
                        data[1] = input[1][0];
                        data[2] = input[2][0];
                        data[3] = input[3][0];
                        data[4] = input[4][0];
                        data[5] = input[5][0];

                        ConsolePort_1_RegD0_WriteRegValue(data[0]);
                        ConsolePort_1_RegD1_WriteRegValue(data[1]);
                        ConsolePort_2_RegD0_WriteRegValue(data[3]);
                        ConsolePort_2_RegD1_WriteRegValue(data[4]);
                        
                        timer_ready = 1;
                        ready = 1;
                        playing = 1;
                        request = 0;

                        P1_IRQ_Start();
                        P1_TimerIRQ_Start();

                        if(autolatch)
                        {
                            ClockCounter_Start();
                            ClockCounter_IRQ_Start();
                        }

                        break;
                    }
                    case 0xF:
                    {
                        /* synchronous send to both ports with interleaved data */                        
                        for(j = 1; j < bytes; j+= blocksize)
                        {
                            for(p = 0; p < ports; p++)
                            {
                                for(d = 0; d < lines; d++)
                                {
                                    tmp = 0;
                                    if(databits > 1)
                                    {
                                        for(i = 0; i < databits; i++)
                                        {
                                            tmp = (tmp<<8) + buffer[j+(p*(databits*lines))+(d*databits)+i];
                                        }
                                    } 
                                    else 
                                    {
                                        tmp = buffer[j+(p*(databits*lines))+(d*databits)] << 8;
                                    }
                                    input[(p*3) + d][buf_ptr] = tmp;
                                    
                                }
                            }
        					buf_ptr = (buf_ptr+1)%INPUT_BUF_SIZE;
                        }
                        request = 0;
                        break;
                    }
                    case 0xA0:
                    {                        
                        ConsolePort_1_WinTimer_WritePeriod((buffer[1]<<8) + (buffer[2]&0xFF));
                        break;
                    }
                    case 0xA1:
                    {
                        window_off = (buffer[1]<<8) + (buffer[2]&0xFF);
                        break;
                    }
                    case 0xA2:
                    {
                        disable_timer = 1;
                        break;
                    }
                    case 0xA3:
                    {
                        disable_timer = 0;
                        use_timer = 1;
                        timer_ready= 1;
                        break;
                    }
                    case 0xA4:
                    {
                        ConsolePort_1_ClockTimer_WritePeriod(buffer[1]);
                        break;
                    }                    
                    case 0xB4:
                    {
                        ConsolePort_2_ClockTimer_WritePeriod(buffer[1]);
                        break;
                    }      
                    case 0xC0:
                    {
                        autolatch = buffer[1];
                        ClockCountSel_Write(buffer[2]);
                        break;
                    }
                    case 0xC1:
                    {
                        autobits = buffer[1];
                        ClockCounter_WritePeriod(buffer[1]);
                        break;
                    }
                    case 0xFF:
                    {
                        while (0u == USBUART_CDCIsReady()) { }
                        USBUART_PutChar(0xFF);
                        break;
                    }
                }
            }
        }
    }
}

/* [] END OF FILE */
