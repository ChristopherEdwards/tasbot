/*******************************************************************************
* File Name: P3_Latch.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_P3_Latch_H) /* Pins P3_Latch_H */
#define CY_PINS_P3_Latch_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "P3_Latch_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 P3_Latch__PORT == 15 && ((P3_Latch__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    P3_Latch_Write(uint8 value);
void    P3_Latch_SetDriveMode(uint8 mode);
uint8   P3_Latch_ReadDataReg(void);
uint8   P3_Latch_Read(void);
void    P3_Latch_SetInterruptMode(uint16 position, uint16 mode);
uint8   P3_Latch_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the P3_Latch_SetDriveMode() function.
     *  @{
     */
        #define P3_Latch_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define P3_Latch_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define P3_Latch_DM_RES_UP          PIN_DM_RES_UP
        #define P3_Latch_DM_RES_DWN         PIN_DM_RES_DWN
        #define P3_Latch_DM_OD_LO           PIN_DM_OD_LO
        #define P3_Latch_DM_OD_HI           PIN_DM_OD_HI
        #define P3_Latch_DM_STRONG          PIN_DM_STRONG
        #define P3_Latch_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define P3_Latch_MASK               P3_Latch__MASK
#define P3_Latch_SHIFT              P3_Latch__SHIFT
#define P3_Latch_WIDTH              1u

/* Interrupt constants */
#if defined(P3_Latch__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in P3_Latch_SetInterruptMode() function.
     *  @{
     */
        #define P3_Latch_INTR_NONE      (uint16)(0x0000u)
        #define P3_Latch_INTR_RISING    (uint16)(0x0001u)
        #define P3_Latch_INTR_FALLING   (uint16)(0x0002u)
        #define P3_Latch_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define P3_Latch_INTR_MASK      (0x01u) 
#endif /* (P3_Latch__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define P3_Latch_PS                     (* (reg8 *) P3_Latch__PS)
/* Data Register */
#define P3_Latch_DR                     (* (reg8 *) P3_Latch__DR)
/* Port Number */
#define P3_Latch_PRT_NUM                (* (reg8 *) P3_Latch__PRT) 
/* Connect to Analog Globals */                                                  
#define P3_Latch_AG                     (* (reg8 *) P3_Latch__AG)                       
/* Analog MUX bux enable */
#define P3_Latch_AMUX                   (* (reg8 *) P3_Latch__AMUX) 
/* Bidirectional Enable */                                                        
#define P3_Latch_BIE                    (* (reg8 *) P3_Latch__BIE)
/* Bit-mask for Aliased Register Access */
#define P3_Latch_BIT_MASK               (* (reg8 *) P3_Latch__BIT_MASK)
/* Bypass Enable */
#define P3_Latch_BYP                    (* (reg8 *) P3_Latch__BYP)
/* Port wide control signals */                                                   
#define P3_Latch_CTL                    (* (reg8 *) P3_Latch__CTL)
/* Drive Modes */
#define P3_Latch_DM0                    (* (reg8 *) P3_Latch__DM0) 
#define P3_Latch_DM1                    (* (reg8 *) P3_Latch__DM1)
#define P3_Latch_DM2                    (* (reg8 *) P3_Latch__DM2) 
/* Input Buffer Disable Override */
#define P3_Latch_INP_DIS                (* (reg8 *) P3_Latch__INP_DIS)
/* LCD Common or Segment Drive */
#define P3_Latch_LCD_COM_SEG            (* (reg8 *) P3_Latch__LCD_COM_SEG)
/* Enable Segment LCD */
#define P3_Latch_LCD_EN                 (* (reg8 *) P3_Latch__LCD_EN)
/* Slew Rate Control */
#define P3_Latch_SLW                    (* (reg8 *) P3_Latch__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define P3_Latch_PRTDSI__CAPS_SEL       (* (reg8 *) P3_Latch__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define P3_Latch_PRTDSI__DBL_SYNC_IN    (* (reg8 *) P3_Latch__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define P3_Latch_PRTDSI__OE_SEL0        (* (reg8 *) P3_Latch__PRTDSI__OE_SEL0) 
#define P3_Latch_PRTDSI__OE_SEL1        (* (reg8 *) P3_Latch__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define P3_Latch_PRTDSI__OUT_SEL0       (* (reg8 *) P3_Latch__PRTDSI__OUT_SEL0) 
#define P3_Latch_PRTDSI__OUT_SEL1       (* (reg8 *) P3_Latch__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define P3_Latch_PRTDSI__SYNC_OUT       (* (reg8 *) P3_Latch__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(P3_Latch__SIO_CFG)
    #define P3_Latch_SIO_HYST_EN        (* (reg8 *) P3_Latch__SIO_HYST_EN)
    #define P3_Latch_SIO_REG_HIFREQ     (* (reg8 *) P3_Latch__SIO_REG_HIFREQ)
    #define P3_Latch_SIO_CFG            (* (reg8 *) P3_Latch__SIO_CFG)
    #define P3_Latch_SIO_DIFF           (* (reg8 *) P3_Latch__SIO_DIFF)
#endif /* (P3_Latch__SIO_CFG) */

/* Interrupt Registers */
#if defined(P3_Latch__INTSTAT)
    #define P3_Latch_INTSTAT            (* (reg8 *) P3_Latch__INTSTAT)
    #define P3_Latch_SNAP               (* (reg8 *) P3_Latch__SNAP)
    
	#define P3_Latch_0_INTTYPE_REG 		(* (reg8 *) P3_Latch__0__INTTYPE)
#endif /* (P3_Latch__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_P3_Latch_H */


/* [] END OF FILE */
