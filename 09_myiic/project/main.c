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
#include "i2c.h"

int main()
{
	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	IIC.Init();
	led.init(led_b);
	while (1)
	{
		IIC.Start();
		IIC.ReceiveACK();
		IIC.SendByte('A');
		IIC.ReceiveACK();
		IIC.SendACK(1);
		IIC.Stop();
		led.set(led_b, true);
		delayms(1000);
		led.set(led_b, false);
		delayms(1000);
	}
	return 0;
}