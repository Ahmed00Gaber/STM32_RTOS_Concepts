/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
typedef struct {
	uint32_t ID;
	uint32_t age;
}student_t;

BaseType_t xReturnedAPI;
TaskHandle_t xHandleAPI = NULL;
uint32_t paratmeter_API = 50;

//define object from struct
student_t Ahmed={
	.ID=25,
	.age=35
};

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for Task_1 */
osThreadId_t Task_1Handle;
const osThreadAttr_t Task_1_attributes = {
  .name = "Task_1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for Task_2 */
osThreadId_t Task_2Handle;
const osThreadAttr_t Task_2_attributes = {
  .name = "Task_2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
/* Definitions for myBinarySem01 */
osSemaphoreId_t myBinarySem01Handle;
const osSemaphoreAttr_t myBinarySem01_attributes = {
  .name = "myBinarySem01"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void Task_one_API(void *argument);
/* USER CODE END FunctionPrototypes */

void Task_one(void *argument);
void Task_Two(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of myBinarySem01 */
  myBinarySem01Handle = osSemaphoreNew(1, 1, &myBinarySem01_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_1 */
  Task_1Handle = osThreadNew(Task_one, NULL, &Task_1_attributes);

  /* creation of Task_2 */
  Task_2Handle = osThreadNew(Task_Two, NULL, &Task_2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  xReturnedAPI = xTaskCreate(
		  	  	  	  Task_one_API,       /* Function that implements the task. */
                      "Task1 Gaber",          /* Text name for the task. */
                      128,      /* Stack size in words, not bytes. */
                      (void *) &Ahmed,    /* Parameter passed into the task. */
                      45,/* Priority at which the task is created. */
                      &xHandleAPI );

  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task_one */
/**
  * @brief  Function implementing the Task_1 thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_one */
void Task_one(void *argument)
{
  /* USER CODE BEGIN Task_one */
	uint8_t task1;
  /* Infinite loop */
  for(;;)
  {

	  task1++;//increase variable each time it join Task1
    osDelay(200);
  }
  /* USER CODE END Task_one */
}

/* USER CODE BEGIN Header_Task_Two */
/**
* @brief Function implementing the Task_2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Two */
void Task_Two(void *argument)
{
  /* USER CODE BEGIN Task_Two */
	uint8_t task2;
  /* Infinite loop */
  for(;;)
  {
	task2++;
    osDelay(1000);
  }
  /* USER CODE END Task_Two */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */
void Task_one_API(void *argument){
	uint32_t local_ID = (((student_t *) argument)->ID);
	uint32_t local_age = (((student_t *) argument)->age);
	for(;;)
	  {

	  }
}
/* USER CODE END Application */

