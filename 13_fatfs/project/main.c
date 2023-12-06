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
#include "ff.h"
#include "w25q32.h"

FATFS fsObject;
FRESULT res;
BYTE work[_MAX_SS];
FIL fp;

// BYTE TXData[] = "测试测试";
// BYTE RXData[];
// BYTE cont;

const uint8_t wdata[] = {0x1, 0x2, 0x3, 0x4};
uint8_t rdata[];

void fatfs_init(void);

int main()
{

	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	Serial_Init();
	led.init(led_r);
	fatfs_init();
	while (1)
	{
		led.set(led_r, true);
		delayms(1000);
		led.set(led_r, false);
		delayms(1000);
	}
	return 0;
}

void fatfs_init(void)
{
	res = f_mount(&fsObject, "0:", 1);

	Serial_SendString((uint8_t *)"\nf_mount:");
	Serial_Num(res);

	if (res == FR_NO_FILESYSTEM)
	{
		Serial_SendString((uint8_t *)"\n无文件系统,格式化FLASH");

		res = f_mkfs("0:", FM_ANY, 0, work, sizeof(work));
		if (res == FR_OK)
		{
			Serial_SendString((uint8_t *)"\n格式化FLASH成功!");
		}
		else
		{
			Serial_SendString((uint8_t *)"\n格式化FLASH失败!");
			Serial_Num(res);
		}
		res = f_mount(NULL, "0:", 1);
		res = f_mount(&fsObject, "0:", 1);

		Serial_SendString((uint8_t *)"\nf_mount:");
		Serial_Num(res);
	}

	res = f_open(&fp, "0:/1.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	Serial_SendString((uint8_t *)"\nf_open:");
	Serial_Num(res);
	// f_write(&fp, TXData, sizeof(TXData));
}