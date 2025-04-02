/*******************************************************************************
* File Name: PWM_DROITE_PM.c
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

#include "PWM_DROITE.h"

static PWM_DROITE_backupStruct PWM_DROITE_backup;


/*******************************************************************************
* Function Name: PWM_DROITE_SaveConfig
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
*  PWM_DROITE_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_DROITE_SaveConfig(void) 
{

    #if(!PWM_DROITE_UsingFixedFunction)
        #if(!PWM_DROITE_PWMModeIsCenterAligned)
            PWM_DROITE_backup.PWMPeriod = PWM_DROITE_ReadPeriod();
        #endif /* (!PWM_DROITE_PWMModeIsCenterAligned) */
        PWM_DROITE_backup.PWMUdb = PWM_DROITE_ReadCounter();
        #if (PWM_DROITE_UseStatus)
            PWM_DROITE_backup.InterruptMaskValue = PWM_DROITE_STATUS_MASK;
        #endif /* (PWM_DROITE_UseStatus) */

        #if(PWM_DROITE_DeadBandMode == PWM_DROITE__B_PWM__DBM_256_CLOCKS || \
            PWM_DROITE_DeadBandMode == PWM_DROITE__B_PWM__DBM_2_4_CLOCKS)
            PWM_DROITE_backup.PWMdeadBandValue = PWM_DROITE_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_DROITE_KillModeMinTime)
             PWM_DROITE_backup.PWMKillCounterPeriod = PWM_DROITE_ReadKillTime();
        #endif /* (PWM_DROITE_KillModeMinTime) */

        #if(PWM_DROITE_UseControl)
            PWM_DROITE_backup.PWMControlRegister = PWM_DROITE_ReadControlRegister();
        #endif /* (PWM_DROITE_UseControl) */
    #endif  /* (!PWM_DROITE_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_DROITE_RestoreConfig
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
*  PWM_DROITE_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_DROITE_RestoreConfig(void) 
{
        #if(!PWM_DROITE_UsingFixedFunction)
            #if(!PWM_DROITE_PWMModeIsCenterAligned)
                PWM_DROITE_WritePeriod(PWM_DROITE_backup.PWMPeriod);
            #endif /* (!PWM_DROITE_PWMModeIsCenterAligned) */

            PWM_DROITE_WriteCounter(PWM_DROITE_backup.PWMUdb);

            #if (PWM_DROITE_UseStatus)
                PWM_DROITE_STATUS_MASK = PWM_DROITE_backup.InterruptMaskValue;
            #endif /* (PWM_DROITE_UseStatus) */

            #if(PWM_DROITE_DeadBandMode == PWM_DROITE__B_PWM__DBM_256_CLOCKS || \
                PWM_DROITE_DeadBandMode == PWM_DROITE__B_PWM__DBM_2_4_CLOCKS)
                PWM_DROITE_WriteDeadTime(PWM_DROITE_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_DROITE_KillModeMinTime)
                PWM_DROITE_WriteKillTime(PWM_DROITE_backup.PWMKillCounterPeriod);
            #endif /* (PWM_DROITE_KillModeMinTime) */

            #if(PWM_DROITE_UseControl)
                PWM_DROITE_WriteControlRegister(PWM_DROITE_backup.PWMControlRegister);
            #endif /* (PWM_DROITE_UseControl) */
        #endif  /* (!PWM_DROITE_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_DROITE_Sleep
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
*  PWM_DROITE_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_DROITE_Sleep(void) 
{
    #if(PWM_DROITE_UseControl)
        if(PWM_DROITE_CTRL_ENABLE == (PWM_DROITE_CONTROL & PWM_DROITE_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_DROITE_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_DROITE_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_DROITE_UseControl) */

    /* Stop component */
    PWM_DROITE_Stop();

    /* Save registers configuration */
    PWM_DROITE_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_DROITE_Wakeup
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
*  PWM_DROITE_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_DROITE_Wakeup(void) 
{
     /* Restore registers values */
    PWM_DROITE_RestoreConfig();

    if(PWM_DROITE_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_DROITE_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
