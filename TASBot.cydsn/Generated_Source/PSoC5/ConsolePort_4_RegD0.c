/*******************************************************************************
* File Name: ConsolePort_4_RegD0.c
* Version 2.30
*
* Description:
*  This file provides the API source code for the Shift Register component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ConsolePort_4_RegD0.h"

uint8 ConsolePort_4_RegD0_initVar = 0u;


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_Start
********************************************************************************
*
* Summary:
*  Starts the Shift Register.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  ConsolePort_4_RegD0_initVar - used to check initial configuration, modified on
*  first function call.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void ConsolePort_4_RegD0_Start(void) 
{
    if(0u == ConsolePort_4_RegD0_initVar)
    {
        ConsolePort_4_RegD0_Init();
        ConsolePort_4_RegD0_initVar = 1u; /* Component initialized */
    }

    ConsolePort_4_RegD0_Enable();
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_Enable
********************************************************************************
*
* Summary:
*  Enables the Shift Register.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void ConsolePort_4_RegD0_Enable(void) 
{
    /* Changing address in Datapath Control Store
       from NOP to component state machine commands space */
    ConsolePort_4_RegD0_SR_CONTROL |= ConsolePort_4_RegD0_CLK_EN;

    ConsolePort_4_RegD0_EnableInt();
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_Init
********************************************************************************
*
* Summary:
*  Initializes Tx and/or Rx interrupt sources with initial values.
*
* Parameters:
*  void.
*
* Return:
*  void.
*
*******************************************************************************/
void ConsolePort_4_RegD0_Init(void) 
{
    ConsolePort_4_RegD0_SetIntMode(ConsolePort_4_RegD0_INT_SRC);
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_Stop
********************************************************************************
*
* Summary:
*  Disables the Shift Register
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_Stop(void) 
{
    /*changing Datapath Control Store address to NOP space*/
    ConsolePort_4_RegD0_SR_CONTROL &= ((uint8) ~ConsolePort_4_RegD0_CLK_EN);
    ConsolePort_4_RegD0_DisableInt();
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_EnableInt
********************************************************************************
*
* Summary:
*  Enables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_EnableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    ConsolePort_4_RegD0_SR_AUX_CONTROL |= ConsolePort_4_RegD0_INTERRUPTS_ENABLE;
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_DisableInt
********************************************************************************
*
* Summary:
*  Disables the Shift Register interrupt.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_DisableInt(void) 
{
    uint8 interruptState;

    interruptState = CyEnterCriticalSection();
    ConsolePort_4_RegD0_SR_AUX_CONTROL &= ((uint8) ~ConsolePort_4_RegD0_INTERRUPTS_ENABLE);
    CyExitCriticalSection(interruptState);
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_GetFIFOStatus
********************************************************************************
*
* Summary:
*  Returns current status of input or output FIFO.
*
* Parameters:
*  fifoId.
*
* Return:
*  FIFO status.
*
*******************************************************************************/
uint8 ConsolePort_4_RegD0_GetFIFOStatus(uint8 fifoId) 
{
    uint8 result;

    result = ConsolePort_4_RegD0_RET_FIFO_NOT_DEFINED;

    #if(0u != ConsolePort_4_RegD0_USE_INPUT_FIFO)
        if(ConsolePort_4_RegD0_IN_FIFO == fifoId)
        {
            switch(ConsolePort_4_RegD0_GET_IN_FIFO_STS)
            {
                case ConsolePort_4_RegD0_IN_FIFO_FULL :
                    result = ConsolePort_4_RegD0_RET_FIFO_FULL;
                    break;

                case ConsolePort_4_RegD0_IN_FIFO_EMPTY :
                    result = ConsolePort_4_RegD0_RET_FIFO_EMPTY;
                    break;

                case ConsolePort_4_RegD0_IN_FIFO_PARTIAL:
                    result = ConsolePort_4_RegD0_RET_FIFO_PARTIAL;
                    break;
                    
                default:
                    /* Initial result value, while 
                       IN_FIFO_EMPTY case is false 
                     */
                    result = ConsolePort_4_RegD0_RET_FIFO_EMPTY;
                    break;
            }   
        }
    #endif /* (0u != ConsolePort_4_RegD0_USE_INPUT_FIFO) */

    if(ConsolePort_4_RegD0_OUT_FIFO == fifoId)
    {
        switch(ConsolePort_4_RegD0_GET_OUT_FIFO_STS)
        {
            case ConsolePort_4_RegD0_OUT_FIFO_FULL :
                result = ConsolePort_4_RegD0_RET_FIFO_FULL;
                break;

            case ConsolePort_4_RegD0_OUT_FIFO_EMPTY :
                result = ConsolePort_4_RegD0_RET_FIFO_EMPTY;
                break;

            case ConsolePort_4_RegD0_OUT_FIFO_PARTIAL :
                result = ConsolePort_4_RegD0_RET_FIFO_PARTIAL;
                break;

            default:
                /* Initial result value, while 
                   OUT_FIFO_FULL case is false 
                 */
                result = ConsolePort_4_RegD0_RET_FIFO_FULL;
                break;
        }
    }

    return(result);
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_SetIntMode
********************************************************************************
*
* Summary:
*  Sets the Interrupt Source for the Shift Register interrupt. Multiple
*  sources may be ORed together
*
* Parameters:
*  interruptSource: Byte containing the constant for the selected interrupt
*  source/s.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_SetIntMode(uint8 interruptSource) 
{
    ConsolePort_4_RegD0_SR_STATUS_MASK &= ((uint8) ~ConsolePort_4_RegD0_INTS_EN_MASK);          /* Clear existing int */
    ConsolePort_4_RegD0_SR_STATUS_MASK |= (interruptSource & ConsolePort_4_RegD0_INTS_EN_MASK); /* Set int */
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_GetIntStatus
********************************************************************************
*
* Summary:
*  Gets the Shift Register Interrupt status.
*
* Parameters:
*  None.
*
* Return:
*  Byte containing the constant for the selected interrupt source/s.
*
*******************************************************************************/
uint8 ConsolePort_4_RegD0_GetIntStatus(void) 
{
    return(ConsolePort_4_RegD0_SR_STATUS & ConsolePort_4_RegD0_INTS_EN_MASK);
}


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_WriteRegValue
********************************************************************************
*
* Summary:
*  Send state directly to shift register
*
* Parameters:
*  shiftData: containing shift register state.
*
* Return:
*  None.
*
*******************************************************************************/
void ConsolePort_4_RegD0_WriteRegValue(uint16 shiftData)
                                                                     
{
    CY_SET_REG16(ConsolePort_4_RegD0_SHIFT_REG_LSB_PTR, shiftData);
}


#if(0u != ConsolePort_4_RegD0_USE_INPUT_FIFO)
    /*******************************************************************************
    * Function Name: ConsolePort_4_RegD0_WriteData
    ********************************************************************************
    *
    * Summary:
    *  Send state to FIFO for later transfer to shift register based on the Load
    *  input
    *
    * Parameters:
    *  shiftData: containing shift register state.
    *
    * Return:
    *  Indicates: successful execution of function
    *  when FIFO is empty; and error when FIFO is full.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    cystatus ConsolePort_4_RegD0_WriteData(uint16 shiftData)
                                                                         
    {
        cystatus result;

        result = CYRET_INVALID_STATE;

        /* Writes data into the input FIFO if it is not FULL */
        if(ConsolePort_4_RegD0_RET_FIFO_FULL != (ConsolePort_4_RegD0_GetFIFOStatus(ConsolePort_4_RegD0_IN_FIFO)))
        {
            CY_SET_REG16(ConsolePort_4_RegD0_IN_FIFO_VAL_LSB_PTR, shiftData);
            result = CYRET_SUCCESS;
        }

        return(result);
    }
#endif /* (0u != ConsolePort_4_RegD0_USE_INPUT_FIFO) */


#if(0u != ConsolePort_4_RegD0_USE_OUTPUT_FIFO)
    /*******************************************************************************
    * Function Name: ConsolePort_4_RegD0_ReadData
    ********************************************************************************
    *
    * Summary:
    *  Returns state in FIFO due to Store input.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Shift Register state
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 ConsolePort_4_RegD0_ReadData(void) 
    {
        return(CY_GET_REG16(ConsolePort_4_RegD0_OUT_FIFO_VAL_LSB_PTR));
    }
#endif /* (0u != ConsolePort_4_RegD0_USE_OUTPUT_FIFO) */


/*******************************************************************************
* Function Name: ConsolePort_4_RegD0_ReadRegValue
********************************************************************************
*
* Summary:
*  Directly returns current state in shift register, not data in FIFO due
*  to Store input.
*
* Parameters:
*  None.
*
* Return:
*  Shift Register state. Clears output FIFO.
*
* Reentrant:
*  No.
*
*******************************************************************************/
uint16 ConsolePort_4_RegD0_ReadRegValue(void) 
{
    uint16 result;

    /* Clear FIFO before software capture */
    while(ConsolePort_4_RegD0_RET_FIFO_EMPTY != ConsolePort_4_RegD0_GetFIFOStatus(ConsolePort_4_RegD0_OUT_FIFO))
    {
        (void) CY_GET_REG16(ConsolePort_4_RegD0_OUT_FIFO_VAL_LSB_PTR);
    }

    /* Read of 8 bits from A1 causes capture to output FIFO */
    (void) CY_GET_REG8(ConsolePort_4_RegD0_SHIFT_REG_CAPTURE_PTR);

    /* Read output FIFO */
    result  = CY_GET_REG16(ConsolePort_4_RegD0_OUT_FIFO_VAL_LSB_PTR);
    
    #if(0u != (ConsolePort_4_RegD0_SR_SIZE % 8u))
        result &= ((uint16) ConsolePort_4_RegD0_SR_MASK);
    #endif /* (0u != (ConsolePort_4_RegD0_SR_SIZE % 8u)) */
    
    return(result);
}


/* [] END OF FILE */
