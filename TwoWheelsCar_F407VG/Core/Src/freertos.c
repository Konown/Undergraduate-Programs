/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "usart.h"
#include "motor.h"
#include "encoder.h"
#include "myuart.h"
#include "mypid.h"
#include "myrgb.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

// 创建按键事件标志
#define Event_Key0 (0x01<<0)
#define Event_Key1 (0x01<<1)
#define Event_KeyUp (0x01<<2)

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
EventGroupHandle_t Event_Key_Handle = NULL;
/* USER CODE END Variables */
osThreadId defaultTaskHandle;
osThreadId KeyTaskHandle;
osThreadId GetEventTaskHandle;
osThreadId ControlTaskHandle;
osThreadId SendTaskHandle;
osThreadId AnalysisTaskHandle;
osTimerId MyTimer1Handle;
osTimerId MyTimer2Handle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);
void StartKeyTask(void const * argument);
void StartGetEventTask(void const * argument);
void StartControlTask(void const * argument);
void StartSendTask(void const * argument);
void StartAnalysisTask(void const * argument);
void MyTimer1_Callback(void const * argument);
void MyTimer2_Callback2(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* GetTimerTaskMemory prototype (linked to static allocation support) */
void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize );

/* USER CODE BEGIN GET_IDLE_TASK_MEMORY */
static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize )
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END GET_IDLE_TASK_MEMORY */

/* USER CODE BEGIN GET_TIMER_TASK_MEMORY */
static StaticTask_t xTimerTaskTCBBuffer;
static StackType_t xTimerStack[configTIMER_TASK_STACK_DEPTH];

void vApplicationGetTimerTaskMemory( StaticTask_t **ppxTimerTaskTCBBuffer, StackType_t **ppxTimerTaskStackBuffer, uint32_t *pulTimerTaskStackSize )
{
  *ppxTimerTaskTCBBuffer = &xTimerTaskTCBBuffer;
  *ppxTimerTaskStackBuffer = &xTimerStack[0];
  *pulTimerTaskStackSize = configTIMER_TASK_STACK_DEPTH;
  /* place for user code */
}
/* USER CODE END GET_TIMER_TASK_MEMORY */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  Event_Key_Handle = xEventGroupCreate();
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of MyTimer1 */
  osTimerDef(MyTimer1, MyTimer1_Callback);
  MyTimer1Handle = osTimerCreate(osTimer(MyTimer1), osTimerPeriodic, NULL);

  /* definition and creation of MyTimer2 */
  osTimerDef(MyTimer2, MyTimer2_Callback2);
  MyTimer2Handle = osTimerCreate(osTimer(MyTimer2), osTimerPeriodic, NULL);

  /* USER CODE BEGIN RTOS_TIMERS */
  osTimerStart(MyTimer1Handle, 1000);
  osTimerStart(MyTimer2Handle, 50);
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
  osThreadDef(defaultTask, StartDefaultTask, osPriorityIdle, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* definition and creation of KeyTask */
  osThreadDef(KeyTask, StartKeyTask, osPriorityBelowNormal, 0, 128);
  KeyTaskHandle = osThreadCreate(osThread(KeyTask), NULL);

  /* definition and creation of GetEventTask */
  osThreadDef(GetEventTask, StartGetEventTask, osPriorityBelowNormal, 0, 128);
  GetEventTaskHandle = osThreadCreate(osThread(GetEventTask), NULL);

  /* definition and creation of ControlTask */
  osThreadDef(ControlTask, StartControlTask, osPriorityHigh, 0, 512);
  ControlTaskHandle = osThreadCreate(osThread(ControlTask), NULL);

  /* definition and creation of SendTask */
  osThreadDef(SendTask, StartSendTask, osPriorityLow, 0, 512);
  SendTaskHandle = osThreadCreate(osThread(SendTask), NULL);

  /* definition and creation of AnalysisTask */
  osThreadDef(AnalysisTask, StartAnalysisTask, osPriorityAboveNormal, 0, 512);
  AnalysisTaskHandle = osThreadCreate(osThread(AnalysisTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_StartKeyTask */
/**
* @brief Function implementing the KeyTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartKeyTask */
void StartKeyTask(void const * argument)
{
  /* USER CODE BEGIN StartKeyTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(50);
//    HAL_UART_Transmit_DMA(&huart2, "abc\n", 4);
    if(HAL_GPIO_ReadPin(KEY0_GPIO_Port, KEY0_Pin) == 0){
        xEventGroupSetBits(Event_Key_Handle, Event_Key0);
    }
    else if(HAL_GPIO_ReadPin(KEY1_GPIO_Port, KEY1_Pin) == 0){
        xEventGroupSetBits(Event_Key_Handle, Event_Key1);
    }
    else if(HAL_GPIO_ReadPin(KEY_UP_GPIO_Port, KEY_UP_Pin) == 1){
        xEventGroupSetBits(Event_Key_Handle, Event_KeyUp);
    }

  }
  /* USER CODE END StartKeyTask */
}

/* USER CODE BEGIN Header_StartGetEventTask */
/**
* @brief Function implementing the GetEventTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartGetEventTask */
void StartGetEventTask(void const * argument)
{
  /* USER CODE BEGIN StartGetEventTask */
  EventBits_t myEventBits_1;
  /* Infinite loop */
  for(;;)
  {
      myEventBits_1 = xEventGroupWaitBits(Event_Key_Handle, Event_Key0|Event_Key1|Event_KeyUp, pdTRUE, pdFALSE, portMAX_DELAY);
      if(myEventBits_1 == Event_Key0){
//          Back_Slow(RightWheel, 500);
//          Forward_Slow(RightWheel, 1000);
          RightSpeedPid.Sv = 400;
          LeftSpeedPid.Sv = -200;

          HAL_GPIO_WritePin(LED0_GPIO_Port, LED0_Pin, GPIO_PIN_RESET);
      }
      else if(myEventBits_1 == Event_Key1){
//          Back(1000);
          HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET);
      }
      else if(myEventBits_1 == Event_KeyUp){
          Stop();
          HAL_GPIO_WritePin(GPIOD, LED0_Pin|LED1_Pin, GPIO_PIN_SET);
      }
    osDelay(50);
  }
  /* USER CODE END StartGetEventTask */
}

/* USER CODE BEGIN Header_StartControlTask */
/**
* @brief Function implementing the ControlTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartControlTask */
void StartControlTask(void const * argument)
{
  /* USER CODE BEGIN StartControlTask */
  /* Infinite loop */
  for(;;)
  {
      MY_ROBOT_Kinematics();
      osDelay(20);
  }
  /* USER CODE END StartControlTask */
}

/* USER CODE BEGIN Header_StartSendTask */
/**
* @brief Function implementing the SendTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartSendTask */
void StartSendTask(void const * argument)
{
  /* USER CODE BEGIN StartSendTask */
  /* Infinite loop */
  for(;;)
  {
//    mydebug_send_motor(RightSpeedPid.Pv, RightSpeedPid.SEk, 0xF1);    // m/s -> mm/s 上传上位�???????????
//      mydebug_send_motor(R_Vel.TG_IX, R_Vel.TG_IW, 0xF1);

      ROBOT_SendDataToRos();
//    mydebug_send_motor(LeftSpeedPid.Pv, LeftSpeedPid.Out, 0xF2);    // m/s -> mm/s 上传上位�???????????
    osDelay(20);
  }
  /* USER CODE END StartSendTask */
}

/* USER CODE BEGIN Header_StartAnalysisTask */
/**
* @brief Function implementing the AnalysisTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartAnalysisTask */
void StartAnalysisTask(void const * argument)
{
  /* USER CODE BEGIN StartAnalysisTask */
  /* Infinite loop */
  for(;;)
  {
//      Uart2_Str.Analysis_function();
    osDelay(20);
  }
  /* USER CODE END StartAnalysisTask */
}

/* MyTimer1_Callback function */
void MyTimer1_Callback(void const * argument)
{
  /* USER CODE BEGIN MyTimer1_Callback */
  HAL_GPIO_TogglePin(LED0_GPIO_Port, LED0_Pin);
  /* USER CODE END MyTimer1_Callback */
}

/* MyTimer2_Callback2 function */
void MyTimer2_Callback2(void const * argument)
{
  /* USER CODE BEGIN MyTimer2_Callback2 */

  /* USER CODE END MyTimer2_Callback2 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */
