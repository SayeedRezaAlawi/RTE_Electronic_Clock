/**
* \file <filename>
* \author <author-name>
* \date <date>
*
* \brief <Symbolic File name>
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

#include "project.h"
#include "watchdog.h"
#include "logging.h"


/*****************************************************************************/
/* Local pre-processor symbols/macros ('#define')                            */
/*****************************************************************************/

/*****************************************************************************/
/* Global variable definitions (declared in header file with 'extern')       */
/*****************************************************************************/
extern cy_en_em_eeprom_status_t eepromReturnStatus;
extern uint8_t eepromReturnValue;
/*****************************************************************************/
/* Local type definitions ('typedef')                                        */
/*****************************************************************************/
#define USED_EEPROM_SECTOR1          (1u)
#define RESET_COUNTER_BYTE1          ((USED_EEPROM_SECTOR1 * CYDEV_EEPROM_SECTOR_SIZE) + 0x00)


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
 * Initialises the LED's and turns them off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t WD_Start(WDT_TimeOut_t* timeout)
{
    RC_t result = RC_SUCCESS;
    CyWdtStart(timeout->timer,timeout->mode); 
    return result;
}

/**
 * Sets the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @param LED_ONOFF_t ledOnOff - Trun the led on or off
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
RC_t WD_Trigger()
{
	RC_t result = RC_SUCCESS;
    uint8_t value=0;
    char str[50];
    value=runnables.byte;
    if(runnables.byte == 0x1F)
    {
        //LOG_I("CyWdtClear","");
        //UART_LOG_PutString("Value: 0x");
        //sprintf(str, "%02X ", value) ;
        //LOG_I(str,"");
        //EEPROM_WriteByte(value, 0);
        //eepromReturnValue = EEPROM_ReadByte(0);
        //sprintf(str, "eepromReturnValue: %d", eepromReturnValue);
        //UART_LOG_PutString("EEPROM_ReadByte(0): 0x");
        //sprintf(str, "%02X ", EEPROM_ReadByte(0)) ;
        //LOG_I(str,"");
        //UART_LOG_PutString("Success to write runnable info to Em_EEPROM! \n\r");
        CyWdtClear();
        result = RC_SUCCESS;
        runnables.byte = 0x00;
    }
    else
    {
        //eepromReturnStatus = Em_EEPROM_Write(0u, &value, 1u);
        //sprintf(str, "value: %d", value);
        //LOG_I(str,"");
        if(value != EEPROM_ReadByte(0)){
        EEPROM_WriteByte(value, 0);
        }
        //EEPROM_WriteByte(value, RESET_COUNTER_BYTE1);
        //eepromReturnValue = EEPROM_ReadByte(RESET_COUNTER_BYTE1);
        //sprintf(str, "eepromReturnValue: %d", eepromReturnValue);
        //LOG_I(str,"");
        //UART_LOG_PutString("Success to write runnable info to Em_EEPROM! \n\r");
        
//        if(eepromReturnStatus != CY_EM_EEPROM_SUCCESS)
//        {
//            UART_LOG_PutString("Error to write runnable info to Em_EEPROM! \n\r");
//        }
//        else
//        {
//            UART_LOG_PutString("Success to write runnable info to Em_EEPROM! \n\r");
//        }
    //LOG_I("Not CyWdtClear","");
    result = RC_SUCCESS;
    }
    return result;
}



/**
 * Toggle the required LED
 * @param LED_t ledId - Identifier for the LED, ALL will change all LED's
 * @return RC_SUCCESS if function was executed as exepected, other error code in case of error
 */
boolean_t WD_CheckResetBit()
{
    boolean_t result = FALSE;
    char str[30];
    uint8_t reset_status = *((uint8_t *)CYREG_PHUB_CFGMEM23_CFG1) ;
    sprintf(str, "reset_status: %d", reset_status);
    UART_LOG_PutString(str);
    UART_LOG_PutString("\n");
    
    if(reset_status & 0x08u)
    {
        result=TRUE;
    }
    else
    {
        result=FALSE;
    }
    return result;
}


