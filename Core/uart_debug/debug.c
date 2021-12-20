#include "debug.h"
#include "debug_thread.h"
#include <stdarg.h>
#include <string.h>

/**
 * @brief for debug print
 * @param str 
 */
void print_db(const char * fmt, ...){
    int8_t buf1[128];
    int8_t buf2[128];
    va_list args;
    va_start(args, fmt);
    snprintf(buf1, sizeof(buf1), "[ %d ]\t\033[1m[DEBUG]\033[0m %ls", HAL_GetTick(), fmt);
    vsnprintf(buf2, sizeof(buf2), buf1, args);
    // osMessageQueuePut(DebugQueue, buf2, 0, 100);
    HAL_UART_Transmit(&DBG_UART, buf2, strlen(buf2), 100);
    va_end(args);
}

/**
 * @brief for warning print
 * @param str 
 */
void print_wr(const char * fmt, ...){
    int8_t buf1[128];
    int8_t buf2[128];
    va_list args;
    va_start(args, fmt);
    snprintf(buf1, sizeof(buf1), "[ %d ]\t\033[33;1m[WARN ]\033[0m %ls", HAL_GetTick(), fmt);
    vsnprintf(buf2, sizeof(buf2), buf1, args);
    // osMessageQueuePut(DebugQueue, buf2, 0, 100);
    HAL_UART_Transmit(&DBG_UART, buf2, strlen(buf2), 100);
    va_end(args);
}

/**
 * @brief for error print
 * @param str 
 */
void print_er(const char * fmt, ...){
    int8_t buf1[128];
    int8_t buf2[128];
    va_list args;
    va_start(args, fmt);
    snprintf(buf1, sizeof(buf1), "[ %d ]\t\033[31;1m[ERROR]\033[0m %ls", HAL_GetTick(), fmt);
    vsnprintf(buf2, sizeof(buf2), buf1, args);
    // osMessageQueuePut(DebugQueue, buf2, 0, 100);
    HAL_UART_Transmit(&DBG_UART, buf2, strlen(buf2), 100);
    va_end(args);
}

/**
 * @brief for info print
 * @param str 
 */
void print_in(const char * fmt, ...){
    int8_t buf1[128];
    int8_t buf2[128];
    va_list args;
    va_start(args, fmt);
    snprintf(buf1, sizeof(buf1), "[ %d ]\t\033[32;1m[INFO ]\033[0m %ls", HAL_GetTick(), fmt);
    vsnprintf(buf2, sizeof(buf2), buf1, args);
    // osMessageQueuePut(DebugQueue, buf2, 0, 100);
    HAL_UART_Transmit(&DBG_UART, buf2, strlen(buf2), 100);
    va_end(args);
}