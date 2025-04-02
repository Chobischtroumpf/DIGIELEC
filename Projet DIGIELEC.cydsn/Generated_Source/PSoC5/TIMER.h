/*******************************************************************************
* File Name: TIMER.h
* Version 2.80
*
*  Description:
*     Contains the function prototypes and constants available to the timer
*     user module.
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#if !defined(CY_TIMER_TIMER_H)
#define CY_TIMER_TIMER_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h" /* For CyEnterCriticalSection() and CyExitCriticalSection() functions */

extern uint8 TIMER_initVar;

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component Timer_v2_80 requires cy_boot v3.0 or later
#endif /* (CY_ PSOC5LP) */


/**************************************
*           Parameter Defaults
**************************************/

#define TIMER_Resolution                 8u
#define TIMER_UsingFixedFunction         1u
#define TIMER_UsingHWCaptureCounter      0u
#define TIMER_SoftwareCaptureMode        0u
#define TIMER_SoftwareTriggerMode        0u
#define TIMER_UsingHWEnable              0u
#define TIMER_EnableTriggerMode          0u
#define TIMER_InterruptOnCaptureCount    0u
#define TIMER_RunModeUsed                0u
#define TIMER_ControlRegRemoved          0u

#if defined(TIMER_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG)
    #define TIMER_UDB_CONTROL_REG_REMOVED            (0u)
#elif  (TIMER_UsingFixedFunction)
    #define TIMER_UDB_CONTROL_REG_REMOVED            (0u)
#else 
    #define TIMER_UDB_CONTROL_REG_REMOVED            (1u)
#endif /* End TIMER_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG */


/***************************************
*       Type defines
***************************************/


/**************************************************************************
 * Sleep Wakeup Backup structure for Timer Component
 *************************************************************************/
typedef struct
{
    uint8 TimerEnableState;
    #if(!TIMER_UsingFixedFunction)

        uint8 TimerUdb;
        uint8 InterruptMaskValue;
        #if (TIMER_UsingHWCaptureCounter)
            uint8 TimerCaptureCounter;
        #endif /* variable declarations for backing up non retention registers in CY_UDB_V1 */

        #if (!TIMER_UDB_CONTROL_REG_REMOVED)
            uint8 TimerControlRegister;
        #endif /* variable declaration for backing up enable state of the Timer */
    #endif /* define backup variables only for UDB implementation. Fixed function registers are all retention */

}TIMER_backupStruct;


/***************************************
*       Function Prototypes
***************************************/

void    TIMER_Start(void) ;
void    TIMER_Stop(void) ;

void    TIMER_SetInterruptMode(uint8 interruptMode) ;
uint8   TIMER_ReadStatusRegister(void) ;
/* Deprecated function. Do not use this in future. Retained for backward compatibility */
#define TIMER_GetInterruptSource() TIMER_ReadStatusRegister()

#if(!TIMER_UDB_CONTROL_REG_REMOVED)
    uint8   TIMER_ReadControlRegister(void) ;
    void    TIMER_WriteControlRegister(uint8 control) ;
#endif /* (!TIMER_UDB_CONTROL_REG_REMOVED) */

uint8  TIMER_ReadPeriod(void) ;
void    TIMER_WritePeriod(uint8 period) ;
uint8  TIMER_ReadCounter(void) ;
void    TIMER_WriteCounter(uint8 counter) ;
uint8  TIMER_ReadCapture(void) ;
void    TIMER_SoftwareCapture(void) ;

#if(!TIMER_UsingFixedFunction) /* UDB Prototypes */
    #if (TIMER_SoftwareCaptureMode)
        void    TIMER_SetCaptureMode(uint8 captureMode) ;
    #endif /* (!TIMER_UsingFixedFunction) */

    #if (TIMER_SoftwareTriggerMode)
        void    TIMER_SetTriggerMode(uint8 triggerMode) ;
    #endif /* (TIMER_SoftwareTriggerMode) */

    #if (TIMER_EnableTriggerMode)
        void    TIMER_EnableTrigger(void) ;
        void    TIMER_DisableTrigger(void) ;
    #endif /* (TIMER_EnableTriggerMode) */


    #if(TIMER_InterruptOnCaptureCount)
        void    TIMER_SetInterruptCount(uint8 interruptCount) ;
    #endif /* (TIMER_InterruptOnCaptureCount) */

    #if (TIMER_UsingHWCaptureCounter)
        void    TIMER_SetCaptureCount(uint8 captureCount) ;
        uint8   TIMER_ReadCaptureCount(void) ;
    #endif /* (TIMER_UsingHWCaptureCounter) */

    void TIMER_ClearFIFO(void) ;
#endif /* UDB Prototypes */

/* Sleep Retention APIs */
void TIMER_Init(void)          ;
void TIMER_Enable(void)        ;
void TIMER_SaveConfig(void)    ;
void TIMER_RestoreConfig(void) ;
void TIMER_Sleep(void)         ;
void TIMER_Wakeup(void)        ;


/***************************************
*   Enumerated Types and Parameters
***************************************/

/* Enumerated Type B_Timer__CaptureModes, Used in Capture Mode */
#define TIMER__B_TIMER__CM_NONE 0
#define TIMER__B_TIMER__CM_RISINGEDGE 1
#define TIMER__B_TIMER__CM_FALLINGEDGE 2
#define TIMER__B_TIMER__CM_EITHEREDGE 3
#define TIMER__B_TIMER__CM_SOFTWARE 4



/* Enumerated Type B_Timer__TriggerModes, Used in Trigger Mode */
#define TIMER__B_TIMER__TM_NONE 0x00u
#define TIMER__B_TIMER__TM_RISINGEDGE 0x04u
#define TIMER__B_TIMER__TM_FALLINGEDGE 0x08u
#define TIMER__B_TIMER__TM_EITHEREDGE 0x0Cu
#define TIMER__B_TIMER__TM_SOFTWARE 0x10u


/***************************************
*    Initialial Parameter Constants
***************************************/

#define TIMER_INIT_PERIOD             255u
#define TIMER_INIT_CAPTURE_MODE       ((uint8)((uint8)1u << TIMER_CTRL_CAP_MODE_SHIFT))
#define TIMER_INIT_TRIGGER_MODE       ((uint8)((uint8)0u << TIMER_CTRL_TRIG_MODE_SHIFT))
#if (TIMER_UsingFixedFunction)
    #define TIMER_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TIMER_STATUS_TC_INT_MASK_SHIFT)) | \
                                                  ((uint8)((uint8)0 << TIMER_STATUS_CAPTURE_INT_MASK_SHIFT)))
#else
    #define TIMER_INIT_INTERRUPT_MODE (((uint8)((uint8)0u << TIMER_STATUS_TC_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TIMER_STATUS_CAPTURE_INT_MASK_SHIFT)) | \
                                                 ((uint8)((uint8)0 << TIMER_STATUS_FIFOFULL_INT_MASK_SHIFT)))
#endif /* (TIMER_UsingFixedFunction) */
#define TIMER_INIT_CAPTURE_COUNT      (2u)
#define TIMER_INIT_INT_CAPTURE_COUNT  ((uint8)((uint8)(1u - 1u) << TIMER_CTRL_INTCNT_SHIFT))


/***************************************
*           Registers
***************************************/

#if (TIMER_UsingFixedFunction) /* Implementation Specific Registers and Register Constants */


    /***************************************
    *    Fixed Function Registers
    ***************************************/

    #define TIMER_STATUS         (*(reg8 *) TIMER_TimerHW__SR0 )
    /* In Fixed Function Block Status and Mask are the same register */
    #define TIMER_STATUS_MASK    (*(reg8 *) TIMER_TimerHW__SR0 )
    #define TIMER_CONTROL        (*(reg8 *) TIMER_TimerHW__CFG0)
    #define TIMER_CONTROL2       (*(reg8 *) TIMER_TimerHW__CFG1)
    #define TIMER_CONTROL2_PTR   ( (reg8 *) TIMER_TimerHW__CFG1)
    #define TIMER_RT1            (*(reg8 *) TIMER_TimerHW__RT1)
    #define TIMER_RT1_PTR        ( (reg8 *) TIMER_TimerHW__RT1)

    #if (CY_PSOC3 || CY_PSOC5LP)
        #define TIMER_CONTROL3       (*(reg8 *) TIMER_TimerHW__CFG2)
        #define TIMER_CONTROL3_PTR   ( (reg8 *) TIMER_TimerHW__CFG2)
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */
    #define TIMER_GLOBAL_ENABLE  (*(reg8 *) TIMER_TimerHW__PM_ACT_CFG)
    #define TIMER_GLOBAL_STBY_ENABLE  (*(reg8 *) TIMER_TimerHW__PM_STBY_CFG)

    #define TIMER_CAPTURE_LSB         (* (reg16 *) TIMER_TimerHW__CAP0 )
    #define TIMER_CAPTURE_LSB_PTR       ((reg16 *) TIMER_TimerHW__CAP0 )
    #define TIMER_PERIOD_LSB          (* (reg16 *) TIMER_TimerHW__PER0 )
    #define TIMER_PERIOD_LSB_PTR        ((reg16 *) TIMER_TimerHW__PER0 )
    #define TIMER_COUNTER_LSB         (* (reg16 *) TIMER_TimerHW__CNT_CMP0 )
    #define TIMER_COUNTER_LSB_PTR       ((reg16 *) TIMER_TimerHW__CNT_CMP0 )


    /***************************************
    *    Register Constants
    ***************************************/

    /* Fixed Function Block Chosen */
    #define TIMER_BLOCK_EN_MASK                     TIMER_TimerHW__PM_ACT_MSK
    #define TIMER_BLOCK_STBY_EN_MASK                TIMER_TimerHW__PM_STBY_MSK

    /* Control Register Bit Locations */
    /* Interrupt Count - Not valid for Fixed Function Block */
    #define TIMER_CTRL_INTCNT_SHIFT                  0x00u
    /* Trigger Polarity - Not valid for Fixed Function Block */
    #define TIMER_CTRL_TRIG_MODE_SHIFT               0x00u
    /* Trigger Enable - Not valid for Fixed Function Block */
    #define TIMER_CTRL_TRIG_EN_SHIFT                 0x00u
    /* Capture Polarity - Not valid for Fixed Function Block */
    #define TIMER_CTRL_CAP_MODE_SHIFT                0x00u
    /* Timer Enable - As defined in Register Map, part of TMRX_CFG0 register */
    #define TIMER_CTRL_ENABLE_SHIFT                  0x00u

    /* Control Register Bit Masks */
    #define TIMER_CTRL_ENABLE                        ((uint8)((uint8)0x01u << TIMER_CTRL_ENABLE_SHIFT))

    /* Control2 Register Bit Masks */
    /* As defined in Register Map, Part of the TMRX_CFG1 register */
    #define TIMER_CTRL2_IRQ_SEL_SHIFT                 0x00u
    #define TIMER_CTRL2_IRQ_SEL                      ((uint8)((uint8)0x01u << TIMER_CTRL2_IRQ_SEL_SHIFT))

    #if (CY_PSOC5A)
        /* Use CFG1 Mode bits to set run mode */
        /* As defined by Verilog Implementation */
        #define TIMER_CTRL_MODE_SHIFT                 0x01u
        #define TIMER_CTRL_MODE_MASK                 ((uint8)((uint8)0x07u << TIMER_CTRL_MODE_SHIFT))
    #endif /* (CY_PSOC5A) */
    #if (CY_PSOC3 || CY_PSOC5LP)
        /* Control3 Register Bit Locations */
        #define TIMER_CTRL_RCOD_SHIFT        0x02u
        #define TIMER_CTRL_ENBL_SHIFT        0x00u
        #define TIMER_CTRL_MODE_SHIFT        0x00u

        /* Control3 Register Bit Masks */
        #define TIMER_CTRL_RCOD_MASK  ((uint8)((uint8)0x03u << TIMER_CTRL_RCOD_SHIFT)) /* ROD and COD bit masks */
        #define TIMER_CTRL_ENBL_MASK  ((uint8)((uint8)0x80u << TIMER_CTRL_ENBL_SHIFT)) /* HW_EN bit mask */
        #define TIMER_CTRL_MODE_MASK  ((uint8)((uint8)0x03u << TIMER_CTRL_MODE_SHIFT)) /* Run mode bit mask */

        #define TIMER_CTRL_RCOD       ((uint8)((uint8)0x03u << TIMER_CTRL_RCOD_SHIFT))
        #define TIMER_CTRL_ENBL       ((uint8)((uint8)0x80u << TIMER_CTRL_ENBL_SHIFT))
    #endif /* (CY_PSOC3 || CY_PSOC5LP) */

    /*RT1 Synch Constants: Applicable for PSoC3 and PSoC5LP */
    #define TIMER_RT1_SHIFT                       0x04u
    /* Sync TC and CMP bit masks */
    #define TIMER_RT1_MASK                        ((uint8)((uint8)0x03u << TIMER_RT1_SHIFT))
    #define TIMER_SYNC                            ((uint8)((uint8)0x03u << TIMER_RT1_SHIFT))
    #define TIMER_SYNCDSI_SHIFT                   0x00u
    /* Sync all DSI inputs with Mask  */
    #define TIMER_SYNCDSI_MASK                    ((uint8)((uint8)0x0Fu << TIMER_SYNCDSI_SHIFT))
    /* Sync all DSI inputs */
    #define TIMER_SYNCDSI_EN                      ((uint8)((uint8)0x0Fu << TIMER_SYNCDSI_SHIFT))

    #define TIMER_CTRL_MODE_PULSEWIDTH            ((uint8)((uint8)0x01u << TIMER_CTRL_MODE_SHIFT))
    #define TIMER_CTRL_MODE_PERIOD                ((uint8)((uint8)0x02u << TIMER_CTRL_MODE_SHIFT))
    #define TIMER_CTRL_MODE_CONTINUOUS            ((uint8)((uint8)0x00u << TIMER_CTRL_MODE_SHIFT))

    /* Status Register Bit Locations */
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TIMER_STATUS_TC_SHIFT                 0x07u
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TIMER_STATUS_CAPTURE_SHIFT            0x06u
    /* As defined in Register Map, part of TMRX_SR0 register */
    #define TIMER_STATUS_TC_INT_MASK_SHIFT        (TIMER_STATUS_TC_SHIFT - 0x04u)
    /* As defined in Register Map, part of TMRX_SR0 register, Shared with Compare Status */
    #define TIMER_STATUS_CAPTURE_INT_MASK_SHIFT   (TIMER_STATUS_CAPTURE_SHIFT - 0x04u)

    /* Status Register Bit Masks */
    #define TIMER_STATUS_TC                       ((uint8)((uint8)0x01u << TIMER_STATUS_TC_SHIFT))
    #define TIMER_STATUS_CAPTURE                  ((uint8)((uint8)0x01u << TIMER_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on TC */
    #define TIMER_STATUS_TC_INT_MASK              ((uint8)((uint8)0x01u << TIMER_STATUS_TC_INT_MASK_SHIFT))
    /* Interrupt Enable Bit-Mask for interrupt on Capture */
    #define TIMER_STATUS_CAPTURE_INT_MASK         ((uint8)((uint8)0x01u << TIMER_STATUS_CAPTURE_INT_MASK_SHIFT))

#else   /* UDB Registers and Register Constants */


    /***************************************
    *           UDB Registers
    ***************************************/

    #define TIMER_STATUS              (* (reg8 *) TIMER_TimerUDB_rstSts_stsreg__STATUS_REG )
    #define TIMER_STATUS_MASK         (* (reg8 *) TIMER_TimerUDB_rstSts_stsreg__MASK_REG)
    #define TIMER_STATUS_AUX_CTRL     (* (reg8 *) TIMER_TimerUDB_rstSts_stsreg__STATUS_AUX_CTL_REG)
    #define TIMER_CONTROL             (* (reg8 *) TIMER_TimerUDB_sCTRLReg_SyncCtl_ctrlreg__CONTROL_REG )
    
    #if(TIMER_Resolution <= 8u) /* 8-bit Timer */
        #define TIMER_CAPTURE_LSB         (* (reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TIMER_CAPTURE_LSB_PTR       ((reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TIMER_PERIOD_LSB          (* (reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TIMER_PERIOD_LSB_PTR        ((reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TIMER_COUNTER_LSB         (* (reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TIMER_COUNTER_LSB_PTR       ((reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
    #elif(TIMER_Resolution <= 16u) /* 8-bit Timer */
        #if(CY_PSOC3) /* 8-bit addres space */
            #define TIMER_CAPTURE_LSB         (* (reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TIMER_CAPTURE_LSB_PTR       ((reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TIMER_PERIOD_LSB          (* (reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TIMER_PERIOD_LSB_PTR        ((reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TIMER_COUNTER_LSB         (* (reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TIMER_COUNTER_LSB_PTR       ((reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 16-bit address space */
            #define TIMER_CAPTURE_LSB         (* (reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TIMER_CAPTURE_LSB_PTR       ((reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__16BIT_F0_REG )
            #define TIMER_PERIOD_LSB          (* (reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TIMER_PERIOD_LSB_PTR        ((reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__16BIT_D0_REG )
            #define TIMER_COUNTER_LSB         (* (reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
            #define TIMER_COUNTER_LSB_PTR       ((reg16 *) TIMER_TimerUDB_sT8_timerdp_u0__16BIT_A0_REG )
        #endif /* CY_PSOC3 */
    #elif(TIMER_Resolution <= 24u)/* 24-bit Timer */
        #define TIMER_CAPTURE_LSB         (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TIMER_CAPTURE_LSB_PTR       ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
        #define TIMER_PERIOD_LSB          (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TIMER_PERIOD_LSB_PTR        ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
        #define TIMER_COUNTER_LSB         (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
        #define TIMER_COUNTER_LSB_PTR       ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
    #else /* 32-bit Timer */
        #if(CY_PSOC3 || CY_PSOC5) /* 8-bit address space */
            #define TIMER_CAPTURE_LSB         (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TIMER_CAPTURE_LSB_PTR       ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__F0_REG )
            #define TIMER_PERIOD_LSB          (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TIMER_PERIOD_LSB_PTR        ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__D0_REG )
            #define TIMER_COUNTER_LSB         (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
            #define TIMER_COUNTER_LSB_PTR       ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
        #else /* 32-bit address space */
            #define TIMER_CAPTURE_LSB         (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TIMER_CAPTURE_LSB_PTR       ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__32BIT_F0_REG )
            #define TIMER_PERIOD_LSB          (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TIMER_PERIOD_LSB_PTR        ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__32BIT_D0_REG )
            #define TIMER_COUNTER_LSB         (* (reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
            #define TIMER_COUNTER_LSB_PTR       ((reg32 *) TIMER_TimerUDB_sT8_timerdp_u0__32BIT_A0_REG )
        #endif /* CY_PSOC3 || CY_PSOC5 */ 
    #endif

    #define TIMER_COUNTER_LSB_PTR_8BIT       ((reg8 *) TIMER_TimerUDB_sT8_timerdp_u0__A0_REG )
    
    #if (TIMER_UsingHWCaptureCounter)
        #define TIMER_CAP_COUNT              (*(reg8 *) TIMER_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TIMER_CAP_COUNT_PTR          ( (reg8 *) TIMER_TimerUDB_sCapCount_counter__PERIOD_REG )
        #define TIMER_CAPTURE_COUNT_CTRL     (*(reg8 *) TIMER_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
        #define TIMER_CAPTURE_COUNT_CTRL_PTR ( (reg8 *) TIMER_TimerUDB_sCapCount_counter__CONTROL_AUX_CTL_REG )
    #endif /* (TIMER_UsingHWCaptureCounter) */


    /***************************************
    *       Register Constants
    ***************************************/

    /* Control Register Bit Locations */
    #define TIMER_CTRL_INTCNT_SHIFT              0x00u       /* As defined by Verilog Implementation */
    #define TIMER_CTRL_TRIG_MODE_SHIFT           0x02u       /* As defined by Verilog Implementation */
    #define TIMER_CTRL_TRIG_EN_SHIFT             0x04u       /* As defined by Verilog Implementation */
    #define TIMER_CTRL_CAP_MODE_SHIFT            0x05u       /* As defined by Verilog Implementation */
    #define TIMER_CTRL_ENABLE_SHIFT              0x07u       /* As defined by Verilog Implementation */

    /* Control Register Bit Masks */
    #define TIMER_CTRL_INTCNT_MASK               ((uint8)((uint8)0x03u << TIMER_CTRL_INTCNT_SHIFT))
    #define TIMER_CTRL_TRIG_MODE_MASK            ((uint8)((uint8)0x03u << TIMER_CTRL_TRIG_MODE_SHIFT))
    #define TIMER_CTRL_TRIG_EN                   ((uint8)((uint8)0x01u << TIMER_CTRL_TRIG_EN_SHIFT))
    #define TIMER_CTRL_CAP_MODE_MASK             ((uint8)((uint8)0x03u << TIMER_CTRL_CAP_MODE_SHIFT))
    #define TIMER_CTRL_ENABLE                    ((uint8)((uint8)0x01u << TIMER_CTRL_ENABLE_SHIFT))

    /* Bit Counter (7-bit) Control Register Bit Definitions */
    /* As defined by the Register map for the AUX Control Register */
    #define TIMER_CNTR_ENABLE                    0x20u

    /* Status Register Bit Locations */
    #define TIMER_STATUS_TC_SHIFT                0x00u  /* As defined by Verilog Implementation */
    #define TIMER_STATUS_CAPTURE_SHIFT           0x01u  /* As defined by Verilog Implementation */
    #define TIMER_STATUS_TC_INT_MASK_SHIFT       TIMER_STATUS_TC_SHIFT
    #define TIMER_STATUS_CAPTURE_INT_MASK_SHIFT  TIMER_STATUS_CAPTURE_SHIFT
    #define TIMER_STATUS_FIFOFULL_SHIFT          0x02u  /* As defined by Verilog Implementation */
    #define TIMER_STATUS_FIFONEMP_SHIFT          0x03u  /* As defined by Verilog Implementation */
    #define TIMER_STATUS_FIFOFULL_INT_MASK_SHIFT TIMER_STATUS_FIFOFULL_SHIFT

    /* Status Register Bit Masks */
    /* Sticky TC Event Bit-Mask */
    #define TIMER_STATUS_TC                      ((uint8)((uint8)0x01u << TIMER_STATUS_TC_SHIFT))
    /* Sticky Capture Event Bit-Mask */
    #define TIMER_STATUS_CAPTURE                 ((uint8)((uint8)0x01u << TIMER_STATUS_CAPTURE_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TIMER_STATUS_TC_INT_MASK             ((uint8)((uint8)0x01u << TIMER_STATUS_TC_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TIMER_STATUS_CAPTURE_INT_MASK        ((uint8)((uint8)0x01u << TIMER_STATUS_CAPTURE_SHIFT))
    /* NOT-Sticky FIFO Full Bit-Mask */
    #define TIMER_STATUS_FIFOFULL                ((uint8)((uint8)0x01u << TIMER_STATUS_FIFOFULL_SHIFT))
    /* NOT-Sticky FIFO Not Empty Bit-Mask */
    #define TIMER_STATUS_FIFONEMP                ((uint8)((uint8)0x01u << TIMER_STATUS_FIFONEMP_SHIFT))
    /* Interrupt Enable Bit-Mask */
    #define TIMER_STATUS_FIFOFULL_INT_MASK       ((uint8)((uint8)0x01u << TIMER_STATUS_FIFOFULL_SHIFT))

    #define TIMER_STATUS_ACTL_INT_EN             0x10u   /* As defined for the ACTL Register */

    /* Datapath Auxillary Control Register definitions */
    #define TIMER_AUX_CTRL_FIFO0_CLR             0x01u   /* As defined by Register map */
    #define TIMER_AUX_CTRL_FIFO1_CLR             0x02u   /* As defined by Register map */
    #define TIMER_AUX_CTRL_FIFO0_LVL             0x04u   /* As defined by Register map */
    #define TIMER_AUX_CTRL_FIFO1_LVL             0x08u   /* As defined by Register map */
    #define TIMER_STATUS_ACTL_INT_EN_MASK        0x10u   /* As defined for the ACTL Register */

#endif /* Implementation Specific Registers and Register Constants */

#endif  /* CY_TIMER_TIMER_H */


/* [] END OF FILE */
