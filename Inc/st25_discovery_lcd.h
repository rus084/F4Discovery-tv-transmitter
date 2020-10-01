/**
  ******************************************************************************
  * @file    st25_discovery_lcd.h 
  * @author  MMY Application Team
  * @version $Revision$
  * @date    $Date$
  * @brief   This file contains all the functions prototypes for the 
  *          st25_discovery_lcd.c driver.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2017 STMicroelectronics</center></h2>
  *
  * Licensed under ST MYLIBERTY SOFTWARE LICENSE AGREEMENT (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/myliberty  
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied,
  * AND SPECIFICALLY DISCLAIMING THE IMPLIED WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE, AND NON-INFRINGEMENT.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ST25_DISCOVERY_LCD_H
#define __ST25_DISCOVERY_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "st25_discovery.h"
/* Include SDRAM Driver */
/* Include LCD component driver */
#include "fonts.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup ST25_DISCOVERY_BSP
  * @{
  */ 
    
/** @addtogroup ST25_DISCOVERY_LCD
  * @{
  */ 

typedef enum 
{
  LCD_OK = 0,
  LCD_ERROR = 1,
  LCD_TIMEOUT = 2
} LCD_StatusTypeDef;

/** 
  * @brief  Point structure definition
  */
typedef struct 
{
  int16_t X;
  int16_t Y;
} Point, * pPoint;   

/** 
  * @brief  Draw properties structure definition
  */
typedef struct 
{ 
  uint32_t TextColor;
  uint32_t BackColor;
  sFONT    *pFont; 
} LCD_DrawPropTypeDef;

/** 
  * @brief  Line mode structure definition
  */ 
typedef enum
{
  CENTER_MODE          = 0x01,    /* Center mode */
  RIGHT_MODE           = 0x02,    /* Right mode  */
  LEFT_MODE            = 0x03     /* Left mode   */
}Line_ModeTypdef;

/** 
  * @brief  LCD color  
  */ 
#define LCD_COLOR_WHITE          0xFFFF
#define LCD_COLOR_BLACK          0x0000
#define LCD_COLOR_GREY           0xF7DE
#define LCD_COLOR_BLUE           0x001F
#define LCD_COLOR_BLUE2          0x051F
#define LCD_COLOR_BLUEST         0x03F9
#define LCD_COLOR_RED            0xF800
#define LCD_COLOR_MAGENTA        0xF81F
#define LCD_COLOR_GREEN          0x07E0
#define LCD_COLOR_CYAN           0x7FFF
#define LCD_COLOR_YELLOW         0xFFE0
#define LCD_COLOR_LIGHTBLUE      0x841F
#define LCD_COLOR_LIGHTGREEN     0x87F0
#define LCD_COLOR_LIGHTRED       0xFC10
#define LCD_COLOR_LIGHTCYAN      0x87FF
#define LCD_COLOR_LIGHTMAGENTA   0xFC1F
#define LCD_COLOR_LIGHTYELLOW    0xFFF0
#define LCD_COLOR_DARKBLUE       0x0010
#define LCD_COLOR_DARKGREEN      0x0400
#define LCD_COLOR_DARKRED        0x8000
#define LCD_COLOR_DARKCYAN       0x0410
#define LCD_COLOR_DARKMAGENTA    0x8010
#define LCD_COLOR_DARKYELLOW     0x8400
#define LCD_COLOR_WHITE          0xFFFF
#define LCD_COLOR_LIGHTGRAY      0xD69A
#define LCD_COLOR_GRAY           0x8410
#define LCD_COLOR_DARKGRAY       0x4208
#define LCD_COLOR_BLACK          0x0000
#define LCD_COLOR_BROWN          0xA145
#define LCD_COLOR_ORANGE         0xFD20

/* Font 24 22 20 16 8 */
#define Line0          0
#define Line1          1
#define Line2          2
#define Line3          3
#define Line4          4
#define Line5          5
#define Line6          6
#define Line7          7
#define Line8          8
#define Line9          9
/* Font 22 20 16 8 */
#define Line10         10
/* Font 20 16 8 */
#define Line11         11
/* Font 16 8 */
#define Line12         12
#define Line13         13
#define Line14         14
/* Font 8 */
#define Line15         15
#define Line16         16
#define Line17         17
#define Line18         18
#define Line19         19
#define Line20         20
#define Line21         21
#define Line22         22
#define Line23         23
#define Line24         24
#define Line25         25
#define Line26         26
#define Line27         27
#define Line28         28
#define Line29         29

/** 
  * @brief LCD default font 
  */ 
#define LCD_DEFAULT_FONT         Font24

/** 
  * @brief  LCD Direction  
  */ 
#define LCD_DIR_HORIZONTAL       0x0000
#define LCD_DIR_VERTICAL         0x0001


/**
  * define used for simple increment display position after draw pixel
  */
#define ILI9341_NO_CURSOR 0xFFFF

/** 
  * @brief LCD Pixel format 
  */  

// Init / Configuration
uint8_t  BSP_LCD_Init(void);
uint32_t BSP_LCD_GetXSize(void);
uint32_t BSP_LCD_GetYSize(void);

// Color / Layer
void BSP_LCD_SetColors( uint16_t aTextColor,  uint16_t aBackColor);
void BSP_LCD_GetColors( uint16_t *Text,  uint16_t *Back);
void BSP_LCD_SetTextColor(uint16_t Color);
void BSP_LCD_SetBackColor(uint16_t Color);
void BSP_LCD_SetFont(sFONT *fonts);
sFONT *BSP_LCD_GetFont(void);
// Init: Not implemented
void BSP_LCD_LayerInit(void);
void BSP_LCD_SetLayer(uint32_t Layerx);
void BSP_LCD_SetTransparency(uint8_t transparency);
void BSP_LCD_SetColorKeying(uint32_t RGBValue);
void BSP_LCD_ReSetColorKeying(void);

// Cursor / Window management
void BSP_LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void BSP_LCD_SetCursor_onwindows(uint16_t Xpos, uint16_t Ypos,uint16_t width,uint16_t height);
int  BSP_LCD_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width , uint16_t Height );
void BSP_LCD_WindowModeDisable(void);

// Char / String
void BSP_LCD_Clear(uint16_t Color);
void BSP_LCD_ClearStringLine(uint16_t Line);
void BSP_LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c);
void BSP_LCD_DrawCharLine(uint16_t Line, uint16_t Columns, const uint8_t *c);
void BSP_LCD_DisplayChar(uint16_t Line, uint16_t Columns, uint8_t Ascii);
void BSP_LCD_DisplayCharAt(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii);
void BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos, const uint8_t *Text, Line_ModeTypdef Mode);
void BSP_LCD_DisplayStringAtLine(uint16_t Line,const uint8_t *ptr);
void BSP_LCD_DisplayStringLineWSize(uint16_t Line, uint8_t *ptr,uint8_t size);

// Geometric
void BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code);
void BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length);
void BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);
void BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount);
void BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius);
void BSP_LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);
void BSP_LCD_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pbmp);
void BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height);
void BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius);
void BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount);
void BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius);

void BSP_LCD_DisplayOff(void);
void BSP_LCD_DisplayOn(void);

// Picture display
void BSP_LCD_DisplayPicture(uint16_t Xpos, uint16_t Ypos, const char* Pict);
void BSP_LCD_GetPictureDim(const char * Pict, uint32_t* Width, uint32_t* Height);
void BSP_LCD_CaptureScreen(void);

// Not implemented
void BSP_LCD_DrawMonoPict(const uint32_t *Pict);
void BSP_LCD_WriteBMP(uint32_t BmpAddress);


/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */
  
#ifdef __cplusplus
}
#endif

#endif /* __ST25_DISCOVERY_LCD_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
