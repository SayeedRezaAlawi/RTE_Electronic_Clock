/*******************************************************************************
* File Name: AAA.h  
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

#if !defined(CY_PINS_AAA_H) /* Pins AAA_H */
#define CY_PINS_AAA_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AAA_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AAA__PORT == 15 && ((AAA__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AAA_Write(uint8 value);
void    AAA_SetDriveMode(uint8 mode);
uint8   AAA_ReadDataReg(void);
uint8   AAA_Read(void);
void    AAA_SetInterruptMode(uint16 position, uint16 mode);
uint8   AAA_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AAA_SetDriveMode() function.
     *  @{
     */
        #define AAA_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AAA_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AAA_DM_RES_UP          PIN_DM_RES_UP
        #define AAA_DM_RES_DWN         PIN_DM_RES_DWN
        #define AAA_DM_OD_LO           PIN_DM_OD_LO
        #define AAA_DM_OD_HI           PIN_DM_OD_HI
        #define AAA_DM_STRONG          PIN_DM_STRONG
        #define AAA_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AAA_MASK               AAA__MASK
#define AAA_SHIFT              AAA__SHIFT
#define AAA_WIDTH              1u

/* Interrupt constants */
#if defined(AAA__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AAA_SetInterruptMode() function.
     *  @{
     */
        #define AAA_INTR_NONE      (uint16)(0x0000u)
        #define AAA_INTR_RISING    (uint16)(0x0001u)
        #define AAA_INTR_FALLING   (uint16)(0x0002u)
        #define AAA_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AAA_INTR_MASK      (0x01u) 
#endif /* (AAA__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AAA_PS                     (* (reg8 *) AAA__PS)
/* Data Register */
#define AAA_DR                     (* (reg8 *) AAA__DR)
/* Port Number */
#define AAA_PRT_NUM                (* (reg8 *) AAA__PRT) 
/* Connect to Analog Globals */                                                  
#define AAA_AG                     (* (reg8 *) AAA__AG)                       
/* Analog MUX bux enable */
#define AAA_AMUX                   (* (reg8 *) AAA__AMUX) 
/* Bidirectional Enable */                                                        
#define AAA_BIE                    (* (reg8 *) AAA__BIE)
/* Bit-mask for Aliased Register Access */
#define AAA_BIT_MASK               (* (reg8 *) AAA__BIT_MASK)
/* Bypass Enable */
#define AAA_BYP                    (* (reg8 *) AAA__BYP)
/* Port wide control signals */                                                   
#define AAA_CTL                    (* (reg8 *) AAA__CTL)
/* Drive Modes */
#define AAA_DM0                    (* (reg8 *) AAA__DM0) 
#define AAA_DM1                    (* (reg8 *) AAA__DM1)
#define AAA_DM2                    (* (reg8 *) AAA__DM2) 
/* Input Buffer Disable Override */
#define AAA_INP_DIS                (* (reg8 *) AAA__INP_DIS)
/* LCD Common or Segment Drive */
#define AAA_LCD_COM_SEG            (* (reg8 *) AAA__LCD_COM_SEG)
/* Enable Segment LCD */
#define AAA_LCD_EN                 (* (reg8 *) AAA__LCD_EN)
/* Slew Rate Control */
#define AAA_SLW                    (* (reg8 *) AAA__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AAA_PRTDSI__CAPS_SEL       (* (reg8 *) AAA__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AAA_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AAA__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AAA_PRTDSI__OE_SEL0        (* (reg8 *) AAA__PRTDSI__OE_SEL0) 
#define AAA_PRTDSI__OE_SEL1        (* (reg8 *) AAA__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AAA_PRTDSI__OUT_SEL0       (* (reg8 *) AAA__PRTDSI__OUT_SEL0) 
#define AAA_PRTDSI__OUT_SEL1       (* (reg8 *) AAA__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AAA_PRTDSI__SYNC_OUT       (* (reg8 *) AAA__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AAA__SIO_CFG)
    #define AAA_SIO_HYST_EN        (* (reg8 *) AAA__SIO_HYST_EN)
    #define AAA_SIO_REG_HIFREQ     (* (reg8 *) AAA__SIO_REG_HIFREQ)
    #define AAA_SIO_CFG            (* (reg8 *) AAA__SIO_CFG)
    #define AAA_SIO_DIFF           (* (reg8 *) AAA__SIO_DIFF)
#endif /* (AAA__SIO_CFG) */

/* Interrupt Registers */
#if defined(AAA__INTSTAT)
    #define AAA_INTSTAT            (* (reg8 *) AAA__INTSTAT)
    #define AAA_SNAP               (* (reg8 *) AAA__SNAP)
    
	#define AAA_0_INTTYPE_REG 		(* (reg8 *) AAA__0__INTTYPE)
#endif /* (AAA__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AAA_H */


/* [] END OF FILE */
