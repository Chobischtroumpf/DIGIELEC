/*******************************************************************************
* File Name: PWM_GAUCHE_PM.c
* Version 3.30
*
* Description:
*  This file provides the power management source code to API for the
*  PWM.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "PWM_GAUCHE.h"

static PWM_GAUCHE_backupStruct PWM_GAUCHE_backup;


/*******************************************************************************
* Function Name: PWM_GAUCHE_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GAUCHE_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_GAUCHE_SaveConfig(void) 
{

    #if(!PWM_GAUCHE_UsingFixedFunction)
        #if(!PWM_GAUCHE_PWMModeIsCenterAligned)
            PWM_GAUCHE_backup.PWMPeriod = PWM_GAUCHE_ReadPeriod();
        #endif /* (!PWM_GAUCHE_PWMModeIsCenterAligned) */
        PWM_GAUCHE_backup.PWMUdb = PWM_GAUCHE_ReadCounter();
        #if (PWM_GAUCHE_UseStatus)
            PWM_GAUCHE_backup.InterruptMaskValue = PWM_GAUCHE_STATUS_MASK;
        #endif /* (PWM_GAUCHE_UseStatus) */

        #if(PWM_GAUCHE_DeadBandMode == PWM_GAUCHE__B_PWM__DBM_256_CLOCKS || \
            PWM_GAUCHE_DeadBandMode == PWM_GAUCHE__B_PWM__DBM_2_4_CLOCKS)
            PWM_GAUCHE_backup.PWMdeadBandValue = PWM_GAUCHE_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_GAUCHE_KillModeMinTime)
             PWM_GAUCHE_backup.PWMKillCounterPeriod = PWM_GAUCHE_ReadKillTime();
        #endif /* (PWM_GAUCHE_KillModeMinTime) */

        #if(PWM_GAUCHE_UseControl)
            PWM_GAUCHE_backup.PWMControlRegister = PWM_GAUCHE_ReadControlRegister();
        #endif /* (PWM_GAUCHE_UseControl) */
    #endif  /* (!PWM_GAUCHE_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_GAUCHE_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration of the component.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GAUCHE_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GAUCHE_RestoreConfig(void) 
{
        #if(!PWM_GAUCHE_UsingFixedFunction)
            #if(!PWM_GAUCHE_PWMModeIsCenterAligned)
                PWM_GAUCHE_WritePeriod(PWM_GAUCHE_backup.PWMPeriod);
            #endif /* (!PWM_GAUCHE_PWMModeIsCenterAligned) */

            PWM_GAUCHE_WriteCounter(PWM_GAUCHE_backup.PWMUdb);

            #if (PWM_GAUCHE_UseStatus)
                PWM_GAUCHE_STATUS_MASK = PWM_GAUCHE_backup.InterruptMaskValue;
            #endif /* (PWM_GAUCHE_UseStatus) */

            #if(PWM_GAUCHE_DeadBandMode == PWM_GAUCHE__B_PWM__DBM_256_CLOCKS || \
                PWM_GAUCHE_DeadBandMode == PWM_GAUCHE__B_PWM__DBM_2_4_CLOCKS)
                PWM_GAUCHE_WriteDeadTime(PWM_GAUCHE_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_GAUCHE_KillModeMinTime)
                PWM_GAUCHE_WriteKillTime(PWM_GAUCHE_backup.PWMKillCounterPeriod);
            #endif /* (PWM_GAUCHE_KillModeMinTime) */

            #if(PWM_GAUCHE_UseControl)
                PWM_GAUCHE_WriteControlRegister(PWM_GAUCHE_backup.PWMControlRegister);
            #endif /* (PWM_GAUCHE_UseControl) */
        #endif  /* (!PWM_GAUCHE_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_GAUCHE_Sleep
********************************************************************************
*
* Summary:
*  Disables block's operation and saves the user configuration. Should be called
*  just prior to entering sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GAUCHE_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_GAUCHE_Sleep(void) 
{
    #if(PWM_GAUCHE_UseControl)
        if(PWM_GAUCHE_CTRL_ENABLE == (PWM_GAUCHE_CONTROL & PWM_GAUCHE_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_GAUCHE_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_GAUCHE_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_GAUCHE_UseControl) */

    /* Stop component */
    PWM_GAUCHE_Stop();

    /* Save registers configuration */
    PWM_GAUCHE_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_GAUCHE_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration. Should be called just after
*  awaking from sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  PWM_GAUCHE_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_GAUCHE_Wakeup(void) 
{
     /* Restore registers values */
    PWM_GAUCHE_RestoreConfig();

    if(PWM_GAUCHE_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_GAUCHE_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
