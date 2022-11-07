/*******************************************************************************
* File Name: SI.h  
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

#if !defined(CY_PINS_SI_H) /* Pins SI_H */
#define CY_PINS_SI_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "SI_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 SI__PORT == 15 && ((SI__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    SI_Write(uint8 value);
void    SI_SetDriveMode(uint8 mode);
uint8   SI_ReadDataReg(void);
uint8   SI_Read(void);
void    SI_SetInterruptMode(uint16 position, uint16 mode);
uint8   SI_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the SI_SetDriveMode() function.
     *  @{
     */
        #define SI_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define SI_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define SI_DM_RES_UP          PIN_DM_RES_UP
        #define SI_DM_RES_DWN         PIN_DM_RES_DWN
        #define SI_DM_OD_LO           PIN_DM_OD_LO
        #define SI_DM_OD_HI           PIN_DM_OD_HI
        #define SI_DM_STRONG          PIN_DM_STRONG
        #define SI_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define SI_MASK               SI__MASK
#define SI_SHIFT              SI__SHIFT
#define SI_WIDTH              1u

/* Interrupt constants */
#if defined(SI__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SI_SetInterruptMode() function.
     *  @{
     */
        #define SI_INTR_NONE      (uint16)(0x0000u)
        #define SI_INTR_RISING    (uint16)(0x0001u)
        #define SI_INTR_FALLING   (uint16)(0x0002u)
        #define SI_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define SI_INTR_MASK      (0x01u) 
#endif /* (SI__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SI_PS                     (* (reg8 *) SI__PS)
/* Data Register */
#define SI_DR                     (* (reg8 *) SI__DR)
/* Port Number */
#define SI_PRT_NUM                (* (reg8 *) SI__PRT) 
/* Connect to Analog Globals */                                                  
#define SI_AG                     (* (reg8 *) SI__AG)                       
/* Analog MUX bux enable */
#define SI_AMUX                   (* (reg8 *) SI__AMUX) 
/* Bidirectional Enable */                                                        
#define SI_BIE                    (* (reg8 *) SI__BIE)
/* Bit-mask for Aliased Register Access */
#define SI_BIT_MASK               (* (reg8 *) SI__BIT_MASK)
/* Bypass Enable */
#define SI_BYP                    (* (reg8 *) SI__BYP)
/* Port wide control signals */                                                   
#define SI_CTL                    (* (reg8 *) SI__CTL)
/* Drive Modes */
#define SI_DM0                    (* (reg8 *) SI__DM0) 
#define SI_DM1                    (* (reg8 *) SI__DM1)
#define SI_DM2                    (* (reg8 *) SI__DM2) 
/* Input Buffer Disable Override */
#define SI_INP_DIS                (* (reg8 *) SI__INP_DIS)
/* LCD Common or Segment Drive */
#define SI_LCD_COM_SEG            (* (reg8 *) SI__LCD_COM_SEG)
/* Enable Segment LCD */
#define SI_LCD_EN                 (* (reg8 *) SI__LCD_EN)
/* Slew Rate Control */
#define SI_SLW                    (* (reg8 *) SI__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define SI_PRTDSI__CAPS_SEL       (* (reg8 *) SI__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define SI_PRTDSI__DBL_SYNC_IN    (* (reg8 *) SI__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define SI_PRTDSI__OE_SEL0        (* (reg8 *) SI__PRTDSI__OE_SEL0) 
#define SI_PRTDSI__OE_SEL1        (* (reg8 *) SI__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define SI_PRTDSI__OUT_SEL0       (* (reg8 *) SI__PRTDSI__OUT_SEL0) 
#define SI_PRTDSI__OUT_SEL1       (* (reg8 *) SI__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define SI_PRTDSI__SYNC_OUT       (* (reg8 *) SI__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(SI__SIO_CFG)
    #define SI_SIO_HYST_EN        (* (reg8 *) SI__SIO_HYST_EN)
    #define SI_SIO_REG_HIFREQ     (* (reg8 *) SI__SIO_REG_HIFREQ)
    #define SI_SIO_CFG            (* (reg8 *) SI__SIO_CFG)
    #define SI_SIO_DIFF           (* (reg8 *) SI__SIO_DIFF)
#endif /* (SI__SIO_CFG) */

/* Interrupt Registers */
#if defined(SI__INTSTAT)
    #define SI_INTSTAT            (* (reg8 *) SI__INTSTAT)
    #define SI_SNAP               (* (reg8 *) SI__SNAP)
    
	#define SI_0_INTTYPE_REG 		(* (reg8 *) SI__0__INTTYPE)
#endif /* (SI__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_SI_H */


/* [] END OF FILE */
