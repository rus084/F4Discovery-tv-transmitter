/**
  ******************************************************************************
  * @file    st25_discovery.h 
  * @author  MMY Application Team
  * @version $Revision$
  * @date    $Date$
  * @brief   This file contains definitions for ST25Dx-Discovery Kit LEDs,
  *          push-buttons hardware resources.
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
#ifndef __ST25_DISCOVERY_H
#define __ST25_DISCOVERY_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
//#include "stm32f4xx_hal.h"
#include "stdint.h"
#if defined(USE_NFCTAG) && defined(USE_ST25DV)
  #include "st25dv.h"
#endif
   
/** @addtogroup BSP
  * @{
  */
  
/** @addtogroup ST25_DISCOVERY_BSP
  * @{
  */
   
/** @addtogroup ST25_DISCOVERY_LOW_LEVEL
  * @{
  */

/**
  * @brief 
  */
typedef enum 
{
  LED2 = 0,
  LED3
}Led_TypeDef;

typedef enum 
{  
  BUTTON_KEY = 0,
  JOYSTICK_SEL = 1,
  JOYSTICK_LEFT = 2,
  JOYSTICK_RIGHT = 3,
  JOYSTICK_UP = 4,
  JOYSTICK_DOWN = 5,
}Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
}ButtonMode_TypeDef; 
    
/**
 * @brief  NFC04A1 Ack Nack enumerator definition
 */
typedef enum 
{
  I2CANSW_ACK = 0,
  I2CANSW_NACK
}ST25_DISCOVERY_I2CANSW_TypeDef;


#define LEDn                                         2

#define LED2_PIN                                     GPIO_PIN_4
#define LED2_GPIO_PORT                               GPIOC
#define LED2_GPIO_CLK_ENABLE()                       __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED2_GPIO_CLK_DISABLE()                      __HAL_RCC_GPIOC_CLK_DISABLE()  

#define LED3_PIN                                     GPIO_PIN_13
#define LED3_GPIO_PORT                               GPIOC
#define LED3_GPIO_CLK_ENABLE()                       __HAL_RCC_GPIOC_CLK_ENABLE()  
#define LED3_GPIO_CLK_DISABLE()                      __HAL_RCC_GPIOC_CLK_DISABLE()  


#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LED2_GPIO_CLK_ENABLE();  \
                                            if((__INDEX__) == 1) LED3_GPIO_CLK_ENABLE();  \
                                            }while(0)
#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) LED2_GPIO_CLK_DISABLE();  \
                                            if((__INDEX__) == 0) LED3_GPIO_CLK_DISABLE();  \
                                            }while(0)

  // JOYSTICK


#define BUTTONn                                      6

/**
 * @brief Wakeup push-button
 */
#define KEY_BUTTON_PIN                               GPIO_PIN_14
#define KEY_BUTTON_GPIO_PORT                         GPIOC
#define KEY_BUTTON_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOC_CLK_ENABLE()
#define KEY_BUTTON_GPIO_CLK_DISABLE()                __HAL_RCC_GPIOC_CLK_DISABLE()
#define KEY_BUTTON_EXTI_IRQn                         EXTI0_IRQn

#define JOYSTICK_GPIO_CLK_ENABLE()                   __HAL_RCC_GPIOE_CLK_ENABLE()
#define JOYSTICK_GPIO_CLK_DISABLE()                  __HAL_RCC_GPIOE_CLK_DISABLE()

#define JOYSTICK_SEL_GPIO_PIN                        GPIO_PIN_8
#define JOYSTICK_SEL_GPIO_PORT                       GPIOE

#define JOYSTICK_LEFT_GPIO_PIN                       GPIO_PIN_9
#define JOYSTICK_LEFT_GPIO_PORT                      GPIOE

#define JOYSTICK_RIGHT_GPIO_PIN                      GPIO_PIN_11
#define JOYSTICK_RIGHT_GPIO_PORT                     GPIOE

#define JOYSTICK_UP_GPIO_PIN                         GPIO_PIN_10
#define JOYSTICK_UP_GPIO_PORT                        GPIOE

#define JOYSTICK_DOWN_GPIO_PIN                       GPIO_PIN_12
#define JOYSTICK_DOWN_GPIO_PORT                      GPIOE


#define BUTTONx_GPIO_CLK_ENABLE(__INDEX__)     do{if((__INDEX__) == 0) KEY_BUTTON_GPIO_CLK_ENABLE(); else \
                                                  if((__INDEX__) >= 1) JOYSTICK_GPIO_CLK_ENABLE(); \
                                                 }while(0)
#define BUTTONx_GPIO_CLK_DISABLE(__INDEX__)    do{if((__INDEX__) == 0) KEY_BUTTON_GPIO_CLK_DISABLE(); \
                                                  if((__INDEX__) >= 1) (JOYSTICK_GPIO_CLK_DISABLE); \
                                                 }while(0)


/* Exported constanIO --------------------------------------------------------*/
#define TS_I2C_ADDRESS                               0x82


/*############################### I2Cx #######################################*/
/* User can use this section to tailor I2C1 instance used and associated 
   resources */
/*********************** TSCR I2C ***********************/
#ifdef HAL_I2C_MODULE_ENABLED
#define DISCOVERY_I2C1                               I2C1
#define DISCOVERY_I2C1_CLOCK_ENABLE()                __HAL_RCC_I2C1_CLK_ENABLE()
#define DISCOVERY_I2C1_FORCE_RESET()                 __HAL_RCC_I2C1_FORCE_RESET()
#define DISCOVERY_I2C1_RELEASE_RESET()               __HAL_RCC_I2C1_RELEASE_RESET()
#define DISCOVERY_I2C1_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define DISCOVERY_I2C1_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE() 
#define DISCOVERY_I2C1_SDA_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()

/* Definition for DISCO I2C1 Pins */
#define DISCOVERY_I2C1_SCL_PIN                       GPIO_PIN_6
#define DISCOVERY_I2C1_SCL_GPIO_PORT                 GPIOB
#define DISCOVERY_I2C1_SCL_SDA_AF                    GPIO_AF4_I2C1
#define DISCOVERY_I2C1_SDA_PIN                       GPIO_PIN_7
#define DISCOVERY_I2C1_SDA_GPIO_PORT                 GPIOB

/* Definition for TS I2C's NVIC */
#define DISCOVERY_I2C1_EV_IRQn                       I2C1_EV_IRQn
#define DISCOVERY_I2C1_ER_IRQn                       I2C1_ER_IRQn

/*********************** NFCTAG I2C ***********************/
#define DISCOVERY_I2C2                               I2C2
#define DISCOVERY_I2C2_CLOCK_ENABLE()                __HAL_RCC_I2C2_CLK_ENABLE()
#define DISCOVERY_I2C2_FORCE_RESET()                 __HAL_RCC_I2C2_FORCE_RESET()
#define DISCOVERY_I2C2_RELEASE_RESET()               __HAL_RCC_I2C2_RELEASE_RESET()
#define DISCOVERY_I2C2_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define DISCOVERY_I2C2_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE() 
#define DISCOVERY_I2C2_SDA_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()
#define DISCOVERY_I2C2_SCL_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()

/* Definition for DISCO I2C2 Pins */
#define DISCOVERY_I2C2_SCL_PIN                       GPIO_PIN_10
#define DISCOVERY_I2C2_SCL_GPIO_PORT                 GPIOB
#define DISCOVERY_I2C2_SDA_PIN                       GPIO_PIN_11
#define DISCOVERY_I2C2_SDA_GPIO_PORT                 GPIOB
#define DISCOVERY_I2C2_SCL_AF                        GPIO_AF4_I2C2
#define DISCOVERY_I2C2_SDA_AF                        GPIO_AF4_I2C2

#define DISCOVERY_I2C2_SPEED                         400000

#if defined(USE_ST25DV)
  #define NFCMEM_I2C_TIMEOUT                         ST25DV_I2C_TIMEOUT
#endif

/*********************** DPOT I2C ***********************/
#define DISCOVERY_I2C3                               I2C3
#define DISCOVERY_I2C3_CLOCK_ENABLE()                __HAL_RCC_I2C3_CLK_ENABLE()
#define DISCOVERY_I2C3_FORCE_RESET()                 __HAL_RCC_I2C3_FORCE_RESET()
#define DISCOVERY_I2C3_RELEASE_RESET()               __HAL_RCC_I2C3_RELEASE_RESET()
#define DISCOVERY_I2C3_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOC_CLK_ENABLE()
#define DISCOVERY_I2C3_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE() 
#define DISCOVERY_I2C3_SDA_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOC_CLK_DISABLE()

/* Definition for DPOT DISCO I2Cx Pins */
#define DISCOVERY_I2C3_SCL_PIN                       GPIO_PIN_8
#define DISCOVERY_I2C3_SCL_GPIO_PORT                 GPIOA
#define DISCOVERY_I2C3_SCL_SDA_AF                    GPIO_AF4_I2C3
#define DISCOVERY_I2C3_SDA_PIN                       GPIO_PIN_9
#define DISCOVERY_I2C3_SDA_GPIO_PORT                 GPIOC

/* Definition for DPOT I2C's NVIC */
#define DISCOVERY_I2C3_EV_IRQn                       I2C3_EV_IRQn
#define DISCOVERY_I2C3_ER_IRQn                       I2C3_ER_IRQn

#define DISCOVERY_DPOT_I2C_ADDR AD5161_ADDR0

/* I2C clock speed configuration (in Hz) 
  WARNING: 
   Make sure that this define is not already declared in other files.
   It can be used in parallel by other modules. */
#ifndef BSP_I2C_SPEED
 #define BSP_I2C_SPEED                               100000
#endif /* BSP_I2C_SPEED */

/*<! The value of the timeout for I2C waiting loops */
#define I2Cx_TIMEOUT                                 0x64
#endif
/*############################### SPIx #######################################*/
#ifdef HAL_SPI_MODULE_ENABLED
#define DISCOVERY_SPI2                               SPI2
#define DISCOVERY_SPI2_CLK_ENABLE()                  __HAL_RCC_SPI2_CLK_ENABLE()
#define DISCOVERY_SPI2_MISO_MOSI_GPIO_PORT           GPIOC                      /* GPIOC */
#define DISCOVERY_SPI2_SCK_NSS_GPIO_PORT             GPIOB                      /* GPIOB */
#define DISCOVERY_SPI2_AF                            GPIO_AF5_SPI2
#define DISCOVERY_SPI2_SCK_NSS_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOB_CLK_ENABLE()
#define DISCOVERY_SPI2_SCK_NSS_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOB_CLK_DISABLE()
#define DISCOVERY_SPI2_MISO_MOSI_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOC_CLK_ENABLE()
#define DISCOVERY_SPI2_MISO_MOSI_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOC_CLK_DISABLE()
#define DISCOVERY_SPI2_SCK_PIN                       GPIO_PIN_13                 /* PB.13 */
#define DISCOVERY_SPI2_NSS_PIN                       GPIO_PIN_12                 /* PB.12 */
#define DISCOVERY_SPI2_MISO_PIN                      GPIO_PIN_2                 /* PC.02 */
#define DISCOVERY_SPI2_MOSI_PIN                      GPIO_PIN_3                 /* PC.03 */

#define DISCOVERY_SPI3                               SPI3
#define DISCOVERY_SPI3_CLK_ENABLE()                  __HAL_RCC_SPI3_CLK_ENABLE()
#define DISCOVERY_SPI3_GPIO_PORT                     GPIOC                      /* GPIOC */
#define DISCOVERY_SPI3_AF                            GPIO_AF6_SPI3
#define DISCOVERY_SPI3_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOC_CLK_ENABLE()
#define DISCOVERY_SPI3_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOC_CLK_DISABLE()
#define DISCOVERY_SPI3_SCK_PIN                       GPIO_PIN_10                 /* PC.10 */
#define DISCOVERY_SPI3_MISO_PIN                      GPIO_PIN_11                 /* PC.11 */
#define DISCOVERY_SPI3_MOSI_PIN                      GPIO_PIN_12                 /* PC.12 */
/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */   
#define SPIx_TIMEOUT_MAX                             ((uint32_t)0x1000)
#endif

/*################################ ADC1 ######################################*/
#ifdef HAL_ADC_MODULE_ENABLED
/**
  * @brief  ADC Interface pins
  *         used to detect motion of Joystick available on Adafruit 1.8" TFT shield
  */
  typedef enum 
{
  ADC1_CHANNEL_8 = 0,
  ADC1_CHANNEL_9 = 1,
  ADC1_CHANNEL_15 = 2
}ADC1_CHANNEL_TypeDef;

#define DISCOVERY_ADCx                               ADC1
#define DISCOVERY_ADCx_CLK_ENABLE()                  __HAL_RCC_ADC1_CLK_ENABLE()
#define DISCOVERY_ADCx_CLK_DISABLE()                 __HAL_RCC_ADC1_CLK_DISABLE()

#define ADC1_CHANNELn                                3
#define ADC1_CHANNEL_LIST                            {ADC_CHANNEL_15,ADC_CHANNEL_8,ADC_CHANNEL_9}

#define ADC1_CHANNEL_8_PIN                           GPIO_PIN_0
#define ADC1_CHANNEL_8_GPIO_PORT                     GPIOB
#define ADC1_CHANNEL_8_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOB_CLK_ENABLE()  
#define ADC1_CHANNEL_8_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOB_CLK_DISABLE()  

#define ADC1_CHANNEL_9_PIN                           GPIO_PIN_1
#define ADC1_CHANNEL_9_GPIO_PORT                     GPIOB
#define ADC1_CHANNEL_9_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOB_CLK_ENABLE()  
#define ADC1_CHANNEL_9_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOB_CLK_DISABLE()  

#define ADC1_CHANNEL_15_PIN                          GPIO_PIN_5
#define ADC1_CHANNEL_15_GPIO_PORT                    GPIOC
#define ADC1_CHANNEL_15_GPIO_CLK_ENABLE()            __HAL_RCC_GPIOC_CLK_ENABLE()  
#define ADC1_CHANNEL_15_GPIO_CLK_DISABLE()           __HAL_RCC_GPIOC_CLK_DISABLE()  


#define ADC1_CHANNELx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) (ADC1_CHANNEL_8_GPIO_CLK_ENABLE()); else \
                                            if((__INDEX__) == 1) (ADC1_CHANNEL_9_GPIO_CLK_ENABLE()); \
                                            if((__INDEX__) == 2) (ADC1_CHANNEL_15_GPIO_CLK_ENABLE()); \
                                            }while(0)
#define ADC1_CHANNELx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) (ADC1_CHANNEL_8_GPIO_CLK_DISABLE()); else \
                                            if((__INDEX__) == 1) (ADC1_CHANNEL_9_GPIO_CLK_DISABLE()); \
                                            if((__INDEX__) == 2) (ADC1_CHANNEL_15_GPIO_CLK_DISABLE()); \
                                            }while(0)
#endif


/*################################ IOE #######################################*/
/** 
  * @brief  IOE Control pin  
  */ 
/* Definition for external IT for STMPE811 */
#define STMPE811_INT_PIN                             GPIO_PIN_5
#define STMPE811_INT_GPIO_PORT                       GPIOB
#define STMPE811_INT_CLK_ENABLE()                    __HAL_RCC_GPIOB_CLK_ENABLE()
#define STMPE811_INT_CLK_DISABLE()                   __HAL_RCC_GPIOB_CLK_DISABLE()
#define STMPE811_INT_EXTI                            EXTI15_10_IRQn
#define STMPE811_INT_EXTIHandler                     EXTI15_10_IRQHandler

/*################################ LCD #######################################*/
#if defined(HAL_SPI_MODULE_ENABLED) && defined(USE_LCD)
/* Set WRX High to send data */
#define LCD_WRX_LOW()      HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_RESET)
#define LCD_WRX_HIGH()     HAL_GPIO_WritePin(LCD_WRX_GPIO_PORT, LCD_WRX_PIN, GPIO_PIN_SET)
#define LCD_WRX_GPIO_CLK_ENABLE()                    __HAL_RCC_GPIOC_CLK_ENABLE()
#define LCD_WRX_GPIO_CLK_DISABLE()                   __HAL_RCC_GPIOC_CLK_DISABLE()

// Use HW control for CS, defines empty SW support
#define LCD_CS_LOW()             HAL_GPIO_WritePin(DISCOVERY_SPI2_SCK_NSS_GPIO_PORT, DISCOVERY_SPI2_NSS_PIN, GPIO_PIN_RESET)         
#define LCD_CS_HIGH()           HAL_GPIO_WritePin(DISCOVERY_SPI2_SCK_NSS_GPIO_PORT, DISCOVERY_SPI2_NSS_PIN, GPIO_PIN_SET) 
#define LCD_NCS_GPIO_CLK_ENABLE() __HAL_RCC_GPIOB_CLK_ENABLE()


/** 
  * @brief  LCD Command/data pin  
  */
#define LCD_WRX_PIN                                  GPIO_PIN_0
#define LCD_WRX_GPIO_PORT                            GPIOC
#define LCD_WRX_GPIO_CLK_ENABLE()                    __HAL_RCC_GPIOC_CLK_ENABLE()
#define LCD_WRX_GPIO_CLK_DISABLE()                   __HAL_RCC_GPIOC_CLK_DISABLE()
#endif
/*################################ GPO NFCMEM #######################################*/
/** 
  * @brief  GPO Input pin  
  */
#ifdef USE_NFCTAG
#define NFCMEM_GPO_PIN                             GPIO_PIN_15
#define NFCMEM_GPO_PIN_PORT                        GPIOE
#define NFCMEM_GPO_CLK_ENABLE()                    __HAL_RCC_GPIOE_CLK_ENABLE()
#define NFCMEM_GPO_CLK_DISABLE()                   __HAL_RCC_GPIOE_CLK_DISABLE()
#define NFCMEM_GPO_EXTI                            EXTI15_10_IRQn
#define NFCMEM_GPO_EXTIHandler                     EXTI15_10_IRQHandler

/*################################ SPARE NFCMEM #######################################*/
/** 
  * @brief  SPARE Control pin  
  */
#define NFCMEM_SPARE_PIN                             GPIO_PIN_7
#define NFCMEM_SPARE_PIN_PORT                        GPIOE
#define NFCMEM_SPARE_CLK_ENABLE()                    __HAL_RCC_GPIOE_CLK_ENABLE()
#define NFCMEM_SPARE_CLK_DISABLE()                   __HAL_RCC_GPIOE_CLK_DISABLE()
#define NFCMEM_SPARE_EXTI                            EXTI9_5_IRQn
#define NFCMEM_SPARE_EXTIHandler                     EXTI9_5_IRQHandler
  
#if defined(USE_ST25DV) 
/** 
  * @brief  ST25DV LPD wrapper  
  */
  #define NFCMEM_LPD_PIN                             NFCMEM_SPARE_PIN
  #define NFCMEM_LPD_PIN_PORT                        NFCMEM_SPARE_PIN_PORT
  #define NFCMEM_LPD_CLK_ENABLE()                    NFCMEM_SPARE_CLK_ENABLE()
  #define NFCMEM_LPD_CLK_DISABLE()                   NFCMEM_SPARE_CLK_DISABLE()
  #define NFCMEM_LPD_EXTI                            NFCMEM_SPARE_EXTI
  #define NFCMEM_LPD_EXTIHandler                     NFCMEM_SPARE_EXTIHandler
#endif

/*########################## MEMORY NFCMEM WRAPPER #################################*/
#if defined(USE_ST25DV)
/** 
  * @brief  NFCMEM wrapper  
  */
  #define NFCMEM_IO_Init                             ST25DV_IO_Init
  #define NFCMEM_IO_MemWrite                         ST25DV_IO_MemWrite
  #define NFCMEM_IO_MemRead                          ST25DV_IO_MemRead
  #define NFCMEM_IO_Read                             ST25DV_IO_Read
  #define NFCMEM_IO_IsNacked                         ST25DV_IO_IsNacked
  #define NFCMEM_IO_IsDeviceReady                    ST25DV_IO_IsDeviceReady
#endif
#endif

uint32_t      BSP_GetVersion(void);  
void          BSP_LED_Init(Led_TypeDef Led);
void          BSP_LED_DeInit(Led_TypeDef Led);
void          BSP_LED_On(Led_TypeDef Led);
void          BSP_LED_Off(Led_TypeDef Led);
void          BSP_LED_Toggle(Led_TypeDef Led);
void          BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef ButtonMode);
uint32_t      BSP_PB_GetState(Button_TypeDef Button);
#if defined(USE_NFCTAG) && defined(USE_ST25DV)
void          BSP_GPO_Init( uint32_t it_mode );
void          BSP_LPD_Init( void );
GPIO_PinState BSP_LPD_ReadPin( void );
void          BSP_LPD_WritePin( GPIO_PinState LpdPinState );
#endif
#if defined(HAL_ADC_MODULE_ENABLED) && defined(USE_ST25DV)
uint8_t       BSP_ST25DV_EH_Init(void);
void          BSP_ST25DV_EH_Measure(uint16_t *values);
void          BSP_ST25DV_EH_DeInit(void);
#endif
#if defined(HAL_SPI_MODULE_ENABLED) && (USE_LCD)
void          BSP_LCD_LowFreq(void);
void          BSP_LCD_HighFreq(void);
#endif
#ifdef HAL_I2C_MODULE_ENABLED
void          BSP_I2C2_ReInit( void );
#endif

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

#endif /* __ST25_DISCOVERY_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
