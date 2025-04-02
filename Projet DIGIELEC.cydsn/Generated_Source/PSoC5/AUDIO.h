/*******************************************************************************
* File Name: AUDIO.h  
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

#if !defined(CY_PINS_AUDIO_H) /* Pins AUDIO_H */
#define CY_PINS_AUDIO_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"
#include "AUDIO_aliases.h"

/* APIs are not generated for P15[7:6] */
#if !(CY_PSOC5A &&\
	 AUDIO__PORT == 15 && ((AUDIO__MASK & 0xC0) != 0))


/***************************************
*        Function Prototypes             
***************************************/    

/**
* \addtogroup group_general
* @{
*/
void    AUDIO_Write(uint8 value);
void    AUDIO_SetDriveMode(uint8 mode);
uint8   AUDIO_ReadDataReg(void);
uint8   AUDIO_Read(void);
void    AUDIO_SetInterruptMode(uint16 position, uint16 mode);
uint8   AUDIO_ClearInterrupt(void);
/** @} general */

/***************************************
*           API Constants        
***************************************/
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup driveMode Drive mode constants
     * \brief Constants to be passed as "mode" parameter in the AUDIO_SetDriveMode() function.
     *  @{
     */
        #define AUDIO_DM_ALG_HIZ         PIN_DM_ALG_HIZ
        #define AUDIO_DM_DIG_HIZ         PIN_DM_DIG_HIZ
        #define AUDIO_DM_RES_UP          PIN_DM_RES_UP
        #define AUDIO_DM_RES_DWN         PIN_DM_RES_DWN
        #define AUDIO_DM_OD_LO           PIN_DM_OD_LO
        #define AUDIO_DM_OD_HI           PIN_DM_OD_HI
        #define AUDIO_DM_STRONG          PIN_DM_STRONG
        #define AUDIO_DM_RES_UPDWN       PIN_DM_RES_UPDWN
    /** @} driveMode */
/** @} group_constants */
    
/* Digital Port Constants */
#define AUDIO_MASK               AUDIO__MASK
#define AUDIO_SHIFT              AUDIO__SHIFT
#define AUDIO_WIDTH              1u

/* Interrupt constants */
#if defined(AUDIO__INTSTAT)
/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AUDIO_SetInterruptMode() function.
     *  @{
     */
        #define AUDIO_INTR_NONE      (uint16)(0x0000u)
        #define AUDIO_INTR_RISING    (uint16)(0x0001u)
        #define AUDIO_INTR_FALLING   (uint16)(0x0002u)
        #define AUDIO_INTR_BOTH      (uint16)(0x0003u) 
    /** @} intrMode */
/** @} group_constants */

    #define AUDIO_INTR_MASK      (0x01u) 
#endif /* (AUDIO__INTSTAT) */


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define AUDIO_PS                     (* (reg8 *) AUDIO__PS)
/* Data Register */
#define AUDIO_DR                     (* (reg8 *) AUDIO__DR)
/* Port Number */
#define AUDIO_PRT_NUM                (* (reg8 *) AUDIO__PRT) 
/* Connect to Analog Globals */                                                  
#define AUDIO_AG                     (* (reg8 *) AUDIO__AG)                       
/* Analog MUX bux enable */
#define AUDIO_AMUX                   (* (reg8 *) AUDIO__AMUX) 
/* Bidirectional Enable */                                                        
#define AUDIO_BIE                    (* (reg8 *) AUDIO__BIE)
/* Bit-mask for Aliased Register Access */
#define AUDIO_BIT_MASK               (* (reg8 *) AUDIO__BIT_MASK)
/* Bypass Enable */
#define AUDIO_BYP                    (* (reg8 *) AUDIO__BYP)
/* Port wide control signals */                                                   
#define AUDIO_CTL                    (* (reg8 *) AUDIO__CTL)
/* Drive Modes */
#define AUDIO_DM0                    (* (reg8 *) AUDIO__DM0) 
#define AUDIO_DM1                    (* (reg8 *) AUDIO__DM1)
#define AUDIO_DM2                    (* (reg8 *) AUDIO__DM2) 
/* Input Buffer Disable Override */
#define AUDIO_INP_DIS                (* (reg8 *) AUDIO__INP_DIS)
/* LCD Common or Segment Drive */
#define AUDIO_LCD_COM_SEG            (* (reg8 *) AUDIO__LCD_COM_SEG)
/* Enable Segment LCD */
#define AUDIO_LCD_EN                 (* (reg8 *) AUDIO__LCD_EN)
/* Slew Rate Control */
#define AUDIO_SLW                    (* (reg8 *) AUDIO__SLW)

/* DSI Port Registers */
/* Global DSI Select Register */
#define AUDIO_PRTDSI__CAPS_SEL       (* (reg8 *) AUDIO__PRTDSI__CAPS_SEL) 
/* Double Sync Enable */
#define AUDIO_PRTDSI__DBL_SYNC_IN    (* (reg8 *) AUDIO__PRTDSI__DBL_SYNC_IN) 
/* Output Enable Select Drive Strength */
#define AUDIO_PRTDSI__OE_SEL0        (* (reg8 *) AUDIO__PRTDSI__OE_SEL0) 
#define AUDIO_PRTDSI__OE_SEL1        (* (reg8 *) AUDIO__PRTDSI__OE_SEL1) 
/* Port Pin Output Select Registers */
#define AUDIO_PRTDSI__OUT_SEL0       (* (reg8 *) AUDIO__PRTDSI__OUT_SEL0) 
#define AUDIO_PRTDSI__OUT_SEL1       (* (reg8 *) AUDIO__PRTDSI__OUT_SEL1) 
/* Sync Output Enable Registers */
#define AUDIO_PRTDSI__SYNC_OUT       (* (reg8 *) AUDIO__PRTDSI__SYNC_OUT) 

/* SIO registers */
#if defined(AUDIO__SIO_CFG)
    #define AUDIO_SIO_HYST_EN        (* (reg8 *) AUDIO__SIO_HYST_EN)
    #define AUDIO_SIO_REG_HIFREQ     (* (reg8 *) AUDIO__SIO_REG_HIFREQ)
    #define AUDIO_SIO_CFG            (* (reg8 *) AUDIO__SIO_CFG)
    #define AUDIO_SIO_DIFF           (* (reg8 *) AUDIO__SIO_DIFF)
#endif /* (AUDIO__SIO_CFG) */

/* Interrupt Registers */
#if defined(AUDIO__INTSTAT)
    #define AUDIO_INTSTAT            (* (reg8 *) AUDIO__INTSTAT)
    #define AUDIO_SNAP               (* (reg8 *) AUDIO__SNAP)
    
	#define AUDIO_0_INTTYPE_REG 		(* (reg8 *) AUDIO__0__INTTYPE)
#endif /* (AUDIO__INTSTAT) */

#endif /* CY_PSOC5A... */

#endif /*  CY_PINS_AUDIO_H */


/* [] END OF FILE */
