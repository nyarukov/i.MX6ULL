/*
 * @Author: Yusaka
 * @Date: 2023-10-05 17:58:33
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 02:22:58
 * @FilePath: /porject/src/uart.c
 * @Description: 
 */

#include "uart.h"


void Serial_Init(void)
{

#if (DEBUG==UART1_DEBUG)
    static __IO u32 *SW_MUX_CTL_PAD_UART1_TX_DATA = (__IO u32*)(0x20E0084);
    static __IO u32 *SW_MUX_CTL_PAD_UART1_RX_DATA = (__IO u32*)(0x20E0088);
    static __IO u32 *UART1_RX_DATA_SELECT_INPUT = (__IO u32*)(0x20E0624);

    *SW_MUX_CTL_PAD_UART1_TX_DATA=0;
    *SW_MUX_CTL_PAD_UART1_RX_DATA=0;
    *UART1_RX_DATA_SELECT_INPUT=3;
    
    UART1->UCR2 |= (1<<14)|(1<<5)|(1<<2)|(1<<1);
    UART1->UCR3 |= (1<<2);
    UART1->UFCR = (5<<7);
    UART1->UBIR=71;
    UART1->UBMR=3124;
    UART1->UCR1 |= (1<<0);
#elif (DEBUG==UART2_DEBUG)
    static __IO u32 *SW_MUX_CTL_PAD_UART2_TX_DATA = (__IO u32*)(0x20E0094);
    static __IO u32 *SW_MUX_CTL_PAD_UART2_RX_DATA = (__IO u32*)(0x20E0098);
    static __IO u32 *UART2_RX_DATA_SELECT_INPUT = (__IO u32*)(0x20E062C);

    *SW_MUX_CTL_PAD_UART2_TX_DATA=0;
    *SW_MUX_CTL_PAD_UART2_RX_DATA=0;
    *UART2_RX_DATA_SELECT_INPUT=1;  

    UART2->UCR2 |= (1<<14)|(1<<5)|(1<<2)|(1<<1);
    UART2->UCR3 |= (1<<2);
    UART2->UFCR = (5<<7);
    UART2->UBIR=71;
    UART2->UBMR=3124;
    UART2->UCR1 |= (1<<0);
#elif (DEBUG==UART3_DEBUG)
    static __IO u32 *SW_MUX_CTL_PAD_UART3_TX_DATA = (__IO u32*)(0x20E00A4);
    static __IO u32 *SW_MUX_CTL_PAD_UART3_RX_DATA = (__IO u32*)(0x20E00A8);
    static __IO u32 *UART3_RX_DATA_SELECT_INPUT = (__IO u32*)(0x20E0634);

    *SW_MUX_CTL_PAD_UART3_TX_DATA=0;
    *SW_MUX_CTL_PAD_UART3_RX_DATA=0;
    *UART3_RX_DATA_SELECT_INPUT=1;

    UART3->UCR2 |= (1<<14)|(1<<5)|(1<<2)|(1<<1);
    UART3->UCR3 |= (1<<2);
    UART3->UFCR = (5<<7);
    UART3->UBIR=71;
    UART3->UBMR=3124;
    UART3->UCR1 |= (1<<0);
#endif

}
void Serial_SendChar(uint8_t ch){
    while(!(UART1->USR2 &(1<<3)));
    UART1->UTXD=(uint8_t)ch;
}

void Serial_SendString(uint8_t *str){
    while (*str!='\0')
    {
        Serial_SendChar(*str);
        str++;
    }
}
void Serial_SendArray(uint8_t *arr,uint8_t length){
    uint8_t i;
    for (i = 0; i < length; i++)
    {
        Serial_SendChar(arr[i]);
    }
}

static uint64_t Serial_Pow(uint8_t x,uint64_t y){
    uint64_t i=1;
    while (y--)
    {
        i*= x;
    }
    return i;
}

void Serial_Num(uint64_t num){
    uint8_t i,length=1;
    uint64_t temp =num;
    while (temp/=10)
    {
        length++;
    }
    temp =num;
    for (i = 0; i < length; i++)
    {
        Serial_SendChar(num/Serial_Pow(10,length-1-i) % 10 + '0');
    }
    Serial_SendChar('\n');
}
uint8_t Serial_ReceChar(void){
    while(!(UART1->USR2 &(1<<0)));
    return (uint8_t)UART1->URXD;
}
// uint8_t Uart_RecvString(void){
//     uint8_t buff[1024];
//     int i;
//     while(Uart_RecvChar()!='\0'){
//         buff[i]=Uart_RecvChar();
//         i++;
//     }
//     return buff;
// }


void raise(int sig_nr) 
{

}
