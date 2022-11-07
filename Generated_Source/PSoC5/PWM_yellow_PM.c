/*******************************************************************************
* File Name: PWM_yellow_PM.c
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

#include "PWM_yellow.h"

static PWM_yellow_backupStruct PWM_yellow_backup;


/*******************************************************************************
* Function Name: PWM_yellow_SaveConfig
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
*  PWM_yellow_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void PWM_yellow_SaveConfig(void) 
{

    #if(!PWM_yellow_UsingFixedFunction)
        #if(!PWM_yellow_PWMModeIsCenterAligned)
            PWM_yellow_backup.PWMPeriod = PWM_yellow_ReadPeriod();
        #endif /* (!PWM_yellow_PWMModeIsCenterAligned) */
        PWM_yellow_backup.PWMUdb = PWM_yellow_ReadCounter();
        #if (PWM_yellow_UseStatus)
            PWM_yellow_backup.InterruptMaskValue = PWM_yellow_STATUS_MASK;
        #endif /* (PWM_yellow_UseStatus) */

        #if(PWM_yellow_DeadBandMode == PWM_yellow__B_PWM__DBM_256_CLOCKS || \
            PWM_yellow_DeadBandMode == PWM_yellow__B_PWM__DBM_2_4_CLOCKS)
            PWM_yellow_backup.PWMdeadBandValue = PWM_yellow_ReadDeadTime();
        #endif /*  deadband count is either 2-4 clocks or 256 clocks */

        #if(PWM_yellow_KillModeMinTime)
             PWM_yellow_backup.PWMKillCounterPeriod = PWM_yellow_ReadKillTime();
        #endif /* (PWM_yellow_KillModeMinTime) */

        #if(PWM_yellow_UseControl)
            PWM_yellow_backup.PWMControlRegister = PWM_yellow_ReadControlRegister();
        #endif /* (PWM_yellow_UseControl) */
    #endif  /* (!PWM_yellow_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: PWM_yellow_RestoreConfig
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
*  PWM_yellow_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_yellow_RestoreConfig(void) 
{
        #if(!PWM_yellow_UsingFixedFunction)
            #if(!PWM_yellow_PWMModeIsCenterAligned)
                PWM_yellow_WritePeriod(PWM_yellow_backup.PWMPeriod);
            #endif /* (!PWM_yellow_PWMModeIsCenterAligned) */

            PWM_yellow_WriteCounter(PWM_yellow_backup.PWMUdb);

            #if (PWM_yellow_UseStatus)
                PWM_yellow_STATUS_MASK = PWM_yellow_backup.InterruptMaskValue;
            #endif /* (PWM_yellow_UseStatus) */

            #if(PWM_yellow_DeadBandMode == PWM_yellow__B_PWM__DBM_256_CLOCKS || \
                PWM_yellow_DeadBandMode == PWM_yellow__B_PWM__DBM_2_4_CLOCKS)
                PWM_yellow_WriteDeadTime(PWM_yellow_backup.PWMdeadBandValue);
            #endif /* deadband count is either 2-4 clocks or 256 clocks */

            #if(PWM_yellow_KillModeMinTime)
                PWM_yellow_WriteKillTime(PWM_yellow_backup.PWMKillCounterPeriod);
            #endif /* (PWM_yellow_KillModeMinTime) */

            #if(PWM_yellow_UseControl)
                PWM_yellow_WriteControlRegister(PWM_yellow_backup.PWMControlRegister);
            #endif /* (PWM_yellow_UseControl) */
        #endif  /* (!PWM_yellow_UsingFixedFunction) */
    }


/*******************************************************************************
* Function Name: PWM_yellow_Sleep
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
*  PWM_yellow_backup.PWMEnableState:  Is modified depending on the enable
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void PWM_yellow_Sleep(void) 
{
    #if(PWM_yellow_UseControl)
        if(PWM_yellow_CTRL_ENABLE == (PWM_yellow_CONTROL & PWM_yellow_CTRL_ENABLE))
        {
            /*Component is enabled */
            PWM_yellow_backup.PWMEnableState = 1u;
        }
        else
        {
            /* Component is disabled */
            PWM_yellow_backup.PWMEnableState = 0u;
        }
    #endif /* (PWM_yellow_UseControl) */

    /* Stop component */
    PWM_yellow_Stop();

    /* Save registers configuration */
    PWM_yellow_SaveConfig();
}


/*******************************************************************************
* Function Name: PWM_yellow_Wakeup
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
*  PWM_yellow_backup.pwmEnable:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void PWM_yellow_Wakeup(void) 
{
     /* Restore registers values */
    PWM_yellow_RestoreConfig();

    if(PWM_yellow_backup.PWMEnableState != 0u)
    {
        /* Enable component's operation */
        PWM_yellow_Enable();
    } /* Do nothing if component's block was disabled before */

}


/* [] END OF FILE */
