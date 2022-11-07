/*******************************************************************************
* File Name: RST.h  
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

#if !defined(CY_PINS_RST_H) /* Pins RST_H */
#define CY_PINS_RST_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "RST_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 RST__PORT == 15 && ((RST__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    RST_Write(uint8 value);
void    RST_SetDriveMode(uint8 mode);
uint8   RST_ReadDataReg(void);
uint8   RST_Read(void);
void    RST_SetInterruptMode(uint16 position, uint16 mode);
uint8   RST_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the RST_SetDriveMode() function.
     *  @{
     */
        #define RST_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define RST_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define RST_DM_RES_UP          PIN_DM_RES_UP
        #define RST_DM_RES_DWN         PIN_DM_RES_DWN
        #define RST_DM_OD_LO           PIN_DM_OD_LO
        #define RST_DM_OD_HI           PIN_DM_OD_HI
        #define RST_DM_STRONG          PIN_DM_STRONG
        #define RST_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define RST_MASK               RST__MASK
#define RST_SHIFT              RST__SHIFT
#define RST_WIDTH              1u

/* Interrupt constants */
#if defined(RST__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in RST_SetInterruptMode() function.
     *  @{
     */
        #define RST_INTR_NONE      (uint16)(0x0000u)
        #define RST_INTR_RISING    (uint16)(0x0001u)
        #define RST_INTR_FALLING   (uint16)(0x0002u)
        #define RST_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define RST_INTR_MASK      (0x01u) 
#endif /* (RST__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define RST_PS                     (* (reg8 *) RST__PS)
/* Data Register */
#define RST_DR                     (* (reg8 *) RST__DR)
/* Port Number */
#define RST_PRT_NUM                (* (reg8 *) RST__PRT) 
/* Connect to Analog Globals */                                                  
#define RST_AG                     (* (reg8 *) RST__AG)                       
/* Analog MUX bux enable */
#define RST_AMUX                   (* (reg8 *) RST__AMUX) 
/* Bidirectional Enable */                                                        
#define RST_BIE                    (* (reg8 *) RST__BIE)
/* Bit-mask for Aliased Register Access */
#define RST_BIT_MASK               (* (reg8 *) RST__BIT_MASK)
/* Bypass Enable */
#define RST_BYP                    (* (reg8 *) RST__BYP)
/* Port wide control signals */                                                   
#define RST_CTL                    (* (reg8 *) RST__CTL)
/* Drive Modes */
#define RST_DM0                    (* (reg8 *) RST__DM0) 
#define RST_DM1                    (* (reg8 *) RST__DM1)
#define RST_DM2                    (* (reg8 *) RST__DM2) 
/* Input Buffer Disable Override */
#define RST_INP_DIS                (* (reg8 *) RST__INP_DIS)
/* LCD Common or Segment Drive */
#define RST_LCD_COM_SEG            (* (reg8 *) RST__LCD_COM_SEG)
/* Enable Segment LCD */
#define RST_LCD_EN                 (* (reg8 *) RST__LCD_EN)
/* Slew Rate Control */
#define RST_SLW                    (* (reg8 *) RST__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define RST_PRTDSI__CAPS_SEL       (* (reg8 *) RST__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define RST_PRTDSI__DBL_SYNC_IN    (* (reg8 *) RST__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define RST_PRTDSI__OE_SEL0        (* (reg8 *) RST__PRTDSI__OE_SEL0) 
#define RST_PRTDSI__OE_SEL1        (* (reg8 *) RST__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define RST_PRTDSI__OUT_SEL0       (* (reg8 *) RST__PRTDSI__OUT_SEL0) 
#define RST_PRTDSI__OUT_SEL1       (* (reg8 *) RST__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define RST_PRTDSI__SYNC_OUT       (* (reg8 *) RST__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(RST__SIO_CFG)
    #define RST_SIO_HYST_EN        (* (reg8 *) RST__SIO_HYST_EN)
    #define RST_SIO_REG_HIFREQ     (* (reg8 *) RST__SIO_REG_HIFREQ)
    #define RST_SIO_CFG            (* (reg8 *) RST__SIO_CFG)
    #define RST_SIO_DIFF           (* (reg8 *) RST__SIO_DIFF)
#endif /* (RST__SIO_CFG) */

/* Interrupt Registers */
#if defined(RST__INTSTAT)
    #define RST_INTSTAT            (* (reg8 *) RST__INTSTAT)
    #define RST_SNAP               (* (reg8 *) RST__SNAP)
    
	#define RST_0_INTTYPE_REG 		(* (reg8 *) RST__0__INTTYPE)
#endif /* (RST__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_RST_H */


/* [] END OF FILE */
