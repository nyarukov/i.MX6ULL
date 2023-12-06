/*
 * @Author: Yusaka
 * @Date: 2023-11-17 17:10:31
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-18 14:46:46
 * @FilePath: /05_spi/include/lcd_draw.h
 * @Description: 
 */
#ifndef __LCD_DRAW_H
#define __LCD_DRAW_H
#include "common.h"
#include "lcd_drive.h"
#include <stdlib.h>
#include <signal.h>

/* 颜色 */
#define LCD_BLUE		  0x000000FF
#define LCD_GREEN		  0x0000FF00
#define LCD_RED 		  0x00FF0000
#define LCD_CYAN		  0x0000FFFF
#define LCD_MAGENTA 	  0x00FF00FF
#define LCD_YELLOW		  0x00FFFF00
#define LCD_LIGHTBLUE	  0x008080FF
#define LCD_LIGHTGREEN	  0x0080FF80
#define LCD_LIGHTRED	  0x00FF8080
#define LCD_LIGHTCYAN	  0x0080FFFF
#define LCD_LIGHTMAGENTA  0x00FF80FF
#define LCD_LIGHTYELLOW   0x00FFFF80
#define LCD_DARKBLUE	  0x00000080
#define LCD_DARKGREEN	  0x00008000
#define LCD_DARKRED 	  0x00800000
#define LCD_DARKCYAN	  0x00008080
#define LCD_DARKMAGENTA   0x00800080
#define LCD_DARKYELLOW	  0x00808000
#define LCD_WHITE		  0x00FFFFFF
#define LCD_LIGHTGRAY	  0x00D3D3D3
#define LCD_GRAY		  0x00808080
#define LCD_DARKGRAY	  0x00404040
#define LCD_BLACK		  0x00000000
#define LCD_BROWN		  0x00A52A2A
#define LCD_ORANGE		  0x00FFA500
#define LCD_TRANSPARENT   0x00000000

void lcd_drawpoint(u16 x,u16 y,u32 u32 );
void lcd_clear(u32 color);
void lcd_fill(u16 x0, u16 y0, u16 x1, u16 y1, u32 color);
void lcd_drawline(u16 x1, u16 y1, u16 x2, u16 y2,u32 color);
void lcd_draw_rectangle(u16 x1, u16 y1, u16 x2, u16 y2,u32 color);
void lcd_draw_circle(u16 x0,u16 y0,u16 r,u32 color);
void lcd_showchar(u16 x,u16 y,u8 num,u8 size,u32 color);
void lcd_showstring(u16 x,u16 y,u16 width, u16 height, u8 size,char *p,u32 color);
u32 lcd_pow(u8 m,u8 n);
void lcd_shownum(u16 x, u16 y, u32 num, u8 len,u8 size,u32 color);

#endif // !__LCD_DRAW_H