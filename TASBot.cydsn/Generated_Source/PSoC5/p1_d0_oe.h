/*******************************************************************************
* File Name: p1_d0_oe.h  
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

#if !defined(CY_PINS_p1_d0_oe_H) /* Pins p1_d0_oe_H */
#define CY_PINS_p1_d0_oe_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "p1_d0_oe_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 p1_d0_oe__PORT == 15 && ((p1_d0_oe__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    p1_d0_oe_Write(uint8 value);
void    p1_d0_oe_SetDriveMode(uint8 mode);
uint8   p1_d0_oe_ReadDataReg(void);
uint8   p1_d0_oe_Read(void);
void    p1_d0_oe_SetInterruptMode(uint16 position, uint16 mode);
uint8   p1_d0_oe_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the p1_d0_oe_SetDriveMode() function.
     *  @{
     */
        #define p1_d0_oe_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define p1_d0_oe_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define p1_d0_oe_DM_RES_UP          PIN_DM_RES_UP
        #define p1_d0_oe_DM_RES_DWN         PIN_DM_RES_DWN
        #define p1_d0_oe_DM_OD_LO           PIN_DM_OD_LO
        #define p1_d0_oe_DM_OD_HI           PIN_DM_OD_HI
        #define p1_d0_oe_DM_STRONG          PIN_DM_STRONG
        #define p1_d0_oe_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define p1_d0_oe_MASK               p1_d0_oe__MASK
#define p1_d0_oe_SHIFT              p1_d0_oe__SHIFT
#define p1_d0_oe_WIDTH              1u

/* Interrupt constants */
#if defined(p1_d0_oe__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in p1_d0_oe_SetInterruptMode() function.
     *  @{
     */
        #define p1_d0_oe_INTR_NONE      (uint16)(0x0000u)
        #define p1_d0_oe_INTR_RISING    (uint16)(0x0001u)
        #define p1_d0_oe_INTR_FALLING   (uint16)(0x0002u)
        #define p1_d0_oe_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define p1_d0_oe_INTR_MASK      (0x01u) 
#endif /* (p1_d0_oe__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define p1_d0_oe_PS                     (* (reg8 *) p1_d0_oe__PS)
/* Data Register */
#define p1_d0_oe_DR                     (* (reg8 *) p1_d0_oe__DR)
/* Port Number */
#define p1_d0_oe_PRT_NUM                (* (reg8 *) p1_d0_oe__PRT) 
/* Connect to Analog Globals */                                                  
#define p1_d0_oe_AG                     (* (reg8 *) p1_d0_oe__AG)                       
/* Analog MUX bux enable */
#define p1_d0_oe_AMUX                   (* (reg8 *) p1_d0_oe__AMUX) 
/* Bidirectional Enable */                                                        
#define p1_d0_oe_BIE                    (* (reg8 *) p1_d0_oe__BIE)
/* Bit-mask for Aliased Register Access */
#define p1_d0_oe_BIT_MASK               (* (reg8 *) p1_d0_oe__BIT_MASK)
/* Bypass Enable */
#define p1_d0_oe_BYP                    (* (reg8 *) p1_d0_oe__BYP)
/* Port wide control signals */                                                   
#define p1_d0_oe_CTL                    (* (reg8 *) p1_d0_oe__CTL)
/* Drive Modes */
#define p1_d0_oe_DM0                    (* (reg8 *) p1_d0_oe__DM0) 
#define p1_d0_oe_DM1                    (* (reg8 *) p1_d0_oe__DM1)
#define p1_d0_oe_DM2                    (* (reg8 *) p1_d0_oe__DM2) 
/* Input Buffer Disable Override */
#define p1_d0_oe_INP_DIS                (* (reg8 *) p1_d0_oe__INP_DIS)
/* LCD Common or Segment Drive */
#define p1_d0_oe_LCD_COM_SEG            (* (reg8 *) p1_d0_oe__LCD_COM_SEG)
/* Enable Segment LCD */
#define p1_d0_oe_LCD_EN                 (* (reg8 *) p1_d0_oe__LCD_EN)
/* Slew Rate Control */
#define p1_d0_oe_SLW                    (* (reg8 *) p1_d0_oe__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define p1_d0_oe_PRTDSI__CAPS_SEL       (* (reg8 *) p1_d0_oe__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define p1_d0_oe_PRTDSI__DBL_SYNC_IN    (* (reg8 *) p1_d0_oe__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define p1_d0_oe_PRTDSI__OE_SEL0        (* (reg8 *) p1_d0_oe__PRTDSI__OE_SEL0) 
#define p1_d0_oe_PRTDSI__OE_SEL1        (* (reg8 *) p1_d0_oe__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define p1_d0_oe_PRTDSI__OUT_SEL0       (* (reg8 *) p1_d0_oe__PRTDSI__OUT_SEL0) 
#define p1_d0_oe_PRTDSI__OUT_SEL1       (* (reg8 *) p1_d0_oe__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define p1_d0_oe_PRTDSI__SYNC_OUT       (* (reg8 *) p1_d0_oe__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(p1_d0_oe__SIO_CFG)
    #define p1_d0_oe_SIO_HYST_EN        (* (reg8 *) p1_d0_oe__SIO_HYST_EN)
    #define p1_d0_oe_SIO_REG_HIFREQ     (* (reg8 *) p1_d0_oe__SIO_REG_HIFREQ)
    #define p1_d0_oe_SIO_CFG            (* (reg8 *) p1_d0_oe__SIO_CFG)
    #define p1_d0_oe_SIO_DIFF           (* (reg8 *) p1_d0_oe__SIO_DIFF)
#endif /* (p1_d0_oe__SIO_CFG) */

/* Interrupt Registers */
#if defined(p1_d0_oe__INTSTAT)
    #define p1_d0_oe_INTSTAT            (* (reg8 *) p1_d0_oe__INTSTAT)
    #define p1_d0_oe_SNAP               (* (reg8 *) p1_d0_oe__SNAP)
    
	#define p1_d0_oe_0_INTTYPE_REG 		(* (reg8 *) p1_d0_oe__0__INTTYPE)
#endif /* (p1_d0_oe__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_p1_d0_oe_H */


/* [] END OF FILE */
