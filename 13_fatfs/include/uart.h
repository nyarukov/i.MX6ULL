/*
 * @Author: Yusaka
 * @Date: 2023-10-05 17:58:33
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 02:22:54
 * @FilePath: /porject/include/uart.h
 * @Description: 
 */

#ifndef __UART_H
#define __UART_H

#include "common.h"


#define UART1_DEBUG 0
#define UART2_DEBUG 1
#define UART3_DEBUG 2

#ifndef DEBUG
#define DEBUG   0
#endif // !

void Serial_Init(void);
void Serial_SendChar(uint8_t ch);
void Serial_SendString(uint8_t *str);
void Serial_SendArray(uint8_t *arr,uint8_t length);
void Serial_Num(uint64_t num);
uint8_t Serial_ReceChar(void);
// uint8_t Uart_RecvString(void);

#endif // !__BSP_LED_H



