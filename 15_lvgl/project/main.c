/*
 * @Author: Yusaka
 * @Date: 23-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-12-06 11:38:36
 * @FilePath: /15_lvgl/project/main.c
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

	led.init(led_r);
	led.init(led_b);



	led.set(led_r, true);
	while (1)
	{

		led.set(led_b, true);

	}
	return 0;
}