#include "lcd_draw.h"
#include "font.h"

struct tftlcd_typedef tftlcd_dev;
/*
 * @description		: 画点函数 
 * @param - x		: x轴坐标
 * @param - y		: y轴坐标
 * @param - color	: 颜色值
 * @return 			: 无
 */
void lcd_drawpoint(u16 x,u16 y,u32 color)
{ 
  	*(u32*)((u32)tftlcd_dev.framebuffer + 
		             tftlcd_dev.pixsize * (tftlcd_dev.width * y+x))=color;
}
/*
 * @description		: 清屏
 * @param - color	: 颜色值
 * @return 			: 读取到的指定点的颜色值
 */
void lcd_clear(u32 color)
{
	u32 num;
	u32 i = 0; 

	u32 *startaddr=(u32*)tftlcd_dev.framebuffer;	//指向帧缓存首地址
	num=(u32)tftlcd_dev.width * tftlcd_dev.height;			//缓冲区总长度
	for(i = 0; i < num; i++)
	{
		startaddr[i] = color;
	}		
}
/*
 * @description		: 以指定的颜色填充一块矩形
 * @param - x0		: 矩形起始点坐标X轴
 * @param - y0		: 矩形起始点坐标Y轴
 * @param - x1		: 矩形终止点坐标X轴
 * @param - y1		: 矩形终止点坐标Y轴
 * @param - color	: 要填充的颜色
 * @return 			: 读取到的指定点的颜色值
 */
void lcd_fill(u16 x0, u16 y0, 
                 u16 x1, u16 y1, u32 color)
{ 
    u16 x, y;

	if(x0 < 0) x0 = 0;
	if(y0 < 0) y0 = 0;
	if(x1 >= tftlcd_dev.width) x1 = tftlcd_dev.width - 1;
	if(y1 >= tftlcd_dev.height) y1 = tftlcd_dev.height - 1;
	
    for(y = y0; y <= y1; y++)
    {
        for(x = x0; x <= x1; x++)
			lcd_drawpoint(x, y, color);
    }
}
/*
 * @description		: 画线函数
 * @param - x1		: 线起始点坐标X轴
 * @param - y1		: 线起始点坐标Y轴
 * @param - x2		: 线终止点坐标X轴
 * @param - y2		: 线终止点坐标Y轴
 * @return 			: 无
 */ 
void lcd_drawline(u16 x1, u16 y1, u16 x2, u16 y2,u32 color)
{
	u16 t; 
	int xerr = 0, yerr = 0, delta_x, delta_y, distance; 
	int incx, incy, uRow, uCol; 
	delta_x = x2 - x1; 					/* 计算坐标增量 */
	delta_y = y2 - y1; 
	uRow = x1; 
	uCol = y1; 
	if(delta_x > 0) 					/* 设置单步方向 */ 
		incx = 1;
	else if(delta_x==0)					/* 垂直线 */
		incx = 0;		
	else 
	{
		incx = -1;
		delta_x = -delta_x;
	} 
	if(delta_y>0)
		incy=1; 
	else if(delta_y == 0)				/* 水平线 */
		incy=0;
	else
	{
		incy = -1;
		delta_y = -delta_y;
	} 
	if( delta_x > delta_y)				/*选取基本增量坐标轴  */
		distance = delta_x; 
	else 
		distance = delta_y; 
	for(t = 0; t <= distance+1; t++ )	/* 画线输出 */
	{  

		lcd_drawpoint(uRow, uCol, color);/* 画点 */
		xerr += delta_x ; 
		yerr += delta_y ; 
		if(xerr > distance) 
		{ 
			xerr -= distance; 
			uRow += incx; 
		} 
		if(yerr > distance) 
		{ 
			yerr -= distance; 
			uCol += incy; 
		} 
	}  
}   

/*
 * @description	: 画矩形函数
 * @param - x1	: 矩形坐上角坐标X轴
 * @param - y1	: 矩形坐上角坐标Y轴
 * @param - x2	: 矩形右下角坐标X轴
 * @param - y2	: 矩形右下角坐标Y轴
 * @return 		: 无
 */
void lcd_draw_rectangle(u16 x1, u16 y1, u16 x2, u16 y2,u32 color)
{
	lcd_drawline(x1, y1, x2, y1,color);
	lcd_drawline(x1, y1, x1, y2,color);
	lcd_drawline(x1, y2, x2, y2,color);
	lcd_drawline(x2, y1, x2, y2,color);
}

/*
 * @description	: 在指定位置画一个指定大小的圆
 * @param - x0	: 圆心坐标X轴
 * @param - y0	: 圆心坐标Y轴
 * @param - y2	: 圆形半径
 * @return 		: 无
 */
void lcd_draw_circle(u16 x0,u16 y0,u16 r,u32 color)
{
    int mx = x0, my = y0;
    int x = 0, y = r;

    int d = 1 - r;   
    while(y > x)    	/* y>x即第一象限的第1区八分圆 */
    {
        lcd_drawpoint(x  + mx, y  + my, color);
        lcd_drawpoint(y  + mx, x  + my, color);
        lcd_drawpoint(-x + mx, y  + my, color);
        lcd_drawpoint(-y + mx, x  + my, color);

        lcd_drawpoint(-x + mx, -y + my, color);
        lcd_drawpoint(-y + mx, -x + my, color);
        lcd_drawpoint(x  + mx, -y + my, color);
        lcd_drawpoint(y  + mx, -x + my, color);
        if( d < 0)
        {
            d = d + 2 * x + 3;
        }
        else
        {
            d= d + 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

/*
 * @description	: 在指定位置显示一个字符
 * @param - x	: 起始坐标X轴
 * @param - y	: 起始坐标Y轴
 * @param - num	: 显示字符
 * @param - size: 字体大小, 可选12/16/24/32
 * @param - color: 字体颜色
 * @return 		: 无
 */
void lcd_showchar(u16 x, u16 y,u8 num, u8 size,u32 color)
{  	
	u8 mode=0;						  
    u8  temp, t1, t;
	u16 y0 = y;
	u8 csize = (size / 8+ ((size % 8) ? 1 : 0)) * (size / 2);	/* 得到字体一个字符对应点阵集所占的字节数	 */	
 	num = num - ' ';  	/*得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）  */
	for(t = 0; t < csize; t++)
	{   
		if(size == 12) temp = asc2_1206[num][t]; 		/* 调用1206字体 */
		else if(size == 16)temp = asc2_1608[num][t];	/* 调用1608字体 */
		else if(size == 24)temp = asc2_2412[num][t];	/* 调用2412字体 */
		else if(size == 32)temp = asc2_3216[num][t];	/* 调用3216字体 */
		else return;									/* 没有的字库 		*/
		for(t1 = 0; t1 < 8; t1++)
		{			    
			if(temp & 0x80)lcd_drawpoint(x, y, color);
			else if(mode==0)lcd_drawpoint(x, y, tftlcd_dev.backcolor);
			temp <<= 1;
			y++;
			if(y >= tftlcd_dev.height) return;			/* 超区域了 */	
			if((y - y0) == size)
			{
				y = y0;
				x++;
				if(x >= tftlcd_dev.width) return;		/* 超区域了 */
				break;
			}
		}  	 
	}  		    	   	 	  
} 

/*
 * @description		: 显示一串字符串
 * @param - x		: 起始坐标点X轴。
 * @param - y		: 起始坐标点Y轴。
 * @param - width 	: 字符串显示区域长度
 * @param - height	: 字符串显示区域高度
 * @param - size	: 字体大小
 * @param - p		: 要显示的字符串首地址
 * @return 			: 无
 */
void lcd_showstring(u16 x,u16 y,u16 width,u16 height,u8 size,char *p,u32 color)
{         
	u8 x0 = x;
	width += x;
	height += y;
    while((*p <= '~') &&(*p >= ' '))		/* 判断是不是非法字符! */ 
    {       
        if(x >= width) {x = x0; y += size;}
        if(y >= height) break;				/* 退出 */
        lcd_showchar(x, y, *p , size, color);
        x += size / 2;
        p++;
    }  
}

/*
 * @description	: 计算m的n次方
 * @param - m	: 要计算的值
 * @param - n	: n次方
 * @return 		: m^n次方.
 */
u32 lcd_pow(u8 m,u8 n)
{
	u32 result = 1;	 
	while(n--) result *= m;    
	return result;
}

/*
 * @description	: 显示指定的数字，高位为0的话不显示
 * @param - x	: 起始坐标点X轴。
 * @param - y	: 起始坐标点Y轴。
 * @param - num	: 数值(0~999999999)。
 * @param - len : 数字位数。
 * @param - size: 字体大小
 * @param - color   : 字体颜色
 * @return 		: 无
 */
void lcd_shownum(u16 x, u16 y, u32 num, u8 len,u8 size,u32 color)
{         	
	u8  t, temp;
	u8  enshow = 0;						   
	for(t = 0; t < len; t++)
	{
		temp = (num / lcd_pow(10, len - t - 1)) % 10;
		if(enshow == 0 && t < (len - 1))
		{
			if(temp == 0)
			{
				lcd_showchar(x + (size / 2) * t, y, ' ', size, color);
				continue;
			}else enshow = 1; 	 
		}
	 	lcd_showchar(x + (size / 2) * t, y, temp + '0', size, color); 
	}
} 