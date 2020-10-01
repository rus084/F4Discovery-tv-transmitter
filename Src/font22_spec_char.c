/**
  ******************************************************************************
  * @file    font22_spec_char.c
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    18-February-2014
  * @brief   This file provides text font22 for STM32xx-EVAL's LCD driver. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2014 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "fonts.h"

/** @addtogroup Utilities
  * @{
  */
  
/** @addtogroup STM32_EVAL
  * @{
  */ 

/** @addtogroup Common
  * @{
  */

/** @addtogroup FONTS
  * @brief      This file provides text font22 for STM32xx-EVAL's LCD driver.
  * @{
  */  

/** @defgroup FONTS_Private_Types
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Defines
  * @{
  */
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Macros
  * @{
  */
/**
  * @}
  */ 
  

/** @defgroup FONTS_Private_Variables
  * @{
  */
const uint8_t Font22_ReturnChar [] = 
{
	// @0 ' ' (16 pixels wide)
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x18, //            ##   
	0x00, 0x18, //            ##   
	0x00, 0x18, //            ##   
	0x01, 0x18, //        #   ##   
	0x02, 0x18, //       #    ##   
	0x07, 0xF8, //      ########   
	0x07, 0xF8, //      ########   
	0x02, 0x00, //       #         
	0x01, 0x00, //        #        
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00  //                               
};

const uint8_t Font22_BackspaceChar [] = 
{
	// @0 ' ' (16 pixels wide)
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x04, 0x00, //      #          
	0x08, 0x00, //     #           
	0x1F, 0xE0, //    ########     
	0x1F, 0xE0, //    ########     
	0x08, 0x00, //     #           
	0x04, 0x00, //      #          
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00, //                 
	0x00, 0x00  //                               
};

/**
  * @}
  */ 


/** @defgroup FONTS_Private_Function_Prototypes
  * @{
  */ 
/**
  * @}
  */ 


/** @defgroup FONTS_Private_Functions
  * @{
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

/**
  * @}
  */

/**
  * @}
  */  
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
