#ifndef _CONFIG_FILE_H_
#define _CONFIG_FILE_H_

#include "stdint.h"
#include "main.h"

typedef uint8_t sd_phy_state_t;

#define SD_CSV_PATH         "table.csv"
#define SD_CSV_HEADER       "Time;Drive;Engine;Voltage\n"
#define SD_TXT_PATH         "text.txt"
#define SD_TXT_HEADER       "System Started\n"

#define SD_PHY_INSERTED       0x00
#define SD_PHY_NOT_INSERTED   0x01

#define SD_PHY_LOCKED         0x01
#define SD_PHY_UNLOCKED       0x00

inline sd_phy_state_t SDIsLocked(void){
    return 0;//HAL_GPIO_ReadPin(SD_LOCKED_GPIO_Port, SD_LOCKED_Pin);
}

inline sd_phy_state_t SDIsInserted(void){
    return 0;//HAL_GPIO_ReadPin(SD_EJECT_GPIO_Port, SD_EJECT_Pin);
}

#endif