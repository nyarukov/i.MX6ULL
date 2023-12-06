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
#include "w25q32.h"
#include "myspi.h"

uint8_t TxArr[] = {0x41, 0x42, 0x43, 0x44};
uint8_t RxArr[] = {0};

int main()
{
	int_init();
	clk_enable();
	imx6u_clkinit();
	delay_init();
	Serial_Init();

	W25Q32_Init();
	uint8_t MID;
	uint16_t DID;
	W25Q32_ReadID(&MID, &DID);
	switch (DID)
	{
	case W25Q80:
		Serial_SendString((uint8_t *)"当前设备W25Q80\n");
		break;
	case W25Q16:
		Serial_SendString((uint8_t *)"当前设备W25Q16\n");
		break;
	case W25Q32:
		Serial_SendString((uint8_t *)"当前设备W25Q32\n");
		break;
	case W25Q64:
		Serial_SendString((uint8_t *)"当前设备W25Q64\n");
		break;
	default:
		Serial_SendString((uint8_t *)"无法识别的Flash设备\n");
		break;
	}
	Serial_SendString((uint8_t *)"RXArr: ");
	Serial_SendArray(RxArr, 4);
	Serial_SendChar('\n');

	W25Q32_SectorErase(0x010042, ERASE_4KB);
	W25Q32_PageProgram(0x010042, TxArr, 4);
	W25Q32_ReadData(0x010042, RxArr, 4);

	Serial_SendString((uint8_t *)"RXArr: ");
	Serial_SendArray(RxArr, 4);
	Serial_SendChar('\n');
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