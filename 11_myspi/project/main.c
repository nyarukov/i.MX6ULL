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
#include "delay.h"
#include "led.h"
#include "uart.h"
#include "myspi.h"

int main()
{
	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	Serial_Init();
	MYSPI_Init();
	led.init(led_r);
	uint8_t rxdata=0;
	while (1)
	{
		led.set(led_r, true);
		delayms(1000);
		led.set(led_r, false);
		delayms(1000);
	}
	return 0;
}