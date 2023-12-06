/*
 * @Author: Yusaka
 * @Date: 2023-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-18 15:01:05
 * @FilePath: /05_spi/project/main.c
 * @Description: 
 */
#include "common.h"
#include "clk.h"
#include "beep.h"
#include "led.h"
#include "uart.h"
#include "delay.h"
#include "lcd_draw.h"

u32 LCD_COLRO[10]={
	LCD_BLUE,LCD_GREEN,LCD_RED,LCD_CYAN,LCD_MAGENTA,
	LCD_YELLOW,LCD_LIGHTBLUE,LCD_LIGHTGREEN,LCD_LIGHTRED,
	LCD_LIGHTCYAN
};

int main(){

	clk_enable();
	lcd_init();
	led_init(led_r);
	lcd_clear(LCD_BLACK);
	int i=0;

	while (1)
	{	
		lcd_shownum(500,232,i,1,16,LCD_GREEN);
	}
	return 0;
}