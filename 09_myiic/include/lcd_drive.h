/*
 * @Author: Yusaka
 * @Date: 2023-11-17 13:34:11
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 14:46:03
 * @FilePath: /04_lcd/include/lcd_drive.h
 * @Description: 
 */
#ifndef __LCD_DRIVE_H
#define __LCD_DRIVE_H

#include "common.h"
#include "lcd_draw.h"
#include "delay.h"

/* LCD显存地址 */
#define LCD_FRAMEBUF_ADDR	(0x89000000)

#define LCD_RESET_ENABLE	 LCDIF->CTRL = 1<<31
#define LCD_RESET_DISABLE	 LCDIF->CTRL = 0<<31
#define LCD_ENABLE		     LCDIF->CTRL |= 1<<0
#define LCD_DISABLE		 	 LCDIF->CTRL &= ~(1<<0)

/* LCD控制参数结构体 */
struct tftlcd_typedef{
	unsigned short height;		/* LCD屏幕高度 */
	unsigned short width;		/* LCD屏幕宽度 */
	unsigned char pixsize;		/* LCD每个像素所占字节大小 */
	unsigned short vspw;
	unsigned short vbpd;
	unsigned short vfpd;
	unsigned short hspw;
	unsigned short hbpd;
	unsigned short hfpd;
	unsigned int framebuffer; 	/* LCD显存首地址   	  */
	unsigned int forecolor;		/* 前景色 */
	unsigned int backcolor;		/* 背景色 */
	unsigned int id;  			/*	屏幕ID */
};

extern struct tftlcd_typedef tftlcd_dev;


/* 函数声明 */
void lcd_init(void);	//初始化
void lcd_config(void);	//lcd配置
void lcd_gpioConfig(void);	//引脚配置
void lcd_clkconfig(unsigned char loopDiv, unsigned char prediv, unsigned char div); //LCD时钟初始化
void lcd_reset(void);
void lcd_noreset(void);
void lcd_enable(void);
#endif // !__LCD_DRIVE_H