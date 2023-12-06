/*
 * @Author: Yusaka
 * @Date: 2023-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 17:25:07
 * @FilePath: /07_ech11/project/main.c
 * @Description: 
 */
#include "common.h"
#include "clk.h"
#include "beep.h"
#include "led.h"
#include "uart.h"
#include "delay.h"
#include "lcd_draw.h"
#include "encoder.h"
#include "key.h"

extern int32_t i;

int main(){

	int_init();
	clk_enable();
	imx6u_clkinit();
	lcd_init();
	led_init(led_r);
	encoder_init();
	beep_init();
	u8 state=0;
	while (1)
	{	
		state =!state;
		led_set(led_r,state);
		lcd_shownum(0,0,i,3,16,LCD_WHITE);
		lcd_shownum(0,16,gpio_readbit(GPIO1,5),3,16,LCD_WHITE);
		lcd_shownum(0,16*2,gpio_readbit(GPIO1,2),3,16,LCD_WHITE);
		lcd_shownum(0,16*3,gpio_readbit(GPIO1,4),3,16,LCD_WHITE);
		delay(1000);
	}
	return 0;
}