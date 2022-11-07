/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "global.h"
#include "button.h"
#include "led.h"
#include "seven.h"
#include "joystick.h"
#include "logging.h"
#include "watchdog.h"

#include "rte.h"
#include "rte_activation.h"
#include "rte_signalpool.h"
#include "tft.h"


//ISR which will increment the systick counter every ms
ISR(systick_handler)
{
    CounterTick(cnt_systick); //application counter
}


int main()
{
    CyGlobalIntEnable; /* Enable global interrupts. */
   
    //Set systick period to 1 ms. Enable the INT and start it.
	EE_systick_set_period(MILLISECONDS_TO_TICKS(1, BCLK__BUS_CLK__HZ));
	EE_systick_enable_int();
	EE_systick_start();
   
    // Start Operating System
    StartOS(OSDEFAULTAPPMODE);
    for(;;)
    {
        asm("bkpt");   
    }

}

void unhandledException()
{
    //Ooops, something terrible happened....check the call stack to see how we got here...
    asm("bkpt");
}

/********************************************************************************
 * Task Definitions
 ********************************************************************************/

TASK(tsk_Init)
{  
    //Init MCAL Drivers
    UART_LOG_Start();
    LED_Init();

    //Reconfigure ISRs with OS parameters.
    //This line MUST be called after the hardware driver initialisation!
    EE_system_init();
    
    //LOG_I("tsk_Init", "Starting...\n");
    
    //Start the alarm with 100ms cycle time
    SetRelAlarm(alrm_1ms,1,1);
    
    
    //Activate the remaining tasks

    ActivateTask(tsk_EventDispatcher);
    //ActivateTask(tsk_CyclicDispatcher);
    ActivateTask(tsk_Background);
    
    TerminateTask();
    
}

TASK(tsk_Background)
{
    while(1)
    {
        //do something with low prioroty
        asm("nop");
    }
}

TASK(tsk_CyclicDispatcher)
{        
        RTE_timertick();   
        
        RTE_ProcessCyclicTable(RTE_cyclicActivationTable, RTE_cyclicActivation_size, 1);
        //LOG_I("tsk_EventDispatcher","");
        
}


TASK(tsk_EventDispatcher)
{
    char value[100];
    uint8_t counter=0;
    EventMaskType ev = 0;
    
    while(1)
    {
        
        //Wait, read and clear the event
        WaitEvent(RTE_EVENTMASK);
        GetEvent(tsk_EventDispatcher,&ev);
        ClearEvent(ev);
        //LOG_I("tsk_EventDispatcher","");    
        //Process all events from the mask
        RTE_ProcessEventTable(RTE_eventActivationTable, RTE_eventActivation_size, ev);   
        
    }
}


/********************************************************************************
 * ISR Definitions
 ********************************************************************************/
    
ISR2(isr_Button)
{
    LED_Set(LED_GREEN,LED_ON);
    isr_Button_ClearPending();      
    if (TRUE == BUTTON_IsPressed(BUTTON_1)) LOG_I("BUTTON1_IsPressed","");ShutdownOS(E_OK);
    //if (TRUE == BUTTON_IsPressed(BUTTON_2)) SetEvent(tsk_EventDispatcher, ev_engine_onUpdate);
    //if (TRUE == BUTTON_IsPressed(BUTTON_1)) LED_Toggle(LED_GREEN);SetEvent(tsk_EventDispatcher, ev_joystick_onUpdate);
    //if (TRUE == BUTTON_IsPressed(BUTTON_2)) LED_Toggle(LED_YELLOW);SetEvent(tsk_EventDispatcher, ev_engine_onUpdate);
}

/* [] END OF FILE */