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
#include "queue.h"
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
typedef struct
{
    char ucMessageID;
    char ucData[ 20 ];
}xMessage;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

QueueHandle_t xQueue1,xQueue2; //data type we will use

xMessage x1;
/* USER CODE END Variables */
/* Definitions for Task_1 */
osThreadId_t Task_1Handle;
const osThreadAttr_t Task_1_attributes = {
  .name = "Task_1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
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

  x1.ucMessageID = 'A';               // Assign a value to ucMessageID
  strcpy(x1.ucData, "Hello, World!");
  	 //create queue of 10 elements it's is 32bit
  xQueue1 = xQueueCreate( 10, sizeof( unsigned long ) );

      if( xQueue1 == NULL )
      {
          /* Queue was not created and must not be used. */
      }

  xQueue2 = xQueueCreate( 10, sizeof( struct xMessage * ) ); //we are creating a queue it's element  is size of ponter to struct

	  if( xQueue2 == NULL )
	  {
		  /* Queue was not created and must not be used. */
	  }
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of Task_1 */
  Task_1Handle = osThreadNew(Task_one, NULL, &Task_1_attributes);

  /* creation of Task_2 */
  Task_2Handle = osThreadNew(Task_Two, NULL, &Task_2_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_Task_one */
/**
  * @brief  Task that send data to the queue
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_Task_one */
//Task 1 know has a higher priority so should be executed all first without interrupted
void Task_one(void *argument)
{
  /* USER CODE BEGIN Task_one */
	BaseType_t ret_val=0;
	uint8_t counter_1=0;
	UBaseType_t queue1_avilable_space;
	UBaseType_t queue2_avilable_space;
	xMessage *pxMessage;
	pxMessage=&x1;
  /* Infinite loop */
  for(;;)
  {
	  if(xQueue1!=NULL){
		  queue1_avilable_space=uxQueueSpacesAvailable(xQueue1);
		  queue2_avilable_space=uxQueueSpacesAvailable(xQueue2);

		  ret_val= xQueueSendToFront( xQueue1,( void * ) &counter_1,350);
		  queue1_avilable_space=uxQueueSpacesAvailable(xQueue1);

		  if(ret_val != pdTRUE){
			  printf("queue send to front Failed");
		  }
		  else{
			  printf("queue send to front sucessfully");
		  }
		  ret_val = xQueueSendToFront( xQueue2, ( void * ) &pxMessage, 350); //push the data of the object created
		  if(ret_val != pdTRUE){
			  printf("queue struct send to front Failed");
		  }
		  else{
			  printf("queue struct send to front sucessfully");
		  }
		  counter_1++;
	  }

  }
  /* USER CODE END Task_one */
}

/* USER CODE BEGIN Header_Task_Two */
/**
* @brief  Task that reads from the queues.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_Task_Two */
void Task_Two(void *argument)
{
  /* USER CODE BEGIN Task_Two */
	//buffer
	BaseType_t ret_val=0;
	uint8_t read_counter_peek;
	xMessage read_struct; //we are having a local struct to copy the value in it after receiving
	uint8_t counter_1; //local buffer we will receive in it
  /* Infinite loop */
  for(;;)
  {
	  if(xQueue1!=NULL){
		  //use xqueuePeek to read the value from queue without removing it
		  if( xQueuePeek(xQueue1,&read_counter_peek,portMAX_DELAY) ){
			  printf("task received peek successfully");
		  }
		  ret_val = xQueueReceive( xQueue1,& counter_1 , portMAX_DELAY); //wait until data avilable in the queue
		  if(pdTRUE !=ret_val){
			  printf("task received failed");
		  }
		  else{
			  printf("task received successfully");
		  }
		  // receving the struct
		  ret_val = xQueueReceive( xQueue2, &read_struct , portMAX_DELAY);
		  if(pdTRUE !=ret_val){
			  printf("task received failed");
		  }
		  else{
			  printf("task received successfully");
		  }
	  }

    osDelay(1);
  }
  /* USER CODE END Task_Two */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

