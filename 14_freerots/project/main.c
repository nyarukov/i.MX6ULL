/*
 * @Author: Yusaka
 * @Date: 23-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-12-05 02:08:19
 * @FilePath: /14_freerots/project/main.c
 * @Description:
 */
#include "common.h"
#include "clk.h"
#include "delay.h"
#include "led.h"
#include "uart.h"


int main()
{
	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	Serial_Init();
	led.init(led_r);
	while (1)
	{
		led.set(led_r, true);
		delayms(1000);
		led.set(led_r, false);
		delayms(1000);
	}
	return 0;
}