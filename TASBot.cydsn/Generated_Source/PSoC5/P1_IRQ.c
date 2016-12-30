/*******************************************************************************
* File Name: P1_IRQ.c  
* Version 1.70
*
*  Description:
*   API for controlling the state of an interrupt.
*
*
*  Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/


#include <cydevice_trm.h>
#include <CyLib.h>
#include <P1_IRQ.h>
#include "cyapicallbacks.h"

#if !defined(P1_IRQ__REMOVED) /* Check for removal by optimization */

/*******************************************************************************
*  Place your includes, defines and code here 
********************************************************************************/
/* `#START P1_IRQ_intc` */
#include <P1.h>
#include <main.h>
/* `#END` */

#ifndef CYINT_IRQ_BASE
#define CYINT_IRQ_BASE      16
#endif /* CYINT_IRQ_BASE */
#ifndef CYINT_VECT_TABLE
#define CYINT_VECT_TABLE    ((cyisraddress **) CYREG_NVIC_VECT_OFFSET)
#endif /* CYINT_VECT_TABLE */

/* Declared in startup, used to set unused interrupts to. */
CY_ISR_PROTO(IntDefaultHandler);


/*******************************************************************************
* Function Name: P1_IRQ_Start
********************************************************************************
*
* Summary:
*  Set up the interrupt and enable it. This function disables the interrupt, 
*  sets the default interrupt vector, sets the priority from the value in the
*  Design Wide Resources Interrupt Editor, then enables the interrupt to the 
*  interrupt controller.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_Start(void)
{
    /* For all we know the interrupt is active. */
    P1_IRQ_Disable();

    /* Set the ISR to point to the P1_IRQ Interrupt. */
    P1_IRQ_SetVector(&P1_IRQ_Interrupt);

    /* Set the priority. */
    P1_IRQ_SetPriority((uint8)P1_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    P1_IRQ_Enable();
}


/*******************************************************************************
* Function Name: P1_IRQ_StartEx
********************************************************************************
*
* Summary:
*  Sets up the interrupt and enables it. This function disables the interrupt,
*  sets the interrupt vector based on the address passed in, sets the priority 
*  from the value in the Design Wide Resources Interrupt Editor, then enables 
*  the interrupt to the interrupt controller.
*  
*  When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*  used to provide consistent definition across compilers:
*  
*  Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*   Function prototype example:
*   CY_ISR_PROTO(MyISR);
*
* Parameters:  
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_StartEx(cyisraddress address)
{
    /* For all we know the interrupt is active. */
    P1_IRQ_Disable();

    /* Set the ISR to point to the P1_IRQ Interrupt. */
    P1_IRQ_SetVector(address);

    /* Set the priority. */
    P1_IRQ_SetPriority((uint8)P1_IRQ_INTC_PRIOR_NUMBER);

    /* Enable it. */
    P1_IRQ_Enable();
}


/*******************************************************************************
* Function Name: P1_IRQ_Stop
********************************************************************************
*
* Summary:
*   Disables and removes the interrupt.
*
* Parameters:  
*   None
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_Stop(void)
{
    /* Disable this interrupt. */
    P1_IRQ_Disable();

    /* Set the ISR to point to the passive one. */
    P1_IRQ_SetVector(&IntDefaultHandler);
}


/*******************************************************************************
* Function Name: P1_IRQ_Interrupt
********************************************************************************
*
* Summary:
*   The default Interrupt Service Routine for P1_IRQ.
*
*   Add custom code between the coments to keep the next version of this file
*   from over writting your code.
*
* Parameters:  
*
* Return:
*   None
*
*******************************************************************************/
CY_ISR(P1_IRQ_Interrupt)
{
    #ifdef P1_IRQ_INTERRUPT_INTERRUPT_CALLBACK
        P1_IRQ_Interrupt_InterruptCallback();
    #endif /* P1_IRQ_INTERRUPT_INTERRUPT_CALLBACK */ 

    /*  Place your Interrupt code here. */
    /* `#START P1_IRQ_Interrupt` */

    if(autofilled == 0)
    {
        ConsolePort_1_RegD0_WriteRegValue(data[0]);
        ConsolePort_1_RegD1_WriteRegValue(data[1]);
        ConsolePort_2_RegD0_WriteRegValue(data[3]);
        ConsolePort_2_RegD1_WriteRegValue(data[4]);
      
        if(playing)
        {
            Vis_L_Write(data[0] & 0xFF);
            Vis_H_Write(data[0] >> 8);

            Vis_L_1_Write(data[1] & 0xFF);
            Vis_H_1_Write(data[1] >> 8);

            Vis_L_2_Write(data[3] & 0xFF);
            Vis_H_2_Write(data[3] >> 8);

            Vis_L_3_Write(data[4] & 0xFF);
            Vis_H_3_Write(data[4] >> 8);

            if(!use_timer)
            {
                input_ptr = (input_ptr+1)%INPUT_BUF_SIZE;
                data[0] = input[0][input_ptr]; 
                data[1] = input[1][input_ptr]; 
                data[2] = input[2][input_ptr]; 

                if(!async)
                {
                    data[3] = input[3][input_ptr]; 
                    data[4] = input[4][input_ptr]; 
                    data[5] = input[5][input_ptr]; 
                }
                
                latches++;
                sent = 1;
            }
            
        }
    } else {
        autofilled = 0;
    }
    
    if(autolatch)
    {
        ClockCounter_WriteCounter(autobits);
    }
    /* `#END` */
}


/*******************************************************************************
* Function Name: P1_IRQ_SetVector
********************************************************************************
*
* Summary:
*   Change the ISR vector for the Interrupt. Note calling P1_IRQ_Start
*   will override any effect this method would have had. To set the vector 
*   before the component has been started use P1_IRQ_StartEx instead.
* 
*   When defining ISR functions, the CY_ISR and CY_ISR_PROTO macros should be 
*   used to provide consistent definition across compilers:
*
*   Function definition example:
*   CY_ISR(MyISR)
*   {
*   }
*
*   Function prototype example:
*     CY_ISR_PROTO(MyISR);
*
* Parameters:
*   address: Address of the ISR to set in the interrupt vector table.
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_SetVector(cyisraddress address)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    ramVectorTable[CYINT_IRQ_BASE + (uint32)P1_IRQ__INTC_NUMBER] = address;
}


/*******************************************************************************
* Function Name: P1_IRQ_GetVector
********************************************************************************
*
* Summary:
*   Gets the "address" of the current ISR vector for the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Address of the ISR in the interrupt vector table.
*
*******************************************************************************/
cyisraddress P1_IRQ_GetVector(void)
{
    cyisraddress * ramVectorTable;

    ramVectorTable = (cyisraddress *) *CYINT_VECT_TABLE;

    return ramVectorTable[CYINT_IRQ_BASE + (uint32)P1_IRQ__INTC_NUMBER];
}


/*******************************************************************************
* Function Name: P1_IRQ_SetPriority
********************************************************************************
*
* Summary:
*   Sets the Priority of the Interrupt. 
*
*   Note calling P1_IRQ_Start or P1_IRQ_StartEx will 
*   override any effect this API would have had. This API should only be called
*   after P1_IRQ_Start or P1_IRQ_StartEx has been called. 
*   To set the initial priority for the component, use the Design-Wide Resources
*   Interrupt Editor.
*
*   Note This API has no effect on Non-maskable interrupt NMI).
*
* Parameters:
*   priority: Priority of the interrupt, 0 being the highest priority
*             PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*             PSoC 4: Priority is from 0 to 3.
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_SetPriority(uint8 priority)
{
    *P1_IRQ_INTC_PRIOR = priority << 5;
}


/*******************************************************************************
* Function Name: P1_IRQ_GetPriority
********************************************************************************
*
* Summary:
*   Gets the Priority of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   Priority of the interrupt, 0 being the highest priority
*    PSoC 3 and PSoC 5LP: Priority is from 0 to 7.
*    PSoC 4: Priority is from 0 to 3.
*
*******************************************************************************/
uint8 P1_IRQ_GetPriority(void)
{
    uint8 priority;


    priority = *P1_IRQ_INTC_PRIOR >> 5;

    return priority;
}


/*******************************************************************************
* Function Name: P1_IRQ_Enable
********************************************************************************
*
* Summary:
*   Enables the interrupt to the interrupt controller. Do not call this function
*   unless ISR_Start() has been called or the functionality of the ISR_Start() 
*   function, which sets the vector and the priority, has been called.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_Enable(void)
{
    /* Enable the general interrupt. */
    *P1_IRQ_INTC_SET_EN = P1_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: P1_IRQ_GetState
********************************************************************************
*
* Summary:
*   Gets the state (enabled, disabled) of the Interrupt.
*
* Parameters:
*   None
*
* Return:
*   1 if enabled, 0 if disabled.
*
*******************************************************************************/
uint8 P1_IRQ_GetState(void)
{
    /* Get the state of the general interrupt. */
    return ((*P1_IRQ_INTC_SET_EN & (uint32)P1_IRQ__INTC_MASK) != 0u) ? 1u:0u;
}


/*******************************************************************************
* Function Name: P1_IRQ_Disable
********************************************************************************
*
* Summary:
*   Disables the Interrupt in the interrupt controller.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_Disable(void)
{
    /* Disable the general interrupt. */
    *P1_IRQ_INTC_CLR_EN = P1_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: P1_IRQ_SetPending
********************************************************************************
*
* Summary:
*   Causes the Interrupt to enter the pending state, a software method of
*   generating the interrupt.
*
* Parameters:
*   None
*
* Return:
*   None
*
* Side Effects:
*   If interrupts are enabled and the interrupt is set up properly, the ISR is
*   entered (depending on the priority of this interrupt and other pending 
*   interrupts).
*
*******************************************************************************/
void P1_IRQ_SetPending(void)
{
    *P1_IRQ_INTC_SET_PD = P1_IRQ__INTC_MASK;
}


/*******************************************************************************
* Function Name: P1_IRQ_ClearPending
********************************************************************************
*
* Summary:
*   Clears a pending interrupt in the interrupt controller.
*
*   Note Some interrupt sources are clear-on-read and require the block 
*   interrupt/status register to be read/cleared with the appropriate block API 
*   (GPIO, UART, and so on). Otherwise the ISR will continue to remain in 
*   pending state even though the interrupt itself is cleared using this API.
*
* Parameters:
*   None
*
* Return:
*   None
*
*******************************************************************************/
void P1_IRQ_ClearPending(void)
{
    *P1_IRQ_INTC_CLR_PD = P1_IRQ__INTC_MASK;
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
