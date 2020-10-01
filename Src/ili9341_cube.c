#include "ili9341_cube.h"

void drawPoint(int y, int x, unsigned short color);

LCD_DrvTypeDef   ili9341_drv = 
{
  ili9341_Init,
  ili9341_ReadID,
  ili9341_DisplayOn,
  ili9341_DisplayOff,
  ili9341_SetCursor,
  ili9341_WritePixel,
  ili9341_ReadPixel,
  ili9341_SetDisplayWindow,
  ili9341_DrawHLine,
  ili9341_DrawVLine,
  ili9341_GetLcdPixelWidth,
  ili9341_GetLcdPixelHeight,
  0,
  0,    
};

/**
  * @brief  Power on the LCD.
  * @param  None
  * @retval None
  */
#define ILI9341_INIT_DELAYS 30
void ili9341_Init(void)
{
	
}

/**
  * @brief  Disables the Display.
  * @param  None
  * @retval LCD Register Value.
  */
uint16_t ili9341_ReadID(void)
{

}

/**
  * @brief  Enables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOn(void)
{

}


/**
  * @brief  Disables the Display.
  * @param  None
  * @retval None
  */
void ili9341_DisplayOff(void)
{

}

static uint16_t cursorX;
static uint16_t cursorY;
static uint16_t windowX;
static uint16_t windowY;
static uint16_t windowXend;
static uint16_t windowYend;

static uint8_t ili9341_ram_mode = 0;


void    LCD_IO_Init(void)
{

}
void    LCD_IO_WriteData(uint8_t RegValue)
{

}

void 	LCD_IO_WriteData16(uint16_t RegValue)
{
    if (ili9341_ram_mode)
    {
        drawPoint(cursorY, cursorX, RegValue);
        cursorX++;
        if (cursorX >= windowXend)
        {
            cursorX = windowX;
            cursorY++;
            if (cursorY >= windowYend)
            {
                cursorY = windowY;
            }
        }
    }
}

void     LCD_IO_WriteReg(uint8_t Reg)
{

}

uint32_t LCD_IO_ReadData(uint16_t RegValue, uint8_t ReadSize)
{

}

void     LCD_Delay(uint32_t delay)
{

}



void ili9341_SetCursor(uint16_t Xpos, uint16_t Ypos)
{
	if(((Xpos < ILI9341_LCD_PIXEL_WIDTH) && (Ypos < ILI9341_LCD_PIXEL_HEIGHT)) && 
		((Xpos != ILI9341_NO_CURSOR) && (Ypos != ILI9341_NO_CURSOR)))
	{
        cursorX = Xpos;
        cursorY = Ypos;
	}
	
}


void ili9341_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width, uint16_t Height)
{
	uint16_t Xend = Xpos+Width;
	uint16_t Yend = Ypos+Height;

	if(Xend > ILI9341_LCD_PIXEL_WIDTH) 
		Xend = ILI9341_LCD_PIXEL_WIDTH;
	if(Yend > ILI9341_LCD_PIXEL_HEIGHT)
		Yend = ILI9341_LCD_PIXEL_HEIGHT;
	
	if(Xpos > ILI9341_LCD_PIXEL_WIDTH) 
		Xpos = ILI9341_LCD_PIXEL_WIDTH;
	if(Ypos > ILI9341_LCD_PIXEL_HEIGHT)
		Ypos = ILI9341_LCD_PIXEL_HEIGHT;


    windowX = Xpos;
    windowY = Ypos;
    windowXend = Xend;
    windowYend = Yend;
	
    ili9341_SetCursor(Xpos, Ypos);

}



void ili9341_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t Val)
{
	// If ILI9341_KEEP_CURSOR is used for Xpos or Ypos -> SetCursor does nothing 
	// This allows to write 9341 RAM using HW pixel increment
	ili9341_SetCursor(Xpos, Ypos);
	if(!ili9341_ram_mode) ili9341_WriteReg(LCD_GRAM);
	LCD_IO_WriteData16(Val);
}	

static uint8_t ili9341_readmem_mode = 0;
uint16_t ili9341_ReadPixel(uint16_t Xpos, uint16_t Ypos)
{
  
}	


/**
  * @brief  Draw vertical line.
  * @param  RGB_Code: Specifies the RGB color   
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void ili9341_DrawHLine(uint16_t RGB_Code, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t i = 0;
  
  /* Set Cursor */
  ili9341_SetDisplayWindow(Xpos, Ypos, Length, 1); 
  
  for(i = 0; i < Length; i++)
  {
    /* Write 16-bit GRAM Reg */
    ili9341_WritePixel(ILI9341_NO_CURSOR,ILI9341_NO_CURSOR,RGB_Code);
  }  
}

/**
  * @brief  Draw vertical line.
  * @param  RGB_Code: Specifies the RGB color    
  * @param  Xpos:     specifies the X position.
  * @param  Ypos:     specifies the Y position.
  * @param  Length:   specifies the Line length.  
  * @retval None
  */
void ili9341_DrawVLine(uint16_t RGB_Code, uint16_t Xpos, uint16_t Ypos, uint16_t Length)
{
  uint16_t i = 0;

  
  /* Set Cursor */
  ili9341_SetDisplayWindow(Xpos, Ypos, 0, Length); 

  for(i = 0; i < Length; i++)
  {
    /* Write 16-bit GRAM Reg */
    ili9341_WritePixel(ILI9341_NO_CURSOR,ILI9341_NO_CURSOR,RGB_Code);
  }
  
}


/**
  * @brief  Writes  to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void ili9341_WriteReg(uint8_t LCD_Reg)
{
  //LCD_IO_WriteReg(LCD_Reg);
	ili9341_ram_mode = (LCD_Reg == LCD_GRAM);
	ili9341_readmem_mode = (LCD_Reg == LCD_RAMRD) || (LCD_Reg == LCD_READ_MEM_CONTINUE);
}

/**
  * @brief  Writes data to the selected LCD register.
  * @param  LCD_Reg: address of the selected register.
  * @retval None
  */
void ili9341_WriteData(uint16_t RegValue)
{
  LCD_IO_WriteData(RegValue);
}

/**
  * @brief  Reads the selected LCD Register.
  * @param  RegValue: Address of the register to read
  * @param  ReadSize: Number of bytes to read
  * @retval LCD Register Value.
  */
uint32_t ili9341_ReadData(uint16_t RegValue, uint8_t ReadSize)
{
  /* Read a max of 4 bytes */
 	ili9341_readmem_mode = (RegValue == LCD_RAMRD) || (RegValue == LCD_READ_MEM_CONTINUE);
 return (LCD_IO_ReadData(RegValue, ReadSize));
}

/**
  * @brief  Get LCD PIXEL WIDTH.
  * @param  None
  * @retval LCD PIXEL WIDTH.
  */
uint16_t ili9341_GetLcdPixelWidth(void)
{
  /* Return LCD PIXEL WIDTH */
  return ILI9341_LCD_PIXEL_WIDTH;
}

/**
  * @brief  Get LCD PIXEL HEIGHT.
  * @param  None
  * @retval LCD PIXEL HEIGHT.
  */
uint16_t ili9341_GetLcdPixelHeight(void)
{
  /* Return LCD PIXEL HEIGHT */
  return ILI9341_LCD_PIXEL_HEIGHT;
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

/**
  * @}
  */
  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
