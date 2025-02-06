/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef uint32_t  u32;
 
typedef uint16_t u16;
 
typedef uint8_t  u8;
 
typedef __IO uint32_t  vu32;
 
typedef __IO uint16_t vu16;
 
typedef __IO uint8_t  vu8;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LCD_BL_Pin GPIO_PIN_15
#define LCD_BL_GPIO_Port GPIOB
#define PF1_Pin GPIO_PIN_2
#define PF1_GPIO_Port GPIOG
#define PF2_Pin GPIO_PIN_3
#define PF2_GPIO_Port GPIOG
#define SCK_Pin GPIO_PIN_4
#define SCK_GPIO_Port GPIOG
#define CSN_Pin GPIO_PIN_5
#define CSN_GPIO_Port GPIOG
#define IUP_Pin GPIO_PIN_6
#define IUP_GPIO_Port GPIOG
#define DRC_Pin GPIO_PIN_7
#define DRC_GPIO_Port GPIOG
#define DRH_Pin GPIO_PIN_8
#define DRH_GPIO_Port GPIOG
#define OSK_Pin GPIO_PIN_6
#define OSK_GPIO_Port GPIOC
#define PF0_Pin GPIO_PIN_8
#define PF0_GPIO_Port GPIOC
#define MRT_Pin GPIO_PIN_9
#define MRT_GPIO_Port GPIOC
#define SDI_Pin GPIO_PIN_8
#define SDI_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
