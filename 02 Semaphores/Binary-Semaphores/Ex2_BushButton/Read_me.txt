// app on counter semaphores 

We have 2 tasks and INTR: EXternal INTR on pin0 (Bushbutton) will release the binary smaphore so task2 will be executed
Notes:
//it's executed in stm32fxx_it.h 

        extern osSemaphoreId_t myBinarySem01Handle; //definting the Type + include "cmsis_v2.h"
        void EXTI0_IRQHandler(void)
        {
        /* USER CODE BEGIN EXTI0_IRQn 0 */

        /* USER CODE END EXTI0_IRQn 0 */
        HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
        /* USER CODE BEGIN EXTI0_IRQn 1 */
        osSemaphoreRelease(myBinarySem01Handle);
        /* USER CODE END EXTI0_IRQn 1 */
        }