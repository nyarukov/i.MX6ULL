/*
 * @Author: Yusaka
 * @Date: 23-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 1123-11-25 17:04:27
 * @FilePath: /09_iic/project/main.c
 * @Description:
 */
#include "common.h"
#include "clk.h"
#include "led.h"
#include "delay.h"
#include "uart.h"

uint8_t array[] = {'a', 'b', 'c', '1', '2', '3', '@', '!', 'z', 'A', 'B', '0', '9', 'x', 'Y', '5', '6', '7', '8', 'd'};

int main()
{
	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	Serial_Init();
	
	led.init(led_b);
	while (1)
	{
		
		Serial_num(5147323565458979458);
		Serial_SendArray(array,10);
		led.set(led_b, true);
		delayms(1000);
		led.set(led_b, false);
		delayms(1000);
	}
	return 0;
}