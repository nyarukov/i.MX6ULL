/*
 * @Author: Yusaka
 * @Date: 2023-11-16 03:55:45
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-21 21:33:20
 * @FilePath: /09_spi/project/main.c
 * @Description:
 */
#include "common.h"
#include "clk.h"
#include "led.h"
#include "delay.h"
#include "lcd_draw.h"
#include "uart.h"
#include "spi.h"
#include "spi_gpio.h"

int main()
{

	int_init();
	clk_enable();
	imx6u_clkinit();
	Uart_Init();
	spi_init(ECSPI1);
	spi1_gpio_init();
	lcd_init();
	led_init(led_b);
	uint8_t state = 0;
	uint16_t i = 0;
	uint16_t spirxdata = 0;
	while (1)
	{
		spi_send(ECSPI1, (u8)'A' + i);
		spirxdata = spi_recv(ECSPI1);
		i++;
		state = !state;
		gpio_writebit(GPIO5, 4, state);
		lcd_shownum(10, 0, spirxdata, 3, 16, LCD_YELLOW);
		delay(1000);
	}
	return 0;
}