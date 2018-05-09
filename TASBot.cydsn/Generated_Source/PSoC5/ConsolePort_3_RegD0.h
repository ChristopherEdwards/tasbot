/*******************************************************************************
* File Name: ConsolePort_3_RegD0.h
* Version 2.30
*
* Description:
*  This header file contains definitions associated with the Shift Register
*  component.
*
* Note: none
*
********************************************************************************
* Copyright 2008-2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/


#if !defined(CY_SHIFTREG_ConsolePort_3_RegD0_H)
#define CY_SHIFTREG_ConsolePort_3_RegD0_H

#include "cyfitter.h"
#include "cytypes.h"
#include "CyLib.h"

/* Check to see if required defines such as CY_PSOC5A are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5A)
    #error Component ShiftReg_v2_30 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5A) */


/***************************************
*   Conditional Compilation Parameters
***************************************/

#define ConsolePort_3_RegD0_FIFO_SIZE          (4u)
#define ConsolePort_3_RegD0_USE_INPUT_FIFO     (0u)
#define ConsolePort_3_RegD0_USE_OUTPUT_FIFO    (0u)
#define ConsolePort_3_RegD0_SR_SIZE            (16u)


/***************************************
*     Data Struct Definitions
***************************************/

/* Sleep Mode API Support */
typedef struct
{
    uint8 enableState;

    uint16 saveSrA0Reg;
    uint16 saveSrA1Reg;

    #if(CY_UDB_V0)
        uint16 saveSrIntMask;
    #endif /* (CY_UDB_V0) */

} ConsolePort_3_RegD0_BACKUP_STRUCT;


/***************************************
*        Function Prototypes
***************************************/

void  ConsolePort_3_RegD0_Start(void)                              ;
void  ConsolePort_3_RegD0_Stop(void)                               ;
void  ConsolePort_3_RegD0_Init(void)                               ;
void  ConsolePort_3_RegD0_Enable(void)                             ;
void  ConsolePort_3_RegD0_RestoreConfig(void)                      ;
void  ConsolePort_3_RegD0_SaveConfig(void)                         ;
void  ConsolePort_3_RegD0_Sleep(void)                              ;
void  ConsolePort_3_RegD0_Wakeup(void)                             ;
void  ConsolePort_3_RegD0_EnableInt(void)                          ;
void  ConsolePort_3_RegD0_DisableInt(void)                         ;
void  ConsolePort_3_RegD0_SetIntMode(uint8 interruptSource)        ;
uint8 ConsolePort_3_RegD0_GetIntStatus(void)                       ;
void  ConsolePort_3_RegD0_WriteRegValue(uint16 shiftData) \
                                                                ;
uint16 ConsolePort_3_RegD0_ReadRegValue(void) ;
uint8    ConsolePort_3_RegD0_GetFIFOStatus(uint8 fifoId)           ;

#if(0u != ConsolePort_3_RegD0_USE_INPUT_FIFO)
    cystatus ConsolePort_3_RegD0_WriteData(uint16 shiftData) \
                                                                ;
#endif /* (0u != ConsolePort_3_RegD0_USE_INPUT_FIFO) */

#if(0u != ConsolePort_3_RegD0_USE_OUTPUT_FIFO)
    uint16 ConsolePort_3_RegD0_ReadData(void) ;
#endif /* (0u != ConsolePort_3_RegD0_USE_OUTPUT_FIFO) */


/**********************************
*   Variable with external linkage
**********************************/

extern uint8 ConsolePort_3_RegD0_initVar;


/***************************************
*           API Constants
***************************************/

#define ConsolePort_3_RegD0_LOAD                   (0x01u)
#define ConsolePort_3_RegD0_STORE                  (0x02u)
#define ConsolePort_3_RegD0_RESET                  (0x04u)

#define ConsolePort_3_RegD0_IN_FIFO                (0x01u)
#define ConsolePort_3_RegD0_OUT_FIFO               (0x02u)

#define ConsolePort_3_RegD0_RET_FIFO_FULL          (0x00u)

/* This define is obsolete */
#define ConsolePort_3_RegD0_RET_FIFO_NOT_EMPTY     (0x01u)

#define ConsolePort_3_RegD0_RET_FIFO_PARTIAL       (0x01u)
#define ConsolePort_3_RegD0_RET_FIFO_EMPTY         (0x02u)
#define ConsolePort_3_RegD0_RET_FIFO_NOT_DEFINED   (0xFEu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ConsolePort_3_RegD0__LEFT 0
#define ConsolePort_3_RegD0__RIGHT 1



/***************************************
*    Initial Parameter Constants
***************************************/

#define ConsolePort_3_RegD0_SR_MASK    (0xFFFFu) /* Unsigned is added to parameter */
#define ConsolePort_3_RegD0_INT_SRC    (1u)
#define ConsolePort_3_RegD0_DIRECTION  (1u)


/***************************************
*             Registers
***************************************/

/* Control register */
#define ConsolePort_3_RegD0_SR_CONTROL_REG (* (reg8 *) \
                                           ConsolePort_3_RegD0_bSR_SyncCtl_CtrlReg__CONTROL_REG)
#define ConsolePort_3_RegD0_SR_CONTROL_PTR (  (reg8 *) \
                                           ConsolePort_3_RegD0_bSR_SyncCtl_CtrlReg__CONTROL_REG)

/* Status register */
#define ConsolePort_3_RegD0_SR_STATUS_REG      (* (reg8 *) ConsolePort_3_RegD0_bSR_StsReg__STATUS_REG)
#define ConsolePort_3_RegD0_SR_STATUS_PTR      (  (reg8 *) ConsolePort_3_RegD0_bSR_StsReg__STATUS_REG)

/* Interrupt status register */
#define ConsolePort_3_RegD0_SR_STATUS_MASK_REG (* (reg8 *) ConsolePort_3_RegD0_bSR_StsReg__MASK_REG)
#define ConsolePort_3_RegD0_SR_STATUS_MASK_PTR (  (reg8 *) ConsolePort_3_RegD0_bSR_StsReg__MASK_REG)

/* Aux control register */
#define ConsolePort_3_RegD0_SR_AUX_CONTROL_REG (* (reg8 *) ConsolePort_3_RegD0_bSR_StsReg__STATUS_AUX_CTL_REG)
#define ConsolePort_3_RegD0_SR_AUX_CONTROL_PTR (  (reg8 *) ConsolePort_3_RegD0_bSR_StsReg__STATUS_AUX_CTL_REG)

/* A1 register: only used to implement capture function */
#define ConsolePort_3_RegD0_SHIFT_REG_CAPTURE_PTR    ( (reg8 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A1_REG )

#if(CY_PSOC3 || CY_PSOC5)
    #define ConsolePort_3_RegD0_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__F0_REG )

    #define ConsolePort_3_RegD0_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A0_REG )

    #define ConsolePort_3_RegD0_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A1_REG )

    #define ConsolePort_3_RegD0_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__F1_REG )

#else
    #if(ConsolePort_3_RegD0_SR_SIZE <= 8u) /* 8bit - ShiftReg */
        #define ConsolePort_3_RegD0_IN_FIFO_VAL_LSB_PTR        ( (reg8 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_LSB_PTR          ( (reg8 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_VALUE_LSB_PTR    ( (reg8 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define ConsolePort_3_RegD0_OUT_FIFO_VAL_LSB_PTR       ( (reg8 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #elif(ConsolePort_3_RegD0_SR_SIZE <= 16u) /* 16bit - ShiftReg */
        #define ConsolePort_3_RegD0_IN_FIFO_VAL_LSB_PTR        ( (reg16 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__16BIT_F0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_LSB_PTR          ( (reg16 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__16BIT_A0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_VALUE_LSB_PTR    ( (reg16 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__16BIT_A1_REG )

        #define ConsolePort_3_RegD0_OUT_FIFO_VAL_LSB_PTR       ( (reg16 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__16BIT_F1_REG )


    #elif(ConsolePort_3_RegD0_SR_SIZE <= 24u) /* 24bit - ShiftReg */
        #define ConsolePort_3_RegD0_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__F0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__A1_REG )

        #define ConsolePort_3_RegD0_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                        ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__F1_REG )

    #else /* 32bit - ShiftReg */
        #define ConsolePort_3_RegD0_IN_FIFO_VAL_LSB_PTR        ( (reg32 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__32BIT_F0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_LSB_PTR          ( (reg32 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__32BIT_A0_REG )

        #define ConsolePort_3_RegD0_SHIFT_REG_VALUE_LSB_PTR    ( (reg32 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__32BIT_A1_REG )

        #define ConsolePort_3_RegD0_OUT_FIFO_VAL_LSB_PTR       ( (reg32 *) \
                                  ConsolePort_3_RegD0_bSR_sC16_BShiftRegDp_u0__32BIT_F1_REG )

    #endif  /* (ConsolePort_3_RegD0_SR_SIZE <= 8u) */
#endif      /* (CY_PSOC3 || CY_PSOC5) */


/***************************************
*       Register Constants
***************************************/

#define ConsolePort_3_RegD0_INTERRUPTS_ENABLE      (0x10u)
#define ConsolePort_3_RegD0_LOAD_INT_EN            (0x01u)
#define ConsolePort_3_RegD0_STORE_INT_EN           (0x02u)
#define ConsolePort_3_RegD0_RESET_INT_EN           (0x04u)
#define ConsolePort_3_RegD0_CLK_EN                 (0x01u)

#define ConsolePort_3_RegD0_RESET_INT_EN_MASK      (0xFBu)
#define ConsolePort_3_RegD0_LOAD_INT_EN_MASK       (0xFEu)
#define ConsolePort_3_RegD0_STORE_INT_EN_MASK      (0xFDu)
#define ConsolePort_3_RegD0_INTS_EN_MASK           (0x07u)

#define ConsolePort_3_RegD0_OUT_FIFO_CLR_BIT       (0x02u)

#if(0u != ConsolePort_3_RegD0_USE_INPUT_FIFO)

    #define ConsolePort_3_RegD0_IN_FIFO_MASK       (0x18u)

    #define ConsolePort_3_RegD0_IN_FIFO_FULL       (0x00u)
    #define ConsolePort_3_RegD0_IN_FIFO_EMPTY      (0x01u)
    #define ConsolePort_3_RegD0_IN_FIFO_PARTIAL    (0x02u)
    
    /* This define is obsolete */
    #define ConsolePort_3_RegD0_IN_FIFO_NOT_EMPTY  (0x02u)
    
#endif /* (0u != ConsolePort_3_RegD0_USE_INPUT_FIFO) */

#define ConsolePort_3_RegD0_OUT_FIFO_MASK          (0x60u)

#define ConsolePort_3_RegD0_OUT_FIFO_EMPTY         (0x00u)
#define ConsolePort_3_RegD0_OUT_FIFO_FULL          (0x01u)
#define ConsolePort_3_RegD0_OUT_FIFO_PARTIAL       (0x02u)

/* This define is obsolete */
#define ConsolePort_3_RegD0_OUT_FIFO_NOT_EMPTY     (0x02u)

#define ConsolePort_3_RegD0_IN_FIFO_SHIFT_MASK     (0x03u)
#define ConsolePort_3_RegD0_OUT_FIFO_SHIFT_MASK    (0x05u)

#define ConsolePort_3_RegD0_DISABLED               (0u)
#define ConsolePort_3_RegD0_DEFAULT_A0             (0u)
#define ConsolePort_3_RegD0_DEFAULT_A1             (0u)


/***************************************
*       Macros
***************************************/

#define ConsolePort_3_RegD0_IS_ENABLED         (0u != (ConsolePort_3_RegD0_SR_CONTROL & ConsolePort_3_RegD0_CLK_EN))

#define ConsolePort_3_RegD0_GET_OUT_FIFO_STS   ((ConsolePort_3_RegD0_SR_STATUS & ConsolePort_3_RegD0_OUT_FIFO_MASK) >> \
                                              ConsolePort_3_RegD0_OUT_FIFO_SHIFT_MASK)

#define ConsolePort_3_RegD0_GET_IN_FIFO_STS    ((ConsolePort_3_RegD0_SR_STATUS & ConsolePort_3_RegD0_IN_FIFO_MASK)  >> \
                                              ConsolePort_3_RegD0_IN_FIFO_SHIFT_MASK)


/***************************************
*       Obsolete
***************************************/

/* Following code are OBSOLETE and must not be used 
 * starting from ShiftReg 2.20 
 */

#define ConsolePort_3_RegD0_SR_CONTROL     (ConsolePort_3_RegD0_SR_CONTROL_REG)
#define ConsolePort_3_RegD0_SR_STATUS      (ConsolePort_3_RegD0_SR_STATUS_REG)
#define ConsolePort_3_RegD0_SR_STATUS_MASK (ConsolePort_3_RegD0_SR_STATUS_MASK_REG)
#define ConsolePort_3_RegD0_SR_AUX_CONTROL (ConsolePort_3_RegD0_SR_AUX_CONTROL_REG)

#define ConsolePort_3_RegD0_IN_FIFO_SHFT_MASK  (ConsolePort_3_RegD0_IN_FIFO_SHIFT_MASK)
#define ConsolePort_3_RegD0_OUT_FIFO_SHFT_MASK (ConsolePort_3_RegD0_OUT_FIFO_SHFIT_MASK)

#define ConsolePort_3_RegD0_RET_FIFO_BAD_PARAM (0xFFu)

#endif /* (CY_SHIFTREG_ConsolePort_3_RegD0_H) */


/* [] END OF FILE */
