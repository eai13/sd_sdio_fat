#ifndef DEBUGGERSRC_H
#define DEBUGGERSRC_H

#define ETHERNET_DEBUG

#include "usart.h"
#include "stdint.h"

#define DBG_UART huart1

void print_db(const char * fmt, ...);
void print_wr(const char * fmt, ...);
void print_er(const char * fmt, ...);
void print_in(const char * fmt, ...);

#endif