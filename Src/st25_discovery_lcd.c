/**
  ******************************************************************************
  * @file    st25_discovery_lcd.c 
  * @author  MMY Application Team
  * @version $Revision$
  * @date    $Date$
  * @brief   This file includes the LCD driver for ILI9341 Liquid Crystal 
  *          Display Modules of ST25-Discovery kit.
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

/* File Info : -----------------------------------------------------------------
                                   User NOTES
1. How To use this driver:
--------------------------
   - This driver is used to drive directly an LCD using SPI communication.
   - This driver select dynamically the mounted LCD, ILI9341 240x320 LCD mounted 
     on MB1283 discovery board, and use the adequate timing and setting for 
	 the specified LCD using device ID of the ILI9341 mounted on MB1283 discovery board           

2. Driver description:
---------------------
  + Initialization steps :
     o Initialize the LCD using the LCD_Init() function.  
     o Enable the LCD display using LCD_DisplayOn() function.

  
  + Display on LCD
      o Clear the whole LCD using LCD_Clear() function or only one specified string
        line using LCD_ClearStringLine() function.
      o Display a character on the specified line and column using LCD_DisplayChar()
        function or a complete string line using LCD_DisplayStringAtLine() function.
      o Display a string line on the specified position (x,y in pixel) and align mode
        using BSP_LCD_DisplayStringAt() function.          
      o Draw and fill a basic shapes (dot, line, rectangle, circle, ellipse, .. bitmap) 
        on LCD using the available set of functions     
 
------------------------------------------------------------------------------*/

/* Includes ------------------------------------------------------------------*/
#include "st25_discovery_lcd.h"
#ifdef ENABLE_SCREEN_CAPTURE
  /* Flash is used to store LCD screen capture */
  #include "fw_command.h"
#endif

/** @addtogroup BSP
  * @{
  */ 
void writeFB(int y,int x,int code);

int xWnd;
int yWnd;
int wWnd;
int hWnd;
int ypWhd;
int xpWnd;

/** @addtogroup ST25_DISCOVERY_BSP
  * @{
  */
    
/** @defgroup ST25_DISCOVERY_LCD ST25 DISCOVERY LCD
  * @brief This file includes the LCD driver for (ILI9341) 
  * @{
  */ 

#define POLY_X(Z)              ((int32_t)((Points + (Z))->X))
#define POLY_Y(Z)              ((int32_t)((Points + (Z))->Y))
#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define ABS(X)  ((X) > 0 ? (X) : -(X)) 

LCD_DrawPropTypeDef DrawProp;

static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c);
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3);

/**
  * @brief  Initializes the LCD.
  * @retval LCD state
  */
uint8_t BSP_LCD_Init(void)
{ 
    BSP_LCD_SetFont( &LCD_DEFAULT_FONT );
    BSP_LCD_SetColors( LCD_COLOR_WHITE, LCD_COLOR_BLACK );
  
  return LCD_OK;
}  

/**
  * @brief  Gets the LCD X size.  
  * @retval The used LCD X size
  */
uint32_t BSP_LCD_GetXSize(void)
{
  return 190;
}

/**
  * @brief  Gets the LCD Y size.  
  * @retval The used LCD Y size
  */
uint32_t BSP_LCD_GetYSize(void)
{
  return 300;
}


/**
  * @brief  Initializes the LCD Layers.
  * @param  None
  * @retval None
  */

void BSP_LCD_LayerInit(void)
{
	// No multiple layer support
}


/**
  * @brief  Sets the LCD Layer.
  * @param  Layerx: specifies the Layer foreground or background.
  * @retval None
  */
void BSP_LCD_SetLayer(uint32_t Layerx)
{
	// No layer support
} 

/**
  * @brief  Sets the LCD Text and Background colors.
  * @param  aTextColor: specifies the Text Color.
  * @param  aBackColor: specifies the Background Color.
  * @retval None
  */
void BSP_LCD_SetColors( uint16_t aTextColor,  uint16_t aBackColor)
{
  DrawProp.TextColor = aTextColor; 
  DrawProp.BackColor = aBackColor;
}

/**
  * @brief  Gets the LCD Text and Background colors.
  * @param  Text: pointer to the variable that will contain the Text 
            Color.
  * @param  Back: pointer to the variable that will contain the Background 
            Color.
  * @retval None
  */
void BSP_LCD_GetColors( uint16_t *Text,  uint16_t *Back)
{
  *Text = DrawProp.TextColor;
  *Back = DrawProp.BackColor;
}
 
/**
  * @brief  Gets the LCD text color. 
  * @retval Used text color.
  */
uint16_t BSP_LCD_GetTextColor(void)
{
  return DrawProp.TextColor;
}

/**
  * @brief  Gets the LCD background color.
  * @retval Used background color
  */
uint16_t BSP_LCD_GetBackColor(void)
{
  return DrawProp.BackColor;
}

/**
  * @brief  Sets the Text color.
  * @param  Color: specifies the Text color code RGB(5-6-5).
  * @retval None
  */
void BSP_LCD_SetTextColor(uint16_t Color)
{
  DrawProp.TextColor = Color;
}

/**
  * @brief  Sets the Background color.
  * @param  Color: specifies the Background color code RGB(5-6-5).
  * @retval None
  */
void BSP_LCD_SetBackColor(uint16_t Color)
{
  DrawProp.BackColor = Color;
}


/**
  * @brief  Configure the transparency.
  * @param  transparency: specifies the transparency, 
  *         This parameter must range from 0x00 to 0xFF.
  * @retval None
  */
void BSP_LCD_SetTransparency(uint8_t transparency)
{
	 // No transparancy support
}

/**
  * @brief  Sets the LCD text font.
  * @param  fonts: Font to be used
  * @retval None
  */
void BSP_LCD_SetFont(sFONT *fonts)
{
  DrawProp.pFont = fonts;
}

/**
  * @brief  Gets the LCD text font.
  * @retval Used font
  */
sFONT *BSP_LCD_GetFont(void)
{
  return DrawProp.pFont;
}

/**
  * @brief  Sets the char cursor position.
  * @param  Xpos: specifies the X position.
  * @param  Ypos: specifies the Y position. 
  * @retval None
  */
void BSP_LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	BSP_LCD_SetDisplayWindow( Xpos, Ypos, DrawProp.pFont->Width, DrawProp.pFont->Height );
}

/**
  * @brief  Config and Sets the color Keying.
  * @param  RGBValue: Specifies the Color reference. 
  * @retval None
  */

void BSP_LCD_SetColorKeying(uint32_t RGBValue)
{  
  // Color Keying not supported
}

/**
  * @brief  Disable the color Keying.
  * @param  RGBValue: Specifies the Color reference. 
  * @retval None
  */
void BSP_LCD_ReSetColorKeying(void)
{
  // Color Keying not supported
} 

/**
  * @brief  Clears the whole LCD
  * @param  Color: Color to use for clearing.
  * @retval None
  */
void BSP_LCD_Clear(uint16_t Color)
{ 
  uint32_t counter = 0;
  uint32_t color_backup = DrawProp.TextColor; 
  DrawProp.TextColor = Color;
  
  for(counter = 0; counter < BSP_LCD_GetYSize(); counter++)
  {
    BSP_LCD_DrawHLine(0, counter, BSP_LCD_GetXSize());
  }
  DrawProp.TextColor = color_backup; 
  BSP_LCD_SetTextColor(DrawProp.TextColor);
}

/**
  * @brief  Clears the selected line.
  * @param  Line: Line to be cleared
  *          This parameter can be one of the following values:
  *            @arg  0..9: if the Current fonts is Font16x24
  *            @arg  0..19: if the Current fonts is Font12x12 or Font8x12
  *            @arg  0..29: if the Current fonts is Font8x8
  */
void BSP_LCD_ClearStringLine(uint16_t Line)
{ 
  uint32_t color_backup = DrawProp.TextColor; 
  DrawProp.TextColor = DrawProp.BackColor;;
    
  /* Draw a rectangle with background color */
  BSP_LCD_FillRect(0, (Line * DrawProp.pFont->Height), BSP_LCD_GetXSize(), DrawProp.pFont->Height);
  
  DrawProp.TextColor = color_backup;
  BSP_LCD_SetTextColor(DrawProp.TextColor);
}

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: X position (in pixel).
  * @param  Ypos: Y position (in pixel).
  * @param  c: pointer to the character data.
  * @retval None
  */
void BSP_LCD_DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c)
{
  DrawChar(Xpos, Ypos, c );
}

/**
  * @brief  Displays one character.
  * @param  Line: Line where to display the character shape.
  * @param  Column: Column where to display the character shape.
  * @param  c: pointer to the character data.
  * @retval None
  */
void BSP_LCD_DrawCharLine(uint16_t Line, uint16_t Columns, const uint8_t *c)
{
	uint16_t Xpos = 0;
	uint16_t Ypos = 0;
	
	Ypos = (Line * DrawProp.pFont->Height);
	Xpos = (Columns * DrawProp.pFont->Width);
	
	DrawChar(Xpos, Ypos, c );
}

/**
  * @brief  Displays one character.
  * @param  Line: Line where to display the character shape.
  * @param  Column: Column where to display the character shape.
  * @param  Ascii: Character ascii code
  *           This parameter must be a number between Min_Data = 0x20 and Max_Data = 0x7E 
  * @retval None
  */
void BSP_LCD_DisplayChar(uint16_t Line, uint16_t Columns, uint8_t Ascii)
{
  uint16_t Xpos = 0;
	uint16_t Ypos = 0;
	
	Ypos = (Line * DrawProp.pFont->Height);
	Xpos = (Columns * DrawProp.pFont->Width);
  
  BSP_LCD_DisplayCharAt( Xpos, Ypos, Ascii);
}

/**
  * @brief  Displays one character.
  * @param  Xpos: X position (in pixel).
  * @param  Ypos: Y position (in pixel).
  * @param  Ascii: Character ascii code
  *           This parameter must be a number between Min_Data = 0x20 and Max_Data = 0x7E 
  * @retval None
  */
void BSP_LCD_DisplayCharAt(uint16_t Xpos, uint16_t Ypos, uint8_t Ascii)
{
  DrawChar(Xpos, Ypos, &DrawProp.pFont->table[(Ascii-' ') *\
  DrawProp.pFont->Height * ((DrawProp.pFont->Width + 7) / 8)]);
}

/**
  * @brief  Displays characters on the LCD.
  * @param  Xpos: X position (in pixel)
  * @param  Ypos: Y position (in pixel)   
  * @param  Text: Pointer to string to display on LCD
  * @param  Mode: Display mode
  *          This parameter can be one of the following values:
  *            @arg  CENTER_MODE
  *            @arg  RIGHT_MODE
  *            @arg  LEFT_MODE
  * @retval None
  */
void BSP_LCD_DisplayStringAt(uint16_t Xpos, uint16_t Ypos,const uint8_t *Text, Line_ModeTypdef Mode)
{
  uint16_t refcolumn = 1, i = 0;
  uint32_t size = 0, xsize = 0; 
  const uint8_t  *ptr = Text;
  
  /* Get the text size */
  while (*ptr++) size ++ ;
  
  /* Characters number per line */
  xsize = (BSP_LCD_GetXSize()/DrawProp.pFont->Width);
  
  switch (Mode)
  {
  case CENTER_MODE:
    {
      refcolumn = Xpos + ((xsize - size)* DrawProp.pFont->Width) / 2;
      break;
    }
  case LEFT_MODE:
    {
      refcolumn = Xpos;
      break;
    }
  case RIGHT_MODE:
    {
      refcolumn =  - Xpos + ((xsize - size)*DrawProp.pFont->Width);
      break;
    }    
  default:
    {
      refcolumn = Xpos;
      break;
    }
  }
  
  /* Send the string character by character on lCD */
  while ((*Text != 0) & (((BSP_LCD_GetXSize() - (i*DrawProp.pFont->Width)) & 0xFFFF) >= DrawProp.pFont->Width))
  {
    /* Display one character on LCD */
    BSP_LCD_DisplayCharAt(refcolumn, Ypos, *Text);
    /* Decrement the column position by 16 */
    refcolumn += DrawProp.pFont->Width;
    /* Point on the next character */
    Text++;
    i++;
  }
}

/**
  * @brief  Displays a character on the LCD.
  * @param  Line: Line where to display the character shape
  *          This parameter can be one of the following values:
  *            @arg  0..9: if the Current fonts is Font16x24  
  *            @arg  0..19: if the Current fonts is Font12x12 or Font8x12
  *            @arg  0..29: if the Current fonts is Font8x8
  * @param  ptr: Pointer to string to display on LCD
  * @retval None
  */
void BSP_LCD_DisplayStringAtLine(uint16_t Line,const uint8_t *ptr)
{
  BSP_LCD_DisplayStringAt(0, LINE(Line), ptr, LEFT_MODE);
}

/**
  * @brief  Displays a maximum of Size char on the LCD.
  * @param  Line: the Line where to display the character shape .
  *   This parameter can be one of the following values:
  *     @arg Linex: where x can be 0..9
  * @param  *ptr: pointer to string to display on LCD.
  * @retval None
  */
void BSP_LCD_DisplayStringLineWSize(uint16_t Line, uint8_t *ptr, uint8_t size)
{ 
  uint32_t i = 0;
  uint16_t refcolumn;
	char space[]={" "};
            
  refcolumn = 0;
  if (size>20) size=20;
	
	//LCD_ClearLine(Line);
            
  /* Send the string character by character on lCD */
  while (i < size) 
  {
    /* Display one character on LCD */
    BSP_LCD_DisplayChar(Line, refcolumn, *ptr);
    /* Decrement the column position by deltacolumn(16 or -16 for HX8347D) */
    refcolumn ++;
    /* Point on the next character */
    ptr++;
    /* Increment the character counter */
    i++;
  }
	
	do
	{
		/* Display one character on LCD */
    BSP_LCD_DisplayChar(Line, refcolumn, (uint8_t)(space[0]));
    /* Decrement the column position by deltacolumn(16 or -16 for HX8347D) */
    refcolumn ++;
    /* Increment the character counter */
    i++;
	}
	while(i < 20);
}

/**
  * @brief  Draws a pixel on LCD.
  * @param  Xpos: X position (in pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  RGB_Code: Pixel color in RGB mode (5-6-5)
  * @retval None
  */
void BSP_LCD_DrawPixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGB_Code)
{
  if ((Xpos == ILI9341_NO_CURSOR) || (Ypos == ILI9341_NO_CURSOR))
  {
    writeFB(ypWhd,xpWnd,RGB_Code);
    xpWnd++;
    if (xpWnd >= (xWnd + wWnd))
    {
      xpWnd = xWnd;
      ypWhd++;
      if (ypWhd >= (yWnd + hWnd))
      {
        ypWhd = yWnd;
      }
    }
    
    //int xWnd = Xpos;
    //int yWnd = Ypos;
    //int wWnd = Width;
    //int hWnd = Height;
    //int ypWhd = Xpos;
    //int xpWnd = Ypos;
  }
  else
  {
    writeFB(Ypos,Xpos,RGB_Code);
  }
}
  
/**
  * @brief  Draws an horizontal line.
  * @param  Xpos: X position (in pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  Length: Line length
  * @retval None
  */
void BSP_LCD_DrawHLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t index = 0;
  
  for(index = 0; index < Length; index++)
  {
    BSP_LCD_DrawPixel((Xpos + index), Ypos, DrawProp.TextColor);
  }
}

/**
  * @brief  Draws a vertical line.
  * @param  Xpos: X position (n pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  Length: Line length
  */
void BSP_LCD_DrawVLine(uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint32_t index = 0;
  
  for(index = 0; index < Length; index++)
  {
    BSP_LCD_DrawPixel(Xpos, Ypos + index, DrawProp.TextColor);
  }
}

/**
  * @brief  Draws an uni-line (between two points).
  * @param  x1: Point 1 X position (in pixels)
  * @param  y1: Point 1 Y position (in pixels)
  * @param  x2: Point 2 X position (in pixels)
  * @param  y2: Point 2 Y position (in pixels)
  * @retval None
  */
void BSP_LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    BSP_LCD_DrawPixel(x, y, DrawProp.TextColor);  /* Draw the current pixel */
    num += numadd;                            /* Increase the numerator by the top of the fraction */
    if (num >= den)                           /* Check if numerator >= denominator */
    {
      num -= den;                             /* Calculate the new numerator value */
      x += xinc1;                             /* Change the x as appropriate */
      y += yinc1;                             /* Change the y as appropriate */
    }
    x += xinc2;                               /* Change the x as appropriate */
    y += yinc2;                               /* Change the y as appropriate */
  }
}

/**
  * @brief  Displays a rectangle.
  * @param  Xpos: specifies the X position (in pixels).
  * @param  Ypos: specifies the Y position (in pixels).
  * @param  Height: display rectangle height (in pixels).
  * @param  Width: display rectangle widthin (in pixels).
  * @retval None
  */
void BSP_LCD_DrawRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  /* Draw horizontal lines */
  BSP_LCD_DrawHLine(Xpos, Ypos, Width);
  BSP_LCD_DrawHLine(Xpos, (Ypos+ Height), Width);
  
  /* Draw vertical lines */
  BSP_LCD_DrawVLine(Xpos, Ypos, Height);
  BSP_LCD_DrawVLine((Xpos + Width), Ypos, Height);
}
                            
/**
  * @brief  Draw a circle.
  * @param  Xpos: specifies the X position (in pixels).
  * @param  Ypos: specifies the Y position (in pixels).
  * @param  Radius: radius of the circle.
  * @retval None
  */
void BSP_LCD_DrawCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;       /* Decision Variable */ 
  uint32_t  CurX;   /* Current X Value */
  uint32_t  CurY;   /* Current Y Value */ 
  
  D = 3 - (Radius << 1);
  CurX = 0;
  CurY = Radius;
  
  while (CurX <= CurY)
  {
    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos - CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos - CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos - CurX), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos - CurX), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + CurX), (Ypos + CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurX), (Ypos + CurY), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos + CurY), (Ypos + CurX), DrawProp.TextColor);

    BSP_LCD_DrawPixel((Xpos - CurY), (Ypos + CurX), DrawProp.TextColor);   

    /* Initialize the font */
    BSP_LCD_SetFont(&LCD_DEFAULT_FONT);

    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  } 
}

/**
  * @brief  Draws an poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void BSP_LCD_DrawPolygon(pPoint Points, uint16_t PointCount)
{
  int16_t X = 0, Y = 0;

  if(PointCount < 2)
  {
    return;
  }

  BSP_LCD_DrawLine(Points->X, Points->Y, (Points+PointCount-1)->X, (Points+PointCount-1)->Y);
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    BSP_LCD_DrawLine(X, Y, Points->X, Points->Y);
  }
  
}

/**
  * @brief  Draws an ellipse on LCD.
  * @param  Xpos: X position (in pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  XRadius: Ellipse X radius (in pixels)
  * @param  YRadius: Ellipse Y radius (in pixels)
  * @retval None
  */
void BSP_LCD_DrawEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);
  
  do {      
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos+y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos+(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);
    BSP_LCD_DrawPixel((Xpos-(uint16_t)(x/K)), (Ypos-y), DrawProp.TextColor);      
    
    e2 = err;
    if (e2 <= x) {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;     
  }
  while (y <= 0);
}

/**
  * @brief  Draws a bitmap picture (16 bpp).
  * @param  Xpos: Bmp X position in the LCD (in pixels)
  * @param  Ypos: Bmp Y position in the LCD (in pixels)
  * @param  pbmp: Pointer to Bmp picture address.
  * @retval None
  */
void BSP_LCD_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp)
{
  // not implemented
}

/**
  * @brief  Draws RGB Image (16 bpp).
  * @param  Xpos:  X position in the LCD (in pixels)
  * @param  Ypos:  Y position in the LCD (in pixels)
  * @param  Xsize: X size in the LCD (in pixels)
  * @param  Ysize: Y size in the LCD (in pixels)
  * @param  pdata: Pointer to the RGB Image address.
  * @retval None
  */
void BSP_LCD_DrawRGBImage(uint16_t Xpos, uint16_t Ypos, uint16_t Xsize, uint16_t Ysize, uint8_t *pdata)
{
  
  BSP_LCD_SetDisplayWindow(Xpos, Ypos, Xsize, Ysize);
  for (int i=0;i<Xsize*Ysize;i++)
  {
    uint16_t color = (pdata[0]) | (pdata[1]<<8);
    pdata+=2;
    BSP_LCD_DrawPixel(ILI9341_NO_CURSOR, ILI9341_NO_CURSOR, color);
  }
  BSP_LCD_SetDisplayWindow(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());
}

/**
  * @brief  Draws a full rectangle.
  * @param  Xpos: X position (in pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  Width: Rectangle width (in pixels)
  * @param  Height: Rectangle height (in pixels)
  * @retval None
  */
void BSP_LCD_FillRect(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
  BSP_LCD_SetTextColor(DrawProp.TextColor);
  do
  {
    BSP_LCD_DrawHLine(Xpos, Ypos++, Width);    
  }
  while(Height--);
}

/**
  * @brief  Draws a full circle.
  * @param  Xpos: X position (in pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  Radius: Circle radius (in pixels)
  * @retval None
  */
void BSP_LCD_FillCircle(uint16_t Xpos, uint16_t Ypos, uint16_t Radius)
{
  int32_t  D;        /* Decision Variable */ 
  uint32_t  CurX;    /* Current X Value */
  uint32_t  CurY;    /* Current Y Value */ 
  
  D = 3 - (Radius << 1);

  CurX = 0;
  CurY = Radius;
  
  BSP_LCD_SetTextColor(DrawProp.TextColor);

  while (CurX <= CurY)
  {
    if(CurY > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - CurY, Ypos + CurX, 2*CurY);
      BSP_LCD_DrawHLine(Xpos - CurY, Ypos - CurX, 2*CurY);
    }

    if(CurX > 0) 
    {
      BSP_LCD_DrawHLine(Xpos - CurX, Ypos - CurY, 2*CurX);
      BSP_LCD_DrawHLine(Xpos - CurX, Ypos + CurY, 2*CurX);
    }
    if (D < 0)
    { 
      D += (CurX << 2) + 6;
    }
    else
    {
      D += ((CurX - CurY) << 2) + 10;
      CurY--;
    }
    CurX++;
  }

  BSP_LCD_SetTextColor(DrawProp.TextColor);
  BSP_LCD_DrawCircle(Xpos, Ypos, Radius);
}

/**
  * @brief  Draws a full poly-line (between many points).
  * @param  Points: Pointer to the points array
  * @param  PointCount: Number of points
  * @retval None
  */
void BSP_LCD_FillPolygon(pPoint Points, uint16_t PointCount)
{
  
  int16_t X = 0, Y = 0, X2 = 0, Y2 = 0, X_center = 0, Y_center = 0, X_first = 0, Y_first = 0, pixelX = 0, pixelY = 0, counter = 0;
  uint16_t  IMAGE_LEFT = 0, IMAGE_RIGHT = 0, IMAGE_TOP = 0, IMAGE_BOTTOM = 0;  
  
  IMAGE_LEFT = IMAGE_RIGHT = Points->X;
  IMAGE_TOP= IMAGE_BOTTOM = Points->Y;
  
  for(counter = 1; counter < PointCount; counter++)
  {
    pixelX = POLY_X(counter);
    if(pixelX < IMAGE_LEFT)
    {
      IMAGE_LEFT = pixelX;
    }
    if(pixelX > IMAGE_RIGHT)
    {
      IMAGE_RIGHT = pixelX;
    }
    
    pixelY = POLY_Y(counter);
    if(pixelY < IMAGE_TOP)
    { 
      IMAGE_TOP = pixelY;
    }
    if(pixelY > IMAGE_BOTTOM)
    {
      IMAGE_BOTTOM = pixelY;
    }
  }  
  
  if(PointCount < 2)
  {
    return;
  }
  
  X_center = (IMAGE_LEFT + IMAGE_RIGHT)/2;
  Y_center = (IMAGE_BOTTOM + IMAGE_TOP)/2;
  
  X_first = Points->X;
  Y_first = Points->Y;
  
  while(--PointCount)
  {
    X = Points->X;
    Y = Points->Y;
    Points++;
    X2 = Points->X;
    Y2 = Points->Y;    
    
    FillTriangle(X, X2, X_center, Y, Y2, Y_center);
    FillTriangle(X, X_center, X2, Y, Y_center, Y2);
    FillTriangle(X_center, X2, X, Y_center, Y2, Y);   
  }
  
  FillTriangle(X_first, X2, X_center, Y_first, Y2, Y_center);
  FillTriangle(X_first, X_center, X2, Y_first, Y_center, Y2);
  FillTriangle(X_center, X2, X_first, Y_center, Y2, Y_first);   
}

/**
  * @brief  Draws a full ellipse.
  * @param  Xpos: X position (in pixels)
  * @param  Ypos: Y position (in pixels)
  * @param  XRadius: Ellipse X radius (in pixels)
  * @param  YRadius: Ellipse Y radius (in pixels)
  * @retval None
  */
void BSP_LCD_FillEllipse(int Xpos, int Ypos, int XRadius, int YRadius)
{
  int x = 0, y = -YRadius, err = 2-2*XRadius, e2;
  float K = 0, rad1 = 0, rad2 = 0;
  
  rad1 = XRadius;
  rad2 = YRadius;
  
  K = (float)(rad2/rad1);    
  
  do 
  { 
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos+y), (2*(uint16_t)(x/K) + 1));
    BSP_LCD_DrawHLine((Xpos-(uint16_t)(x/K)), (Ypos-y), (2*(uint16_t)(x/K) + 1));
    
    e2 = err;
    if (e2 <= x) 
    {
      err += ++x*2+1;
      if (-y == x && e2 <= y) e2 = 0;
    }
    if (e2 > y) err += ++y*2+1;
  }
  while (y <= 0);
}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOn(void)
{
  // not implemented
}


/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void BSP_LCD_DisplayOff(void)
{
  // not implemented
}


/**
  * @brief  Sets a display window
  * @param  Xpos: specifies the X buttom left position.
  * @param  Ypos: specifies the Y buttom left position.
  * @param  Height: display window height.
  * @param  Width: display window width.
  * @retval LCD_OK when completed
  */
int BSP_LCD_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width , uint16_t Height )
{
  xWnd = Xpos;
  yWnd = Ypos;
  wWnd = Width;
  hWnd = Height;
  ypWhd = Ypos;
  xpWnd = Xpos;
  return LCD_OK;
}

/**  
 * @brief  Disables LCD Window mode.
 * @retval None.
 */
void BSP_LCD_WindowModeDisable(void)
{
  BSP_LCD_SetDisplayWindow(0, 0, BSP_LCD_GetXSize(), BSP_LCD_GetYSize());	    
}


/**  
 * @brief  Displays a bitmap picture loaded in the SPI Flash.
 * @param  Xpos: specifies the X position (in pixels).
 * @param  Ypos: specifies the Y position (in pixels).
 * @param  BmpAddress: Bmp picture address in the SPI Flash.
 * @retval None.
 */
void BSP_LCD_WriteBMP_FAT(uint16_t Xpos, uint16_t Ypos, const char* BmpName)
{
  uint32_t index = 0, size = 0, width=0, height=0;
  uint16_t *pBmpWord=0;
	uint16_t data;
 
  /* Read bitmap width*/
  width  = BmpName[0]+1; 
  /* Read bitmap height*/
  height = BmpName[1]+1; 
	/* Read bitmap size */
	size   = width * height;  /* nb of 16 bits */
	
	if (BSP_LCD_SetDisplayWindow(Xpos, Ypos, width-1 , height-1) != LCD_OK)
	{
			BSP_LCD_WindowModeDisable();
			return;
	}

	pBmpWord = (uint16_t *) (&BmpName[5]);
	/* Send them on the screen */
	for(index = 0; index < size; index++)
	{
		data = (*pBmpWord & 0xFF00)>>8;
		data += (*pBmpWord & 0x00FF)<<8;
		
    BSP_LCD_DrawPixel( ILI9341_NO_CURSOR, ILI9341_NO_CURSOR, data );
		pBmpWord++;
	} 

	BSP_LCD_WindowModeDisable();
}

typedef struct RGB
{
  uint8_t B;
  uint8_t G;
  uint8_t R;
}RGB_typedef;
RGB_typedef *RGB_matrix;


/* This structure is used to control picture cropping (to only display part of big pictures, fitting the LCD screen dimensions) */
static struct {
  uint32_t factor;        /* Only display one out of <factor> pixels. */
  uint32_t line_counter;  /* Count the line position, as the information is not provided by the libJPEG. */
  uint32_t first_row;     /* Used to center the crop. */
  uint32_t first_col;     /* Used to center the crop. */
  uint32_t last_row;     /* Used to center the crop. */
  uint32_t last_col;     /* Used to center the crop. */
} crop;

/**
  * @brief  Draws a 24 Bytes Pixel Line on LCD.
  * @param  Row: pointer to the row to draw.
  * @param  DataLength: length of data.
  * @retval 0 when finish.
  */
static uint8_t BSP_LCD_Write24BPixelLine(uint8_t* Row, uint32_t DataLength)
{
   
  RGB_matrix =  (RGB_typedef*)Row;
  uint16_t  ARGB32Buffer;
  uint32_t counter = 0;
  uint32_t width =  DataLength / 3;
  
  if(((crop.line_counter % crop.factor) != 0) ||  /* If crop factor is > 1, bypass some lines */
    (crop.line_counter < crop.first_row) ||       /* Bypass the first picture rows, to center the crop */
    (crop.line_counter >= crop.last_row))         /* Bypass the last picture rows, to center the crop */
  {
    crop.line_counter++;
    return 0; 
  }
  crop.line_counter++;

  for(counter = 0; counter < width; counter++)
  {
    if ((counter % crop.factor) ||      /* If crop factor is > 1, bypass some columns */
         (counter < crop.first_col) ||  /* Bypass the first columns, to center the crop */
          (counter >= crop.last_col))   /* Bypass the last columns, to center the crop */
    {    
      continue;
    }
    ARGB32Buffer  = (uint16_t)
    (
     (((RGB_matrix[counter].B >> 3)<<11)|
      ((RGB_matrix[counter].G >> 2)<<5)|
      (RGB_matrix[counter].R >> 3))
    );
    BSP_LCD_DrawPixel( ILI9341_NO_CURSOR, ILI9341_NO_CURSOR, ARGB32Buffer );
  }

  return 0;
}




/******************************************************************************
                            Static Function
*******************************************************************************/

/**
  * @brief  Draws a character on LCD.
  * @param  Xpos: specifies the X position (in pixels).
  * @param  Ypos: specifies the Y position (in pixels).
  * @param  c: Pointer to the character data
  * @retval None
  */
static void DrawChar(uint16_t Xpos, uint16_t Ypos, const uint8_t *c)
{
  uint32_t i = 0, j = 0;
  uint16_t height, width;
  uint8_t offset;
  uint8_t *pchar;
  uint32_t line;
  
  height = DrawProp.pFont->Height;
  width  = DrawProp.pFont->Width;
  
  offset =  8 *((width + 7)/8) -  width ;
  
  for(i = 0; i < height; i++)
  {
    pchar = ((uint8_t *)c + (width + 7)/8 * i);
    
    switch(((width + 7)/8))
    {
    case 1:
      line =  pchar[0];
      break;    

    case 2:
      line =  (pchar[0]<< 8) | pchar[1];
      break;
      
    case 3:
    default:
      line =  (pchar[0]<< 16) | (pchar[1]<< 8) | pchar[2];
      break;
    }  
    
    BSP_LCD_SetCursor( Xpos, Ypos );
    for (j = 0; j < width; j++)
    {
      if(line & (1 << (width- j + offset- 1))) 
      {
        BSP_LCD_DrawPixel( ILI9341_NO_CURSOR, ILI9341_NO_CURSOR, DrawProp.TextColor);
      }
      else
      {
        BSP_LCD_DrawPixel( ILI9341_NO_CURSOR, ILI9341_NO_CURSOR, DrawProp.BackColor);
      } 
    }
    Ypos++;
  }
}

/**
  * @brief  Fills a triangle (between 3 points).
  * @param  x1: Point 1 X position (in pixels).
  * @param  y1: Point 1 Y position (in pixels).
  * @param  x2: Point 2 X position (in pixels).
  * @param  y2: Point 2 Y position (in pixels).
  * @param  x3: Point 3 X position (in pixels).
  * @param  y3: Point 3 Y position (in pixels).
  * @retval None
  */
static void FillTriangle(uint16_t x1, uint16_t x2, uint16_t x3, uint16_t y1, uint16_t y2, uint16_t y3)
{ 
  int16_t deltax = 0, deltay = 0, x = 0, y = 0, xinc1 = 0, xinc2 = 0, 
  yinc1 = 0, yinc2 = 0, den = 0, num = 0, numadd = 0, numpixels = 0, 
  curpixel = 0;
  
  deltax = ABS(x2 - x1);        /* The difference between the x's */
  deltay = ABS(y2 - y1);        /* The difference between the y's */
  x = x1;                       /* Start x off at the first pixel */
  y = y1;                       /* Start y off at the first pixel */
  
  if (x2 >= x1)                 /* The x-values are increasing */
  {
    xinc1 = 1;
    xinc2 = 1;
  }
  else                          /* The x-values are decreasing */
  {
    xinc1 = -1;
    xinc2 = -1;
  }
  
  if (y2 >= y1)                 /* The y-values are increasing */
  {
    yinc1 = 1;
    yinc2 = 1;
  }
  else                          /* The y-values are decreasing */
  {
    yinc1 = -1;
    yinc2 = -1;
  }
  
  if (deltax >= deltay)         /* There is at least one x-value for every y-value */
  {
    xinc1 = 0;                  /* Don't change the x when numerator >= denominator */
    yinc2 = 0;                  /* Don't change the y for every iteration */
    den = deltax;
    num = deltax / 2;
    numadd = deltay;
    numpixels = deltax;         /* There are more x-values than y-values */
  }
  else                          /* There is at least one y-value for every x-value */
  {
    xinc2 = 0;                  /* Don't change the x for every iteration */
    yinc1 = 0;                  /* Don't change the y when numerator >= denominator */
    den = deltay;
    num = deltay / 2;
    numadd = deltax;
    numpixels = deltay;         /* There are more y-values than x-values */
  }
  
  for (curpixel = 0; curpixel <= numpixels; curpixel++)
  {
    BSP_LCD_DrawLine(x, y, x3, y3);
    
    num += numadd;              /* Increase the numerator by the top of the fraction */
    if (num >= den)             /* Check if numerator >= denominator */
    {
      num -= den;               /* Calculate the new numerator value */
      x += xinc1;               /* Change the x as appropriate */
      y += yinc1;               /* Change the y as appropriate */
    }
    x += xinc2;                 /* Change the x as appropriate */
    y += yinc2;                 /* Change the y as appropriate */
  } 
}


/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
