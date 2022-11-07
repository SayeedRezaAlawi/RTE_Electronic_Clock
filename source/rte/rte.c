/**
* \file rte.c
* \author P. Fromm
* \date 8.12.18
*
* \brief Runnable dispatcher
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
*/

/*****************************************************************************/
/* Include files                                                             */
/*****************************************************************************/
#include "rte.h"
#include "led.h"
#include "logging.h"
#include "watchdog.h"

/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/

/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/

/*****************************************************************************/
/* Local variable definitions ('static')                                     */
/*****************************************************************************/



/*****************************************************************************/
/* Local function prototypes ('static')                                      */
/*****************************************************************************/


/*****************************************************************************/
/* Function implementation - global ('extern') and local ('static')          */
/*****************************************************************************/

/**
 * Will call all cyclic runnables when due
 * \param RTE_cyclicTable_t const *const table : [IN] table to be processed
 * \param uint16_t tableSize : [IN] table size
 * \param uint16_t time : [IN] time elapsed since last call in ms
 * \return RC_SUCCESS if all ok, error code otherwise
 */
RC_t RTE_ProcessCyclicTable(RTE_cyclicTable_t const *const table, uint16_t tableSize, uint16_t time)
{
    static uint32_t totalTime = 0;
    char data[20];
    
    
    for (uint16_t i = 0; i < tableSize; i++)
    {
        
        if (0 == (totalTime % table[i].cycleTime))
        {
            //LOG_I("RTE_ProcessCyclicTable","");
            //itoa(totalTime, data, 10);
            //UART_LOG_PutString("totalTime: ");
            //UART_LOG_PutString(data);
            //UART_LOG_PutString("\n");
            table[i].run();
            //WD_Trigger();
            LED_Toggle(LED_RED);
            
        }
    }
    
    totalTime += time;
    //LED_Set(LED_ALL,LED_OFF);
    totalTime %= 100000;    
}
    
/**
 * Will call all event runnables when due
 * \param RTE_eventTable_t const *const table : [IN] table to be processed
 * \param uint16_t tableSize : [IN] table size
 * \param EventMaskType ev : [IN] event mask to be processed
 * \return RC_SUCCESS if all ok, error code otherwise
 */
RC_t RTE_ProcessEventTable(RTE_eventTable_t const *const table, uint16_t tableSize, EventMaskType ev)
{
    char data[20];
    for (uint16_t i = 0; i < tableSize; i++)
    {
        //itoa(i, data, 10);
            //UART_LOG_PutString("i: ");
            //UART_LOG_PutString(data);
            //UART_LOG_PutString("\n");
        if (ev & table[i].event)
        {
            //LOG_I("ev & table[i].event","");
            table[i].run();
            //WD_Trigger();
        }
    }
    
}