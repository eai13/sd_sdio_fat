/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "sdio.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "debug.h"
#include "config.h"

// #include "debug_thread.h"
// #include "sd_thread.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
extern char SDPath[4];
FATFS FileSystem;
FIL CSVFile;
uint8_t CSV_opened = 0;
FIL TXTFile;
uint8_t TXT_opened = 0;

uint32_t bw;
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  MX_SDIO_SD_Init();
  MX_USART1_UART_Init();
  MX_FATFS_Init();
  /* USER CODE BEGIN 2 */
  
  if (SDIsInserted() == SD_PHY_INSERTED){
    if (SDIsLocked() == SD_PHY_LOCKED){
      print_wr("SD Card Slot: READONLY\r\n");
      HAL_NVIC_SystemReset();
    }
  }
  else{
    print_er("SD Card Slot: EMPTY\r\n");
    HAL_NVIC_SystemReset();
  }

  FRESULT op_code;

  op_code = f_mount(&FileSystem, (TCHAR const *)SDPath, 0);
  if (op_code != FR_OK){
    print_er("SD Card Mounted with code 0x%X\r\n", op_code);
    HAL_NVIC_SystemReset();
  }
  print_in("SD Card Mounted with code 0x%X\r\n", op_code);

  op_code = f_open(&CSVFile, SD_CSV_PATH, FA_WRITE | FA_CREATE_ALWAYS);
  if (op_code != FR_OK){
    print_er("File %s opened with code 0x%X\r\n", SD_CSV_PATH, op_code);
  }
  else{
    print_in("File %s opened with code 0x%X\r\n", SD_CSV_PATH, op_code);
    CSV_opened = 1;
    op_code = f_write(&CSVFile, SD_CSV_HEADER, sizeof(SD_CSV_HEADER), (void *)&bw);
    if (op_code != FR_OK){
      print_er("File %s header writing with code 0x%X\r\n", SD_CSV_PATH, op_code);
      f_close(&CSVFile);
      CSV_opened = 0;
    }
    else{
      print_in("File %s header writing with code 0x%X\r\n", SD_CSV_PATH, op_code);
      f_close(&CSVFile);
    }
  }

  op_code = f_open(&TXTFile, SD_TXT_PATH, FA_WRITE | FA_CREATE_ALWAYS);
  if (op_code != FR_OK){
    print_er("File %s opened with code 0x%X\r\n", SD_TXT_PATH, op_code);
  }
  else{
    print_in("File %s opened with code 0x%X\r\n", SD_TXT_PATH, op_code);
    TXT_opened = 1;
    op_code = f_write(&TXTFile, SD_TXT_HEADER, sizeof(SD_TXT_HEADER), (void *)&bw);
    if (op_code != FR_OK){
      print_er("File %s header writing with code 0x%X\r\n", SD_TXT_PATH, op_code);
      f_close(&TXTFile);
      TXT_opened = 0;
    }
    else{
      print_in("File %s header writing with code 0x%X\r\n", SD_TXT_PATH, op_code);
      f_close(&TXTFile);
    }
  }
  uint8_t buffer[128];
  while (1)
  {
    if (SDIsInserted() == SD_PHY_INSERTED){
      if (CSV_opened){
        snprintf(buffer, 128, "%d;%d;%d;%d\n", HAL_GetTick(), HAL_GetTick() % 2, HAL_GetTick() % 2, HAL_GetTick() % 24);
        f_open(&CSVFile, SD_CSV_PATH, FA_WRITE | FA_OPEN_APPEND);
        op_code = f_write(&CSVFile, buffer, strlen(buffer), (void *)&bw);
        if (op_code != FR_OK){
          print_er("File %s writing corrupted with code 0x%X\r\n", SD_CSV_PATH, op_code);
          f_close(&CSVFile);
          CSV_opened = 0;
        }
        else{
          print_in("File %s done with code 0x%X\r\n", SD_CSV_PATH, op_code);
          f_close(&CSVFile);
        }
      }
      if (TXT_opened){
        snprintf(buffer, 128, "Time is at %d, some fun number is %d\r\n", HAL_GetTick(), HAL_GetTick() % 42);
        f_open(&TXTFile, SD_TXT_PATH, FA_WRITE | FA_OPEN_APPEND);
        op_code = f_write(&TXTFile, buffer, strlen(buffer), (void *)&bw);
        if (op_code != FR_OK){
          print_er("File %s writing corrupted with code 0x%X\r\n", SD_TXT_PATH, op_code);
          f_close(&TXTFile);
          TXT_opened = 0;
        }
        else{
          print_in("File %s done with code 0x%X\r\n", SD_TXT_PATH, op_code);
          f_close(&TXTFile);
        }
      }
    }
    else{
      print_in("Cannot Find SD Card\r\n");
      print_db(" -----     +------+       -----\r\n");
      print_db("|     |    | | | | \\     |     |\r\n");
      print_db("      |    |        \\          |\r\n");
      print_db("      |    |        |          |\r\n");
      print_db("    --     |   SD   |        --\r\n");
      print_db("   |       |        |       |\r\n");
      print_db("   0       +--------+       0\r\n");
      print_er("SD Card Slot Empty, Rebooting...\r\n");
    }
    HAL_Delay(500);
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 120;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 5;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_3) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
