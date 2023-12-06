/*
 * @Author: Yusaka
 * @Date: 2023-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 01:23:58
 * @FilePath: /porject/project/main.c
 * @Description: 
 */
#include "common.h"
#include "clk.h"
#include "led.h"

void delay(__O u32 val){
	while (val--);
}

int main(){

	clk_enable();
	led_init(led_r);
	led_init(led_g);
	led_init(led_b);
	u8 led_index=0;
	while (1)
	{
		led_set(led_index,true);
		delay(100000);
		led_set(led_index,false);
		delay(100000);
		led_index++;
		if(led_index==3)
		led_index=0;
	}
	return 0;
}
