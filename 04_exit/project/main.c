/*
 * @Author: Yusaka
 * @Date: 2023-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 11:23:16
 * @FilePath: /04_exit/project/main.c
 * @Description:
 */
#include "common.h"
#include "clk.h"
#include "beep.h"
#include "led.h"
#include "delay.h"
#include "lcd_draw.h"
#include "int.h"
#include "key.h"

int main()
{

	int_init();
	//imx6u_clkinit();
	clk_enable();
	lcd_init();
	led_init(led_r);
	beep_init();
	key_init();
	u8 state = 0;
	while (1)
	{
		state = !state;
		led_set(led_r, state);
		delay(100);
		lcd_shownum(10, 10, key_read(), 1, 16, LCD_WHITE);
	}
	return 0;
}