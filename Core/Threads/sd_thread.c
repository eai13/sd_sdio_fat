// #include "sd_thread.h"
// #include "stdint.h"

// #define CSV_MESSAGE_QUEUE_SIZE 10
// #define TXT_MESSAGE_QUEUE_SIZE 10

// #define TXT_FILE_NAME "text.txt"
// #define CSV_FILE_NAME "table.csv"

// #define MESSAGE_MAX_SIZE    64

// extern char SDPath[4];

// static uint8_t ReadOnly = 0;

// FATFS SDFatFs;

// file_t CSVFile = {
//     .name = CSV_FILE_NAME,
//     .is_opened = CLOSED
// };
// file_t TXTFile = {
//     .name = TXT_FILE_NAME,
//     .is_opened = CLOSED
// };

// osMessageQueueId_t CSVMessageQueue;
// osMessageQueueId_t TXTMessageQueue;

// static WaitForDebugThread(void){
//     osDelay(100);
// }

// static SDErrorHandler(void){
//     while(1) osDelay(5000);
// }

// void ThreadSD(void){
//     CSVFile.queue = osMessageQueueNew(CSV_MESSAGE_QUEUE_SIZE, MESSAGE_MAX_SIZE, NULL);
//     TXTFile.queue = osMessageQueueNew(TXT_MESSAGE_QUEUE_SIZE, MESSAGE_MAX_SIZE, NULL);
//     WaitForDebugThread();
//     if (SDIsInserted() == SD_PHY_INSERTED){
//         if (SDIsLocked() == SD_PHY_UNLOCKED)
//             print_in("SD Inserted READ\\WRITE\r\n");
//         else{
//             print_wr("SD Inserted READONLY\r\n");
//             ReadOnly = 1;
//         }
//     }
//     else{
//         print_er("SD Slot Empty\r\n");
//         SDErrorHandler();
//     }

//     if (f_mount(&SDFatFs, (TCHAR const *)SDPath, 0) != FR_OK){
//         print_er("Unable to open SD card\r\n");
//         SDErrorHandler();
//     }
//     else print_in("SD Card mounted\r\n");

//     print_in("SD Card initialization ended\r\n");
//     HAL_UART_Transmit(&huart1, "hey 1\r\n", 5, 100);
//     if (f_open(&(CSVFile.handle), "tmp.txt", FA_READ) != FR_OK){
//         HAL_UART_Transmit(&huart1, "hey\r\n", 5, 100);
//         // print_er("Unable to open %s\r\n", CSVFile.name);
//     }
//     // else print_in("Successfully opened %s\r\n", CSVFile.name);
//     HAL_UART_Transmit(&huart1, "hey 2\r\n", 5, 100);
//     if (f_open(&TXTFile.handle, TXT_FILE_NAME, FA_WRITE | FA_CREATE_ALWAYS) != FR_OK){
//         // print_er("Unable to open %s\r\n", TXTFile.name);
//         HAL_UART_Transmit(&huart1, "hey\r\n", 5, 100);
//     }
//     // else print_in("Successfully opened %s\r\n", TXTFile.name);
// HAL_UART_Transmit(&huart1, "hey\r\n", 5, 100);
//     f_close(&CSVFile.handle);
//     f_close(&TXTFile.handle);

//     uint8_t buffer[MESSAGE_MAX_SIZE];
//     while(1){
//         // print_in("%d %d %d\r\n", Time.Hours, Time.Minutes, Time.Seconds);
//         osDelay(500);
//     }
// }