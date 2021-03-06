/*******************************************************************************
* File Name: ConsolePort_2_ClockTimer_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "ConsolePort_2_ClockTimer.h"

static ConsolePort_2_ClockTimer_backupStruct ConsolePort_2_ClockTimer_backup;


/*******************************************************************************
* Function Name: ConsolePort_2_ClockTimer_SaveConfig
********************************************************************************
*
* Summary:
*     Save the current user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  ConsolePort_2_ClockTimer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void ConsolePort_2_ClockTimer_SaveConfig(void) 
{
    #if (!ConsolePort_2_ClockTimer_UsingFixedFunction)
        ConsolePort_2_ClockTimer_backup.TimerUdb = ConsolePort_2_ClockTimer_ReadCounter();
        ConsolePort_2_ClockTimer_backup.InterruptMaskValue = ConsolePort_2_ClockTimer_STATUS_MASK;
        #if (ConsolePort_2_ClockTimer_UsingHWCaptureCounter)
            ConsolePort_2_ClockTimer_backup.TimerCaptureCounter = ConsolePort_2_ClockTimer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!ConsolePort_2_ClockTimer_UDB_CONTROL_REG_REMOVED)
            ConsolePort_2_ClockTimer_backup.TimerControlRegister = ConsolePort_2_ClockTimer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: ConsolePort_2_ClockTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  ConsolePort_2_ClockTimer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void ConsolePort_2_ClockTimer_RestoreConfig(void) 
{   
    #if (!ConsolePort_2_ClockTimer_UsingFixedFunction)

        ConsolePort_2_ClockTimer_WriteCounter(ConsolePort_2_ClockTimer_backup.TimerUdb);
        ConsolePort_2_ClockTimer_STATUS_MASK =ConsolePort_2_ClockTimer_backup.InterruptMaskValue;
        #if (ConsolePort_2_ClockTimer_UsingHWCaptureCounter)
            ConsolePort_2_ClockTimer_SetCaptureCount(ConsolePort_2_ClockTimer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!ConsolePort_2_ClockTimer_UDB_CONTROL_REG_REMOVED)
            ConsolePort_2_ClockTimer_WriteControlRegister(ConsolePort_2_ClockTimer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: ConsolePort_2_ClockTimer_Sleep
********************************************************************************
*
* Summary:
*     Stop and Save the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  ConsolePort_2_ClockTimer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void ConsolePort_2_ClockTimer_Sleep(void) 
{
    #if(!ConsolePort_2_ClockTimer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(ConsolePort_2_ClockTimer_CTRL_ENABLE == (ConsolePort_2_ClockTimer_CONTROL & ConsolePort_2_ClockTimer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            ConsolePort_2_ClockTimer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            ConsolePort_2_ClockTimer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    ConsolePort_2_ClockTimer_Stop();
    ConsolePort_2_ClockTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ConsolePort_2_ClockTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*
* Parameters:
*  void
*
* Return:
*  void
*
* Global variables:
*  ConsolePort_2_ClockTimer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void ConsolePort_2_ClockTimer_Wakeup(void) 
{
    ConsolePort_2_ClockTimer_RestoreConfig();
    #if(!ConsolePort_2_ClockTimer_UDB_CONTROL_REG_REMOVED)
        if(ConsolePort_2_ClockTimer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                ConsolePort_2_ClockTimer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
