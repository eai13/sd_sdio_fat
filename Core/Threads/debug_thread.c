// #include "debug_thread.h"
// #include "debug.h"

// void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart){
//     if (huart == &DEBUG_UART)
//         osSemaphoreRelease(DebugSemaphore);
// }

// void ThreadDebug(void){
//     osDelay(10);
//     HAL_UART_Transmit(&huart1, "Hello from Debug\r\n", 18, 100);
//     DebugQueue = osMessageQueueNew(DEBUG_QUEUE_SIZE, DEBUG_MSG_SIZE, NULL);
//     DebugSemaphore = osSemaphoreNew(1, 1, NULL);
//     uint8_t buffer[DEBUG_MSG_SIZE];
//     while(1){
//         if (osSemaphoreAcquire(DebugSemaphore, 5000) == osOK){
//             if (osMessageQueueGet(DebugQueue, buffer, 0, 5000) == osOK){
//                 if (HAL_UART_Transmit_IT(&DEBUG_UART, buffer, strlen(buffer)) != HAL_OK)
//                     osSemaphoreRelease(DebugSemaphore);
//             }
//             else osSemaphoreRelease(DebugSemaphore);
//         }
//     }
// }