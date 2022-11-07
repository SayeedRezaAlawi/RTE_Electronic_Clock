/*******************************************************************************
* File Name: ugui_st7735.c
*
* Description:
*  This is a driver for the uGui graphical library developed by 
*  Achim Döbler.
*  It is for ST7735 graphic controller found in a lot of low cost graphics 
*  chinese displays an to be used with PSoC microcontrollers from Cypress.
*  At the time of writting this, developing and testing with PSoC 4 micros.
*  Will test it with other PSoC micros as soon as i can.
*
* Note:
*  For more information about uGui...
*  Website: http://www.embeddedlightning.com/ugui/
*  Git: https://github.com/achimdoebler/UGUI
*  Forum: http://www.embeddedlightning.com/forum/
*  PDF Reference manual (excellent): http://www.embeddedlightning.com/download/reference-guide/?wpdmdl=205
*
*  Thanks to Achim Döbler for such a god job.
*
* Log version:
*  1.0 - April, 2016.       First version.
*
********************************************************************************
* Copyright (c) 2015 Jesús Rodríguez Cacabelos
* This driver follows the same license than the uGui library.
* http:
*******************************************************************************/

//#include "ugui_config.h"
#include <project.h>
#include "ugui.h"
#include "ugui_st7735.h"

/* *** Function prototypes. *** */
void Display_Reset();
void Display_WriteCommand(uint8 command);
void Display_WriteData(uint8 data[], uint8 length);

void Display_Init()
{
    uint8 loop;
    
    // { command, datalength, ... data ..., delay }
    uint8 configdata[19][20] = {
        {0x11, 0, 120},
        {0xB1, 3, 0x01, 0x2C, 0x2D, 0},
        {0xB2, 3, 0x01, 0x2C, 0x2D, 0},
        {0xB3, 6, 0x01, 0x2C, 0x2D, 0x01, 0x2C, 0x2D, 0},
        {0xB4, 1, 0x07, 0},
        {0xB6, 2, 0xB4, 0xF0, 0},
        {0xC0, 3, 0xA2, 0x02,  0x04, 0},
        {0xC1, 1, 0xC5, 0},
        {0xC2, 2, 0x0A, 0x00, 0},
        {0xC3, 2, 0x8A, 0x2A},
        {0xC4, 2, 0x8A, 0xEE}, 
        {0xC5, 1, 0x04, 0},
        {0x36, 1, 0xC8, 0},
        {0xE0, 17, 0x0f, 0x1A, 0x0f, 0x18, 0x2f, 0x28, 0x20, 0x22, 0x1f,
                   0x1b, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10, 0},
        {0xE1, 16, 0x0f, 0x1b, 0x0f, 0x17, 0x33, 0x2c, 0x29, 0x2e, 0x30,
                   0x30, 0x39, 0x3f, 0x00, 0x07, 0x03, 0x10, 0},
        {0x2A, 4, 0x00, 0x02, 0x00, 0x81, 0},
        {0x2B, 4, 0x00, 0x01, 0x00, 0xa0, 0},
#if defined USE_COLOR_RGB565        
        {0x3A, 1, 0x05, 0},
#endif
#if defined USE_COLOR_RGB888        
        {0x3A, 1, 0x06, 0},
#endif
        {0x29, 0, 0}};
    
    /* *** Initialize hardware. **** */
    RST_Write(1);                    // DISP_RESET is active low. So initialize it to high level.
    RS_Write(1);                       // DISP_CD. Ready for data mode, the most
                                            //          common mode.
    
    SPIM_Start();                            // Initialize SPI bus.
        
    /* *** Initialize display. *** */
    Display_Reset();
    
    for (loop = 0; loop < 19; loop++)
    {
        Display_WriteCommand(configdata[loop][0]);
        Display_WriteData(&configdata[loop][2], configdata[loop][1]);
        
        if (configdata[loop][configdata[loop][1] + 2] != 0)
            CyDelay(configdata[loop][configdata[loop][1] + 2]);
    }
   
    // Initialize global structure and set PSET to this.PSET. 
    UG_Init(&gui7735, Display_PSet, DISPLAY_WIDTH, DISPLAY_HEIGHT); 
    
    // Register acceleratos.
    UG_DriverRegister(DRIVER_FILL_FRAME, (void*)HW_FillFrame);
    UG_DriverRegister(DRIVER_DRAW_LINE, (void*)HW_DrawLine);
}

void Display_Reset()
{
    RST_Write(0); CyDelay(50);
    RST_Write(1); CyDelay(120);
}

void Display_WriteCommand(uint8 command)
{
    /* *** Clear CD line for command mode. *** */
    RS_Write(0);

    SPIM_WriteTxData(command);
    
    // White until all data in TX buffer has been sent.
    // Microcontroller is faster than SPI data rate. We have to 
    // wait to avoid changing state of CD line before all data has
    // been sent.
   // while (mmSPI_SpiUartGetTxBufferSize() > 0) {};
    
    /* *** Let CD line ready for data mode. *** */
    //mmDisplayCD_Write(1);
}

void Display_WriteData(uint8 data[], uint8 length)
{
    /* *** CD line is managed in Display_WriteCommand function.
           This way we make this funtion faster. *** */
    //mmDisplayCD_Write(1);
    RS_Write(1);

    // If there is some pending data in TX buffer, wait.
    //while (mmSPI_SpiUartGetTxBufferSize() > 0) {};

    SPIM_PutArray(data, length);
}


void Display_PSet(UG_S16 x, UG_S16 y, UG_COLOR c)
{
    UG_U16 color;
    uint8 ddata[4];

    if((x < 0) ||(x >= DISPLAY_WIDTH) || (y < 0) || (y >= DISPLAY_HEIGHT)) return;

    Display_WriteCommand(0x2A);
    ddata[0] = 0x00; ddata[1] = x; ddata[2] = 0x00; ddata[3] = x + 1;
    Display_WriteData(ddata, 4);

    Display_WriteCommand(0x2B);
    ddata[0] = 0x00; ddata[1] = y; ddata[2] = 0x00; ddata[3] = y + 1;
    Display_WriteData(ddata, 4);

    Display_WriteCommand(0x2C);

#if defined USE_COLOR_RGB565
    
    color = (c & 0xF800) >> 11;
    color = color | (c & 0x07E0);
    color = color | ((c & 0x001F) << 11);
    
    ddata[0] = (color >> 8); ddata[1] = color;
    Display_WriteData(ddata, 2);
    
#endif    

#if defined USE_COLOR_RGB888
    
    ddata[0] = (uint8)(c);
    ddata[1] = (uint8)(c >> 8);
    ddata[2] = (uint8)(c >> 16);
    
    Display_WriteData(ddata, 3); 
    
#endif    

}

UG_RESULT HW_FillFrame(UG_S16 x1, UG_S16 y1, UG_S16 x2, UG_S16 y2, UG_COLOR c)
{
    uint8 loopx, loopy;
    UG_U16 color;
    uint8 ddata[4];
    
    if((x1 < 0) ||(x1 >= DISPLAY_WIDTH) || (y1 < 0) || (y1 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;
    if((x2 < 0) ||(x2 >= DISPLAY_WIDTH) || (y2 < 0) || (y2 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;

    Display_WriteCommand(0x2A);
    ddata[0] = 0x00; ddata[1] = x1; ddata[2] = 0x00; ddata[3] = x2;
    Display_WriteData(ddata, 4);

    Display_WriteCommand(0x2B);
    ddata[0] = 0x00; ddata[1] = y1; ddata[2] = 0x00; ddata[3] = y2;
    Display_WriteData(ddata, 4);

    Display_WriteCommand(0x2C);    
    
#if defined USE_COLOR_RGB565
    
    color = (c & 0xF800) >> 11;
    color = color | (c & 0x07E0);
    color = color | ((c & 0x001F) << 11);
    
    for (loopx = x1; loopx < (x2 + 1); loopx++)
    {
        for (loopy = y1; loopy < (y2 + 1); loopy++)
        {
            ddata[0] = (color >> 8); ddata[1] = color;
            Display_WriteData(ddata, 2); 
        }
    }
    
#endif    

#if defined USE_COLOR_RGB888
    
    ddata[0] = (uint8)(c);
    ddata[1] = (uint8)(c >> 8);
    ddata[2] = (uint8)(c >> 16);
    
    for (loopx = x1; loopx < (x2 + 1); loopx++)
    {
        for (loopy = y1; loopy < (y2 + 1); loopy++)
        {
            Display_WriteData(ddata, 3); 
        }
    }
    
#endif    
    
    return UG_RESULT_OK;
}

UG_RESULT HW_DrawLine( UG_S16 x1 , UG_S16 y1 , UG_S16 x2 , UG_S16 y2 , UG_COLOR c )
{
    if((x1 < 0) ||(x1 >= DISPLAY_WIDTH) || (y1 < 0) || (y1 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;
    if((x2 < 0) ||(x2 >= DISPLAY_WIDTH) || (y2 < 0) || (y2 >= DISPLAY_HEIGHT)) return UG_RESULT_FAIL;
    
    // If it is a vertical or a horizontal line, draw it.
    // If not, then use original drawline routine.
    if ((x1 == x2) || (y1 == y2)) 
    {
        HW_FillFrame(x1, y1, x2, y2, c);
        return UG_RESULT_OK;
    }
    
    return UG_RESULT_FAIL;
}


/* [] END OF FILE */
