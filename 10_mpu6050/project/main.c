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
#include "mpu6050.h"
#include "lcd_draw.h"

int main()
{
	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	lcd_init();
	mpu6050.Init();
	led.init(led_b);
	while (1)
	{
		mpu6050.ReadData();
		lcd_showstring(0,0,8*11,16,16,"ACCEL_XOUT:",LCD_YELLOW);
		lcd_showstring(0,16,8*11,16,16,"ACCEL_YOUT:",LCD_YELLOW);
		lcd_showstring(0,16*2,8*11,16,16,"ACCEL_ZOUT:",LCD_YELLOW);
		lcd_showstring(0,16*3,8*11,16,16,"GYRO_XOUT:",LCD_YELLOW);
		lcd_showstring(0,16*4,8*11,16,16,"GYRO_YOUT:",LCD_YELLOW);
		lcd_showstring(0,16*5,8*11,16,16,"GYRO_ZOUT:",LCD_YELLOW);
		lcd_showstring(0,16*6,8*11,16,16,"TEMP:",LCD_YELLOW);
		lcd_shownum(90,0,mpu6050.ACCEL_XOUT,5,16,LCD_YELLOW);
		lcd_shownum(90,16,mpu6050.ACCEL_YOUT,5,16,LCD_YELLOW);
		lcd_shownum(90,16*2,mpu6050.ACCEL_ZOUT,5,16,LCD_YELLOW);
		lcd_shownum(90,16*3,mpu6050.GYRO_XOUT,5,16,LCD_YELLOW);
		lcd_shownum(90,16*4,mpu6050.GYRO_YOUT,5,16,LCD_YELLOW);
		lcd_shownum(90,16*5,mpu6050.GYRO_ZOUT,5,16,LCD_YELLOW);
		lcd_shownum(90,16*6,mpu6050.TEMP,5,16,LCD_YELLOW);
		// led.set(led_b, true);
		// delayms(1000);
		// led.set(led_b, false);
		delayms(1000);
	}
	return 0;
}