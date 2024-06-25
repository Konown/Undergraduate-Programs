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
#define PWM1_Pin GPIO_PIN_5
#define PWM1_GPIO_Port GPIOE
#define PWM2_Pin GPIO_PIN_6
#define PWM2_GPIO_Port GPIOE
#define Encoder1_A_Pin GPIO_PIN_0
#define Encoder1_A_GPIO_Port GPIOA
#define Encoder1_B_Pin GPIO_PIN_1
#define Encoder1_B_GPIO_Port GPIOA
#define Encoder2_A_Pin GPIO_PIN_6
#define Encoder2_A_GPIO_Port GPIOA
#define Encoder2_B_Pin GPIO_PIN_7
#define Encoder2_B_GPIO_Port GPIOA
#define KEY_UP_Pin GPIO_PIN_12
#define KEY_UP_GPIO_Port GPIOB
#define KEY0_Pin GPIO_PIN_13
#define KEY0_GPIO_Port GPIOB
#define KEY1_Pin GPIO_PIN_14
#define KEY1_GPIO_Port GPIOB
#define RGB_Pin GPIO_PIN_9
#define RGB_GPIO_Port GPIOD
#define LED0_Pin GPIO_PIN_10
#define LED0_GPIO_Port GPIOD
#define LED1_Pin GPIO_PIN_11
#define LED1_GPIO_Port GPIOD
#define Motor1_IN1_Pin GPIO_PIN_12
#define Motor1_IN1_GPIO_Port GPIOD
#define Motor1_IN2_Pin GPIO_PIN_13
#define Motor1_IN2_GPIO_Port GPIOD
#define Motor2_IN1_Pin GPIO_PIN_14
#define Motor2_IN1_GPIO_Port GPIOD
#define Motor2_IN2_Pin GPIO_PIN_15
#define Motor2_IN2_GPIO_Port GPIOD

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
