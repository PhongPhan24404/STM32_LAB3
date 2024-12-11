/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
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
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

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
/* USER CODE BEGIN Private defines */
#define SEG1_0 GPIO_PIN_0
#define SEG1_1 GPIO_PIN_1
#define SEG1_2 GPIO_PIN_2
#define SEG1_3 GPIO_PIN_3
#define SEG1_4 GPIO_PIN_4
#define SEG1_5 GPIO_PIN_5
#define SEG1_6 GPIO_PIN_6
#define SEG2_0 GPIO_PIN_7
#define SEG2_1 GPIO_PIN_8
#define SEG2_2 GPIO_PIN_9
#define SEG2_3 GPIO_PIN_10
#define SEG2_4 GPIO_PIN_11
#define SEG2_5 GPIO_PIN_12
#define SEG2_6 GPIO_PIN_13
#define EN0 GPIO_PIN_8
#define EN1 GPIO_PIN_9
#define EN2 GPIO_PIN_10
#define EN3 GPIO_PIN_11


#define BUT1 GPIO_PIN_13
#define BUT2 GPIO_PIN_14
#define BUT3 GPIO_PIN_15
#define REDA GPIO_PIN_1
#define REDB GPIO_PIN_4
#define YELLOWA GPIO_PIN_2
#define YELLOWB GPIO_PIN_6
#define GREENA GPIO_PIN_3
#define GREENB GPIO_PIN_7


/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
