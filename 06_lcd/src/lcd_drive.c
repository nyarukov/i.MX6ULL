/*
 * @Author: Yusaka
 * @Date: 2023-11-17 13:34:41
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 14:46:28
 * @FilePath: /04_lcd/src/lcd_drive.c
 * @Description: 
 */
#include "lcd_drive.h"

struct tftlcd_typedef tftlcd_dev;

void lcd_init(void)
{
	lcd_gpioConfig();			/* 初始化IO 			*/
   
	lcd_reset();		/* 复位LCD  			*/
	delay(10);		/* 延时10ms 			*/
	lcd_noreset();		/* 结束复位 	*/
	lcd_config();		
	lcd_enable();			/* 使能LCD 	*/
	delay(10);
	lcd_clear(LCD_WHITE);	/* 清屏 		*/
}
void lcd_config(void){
    tftlcd_dev.id = 0X7016;
    tftlcd_dev.height = 600;	
    tftlcd_dev.width = 1024;
    tftlcd_dev.vspw = 3;
    tftlcd_dev.vbpd = 20;
    tftlcd_dev.vfpd = 12;
    tftlcd_dev.hspw = 20;
    tftlcd_dev.hbpd = 140;
    tftlcd_dev.hfpd = 160;
	lcd_clkconfig(32, 3, 5);	/* 初始化LCD时钟 51.2MHz */
    tftlcd_dev.pixsize = 4;				/* ARGB8888模式，每个像素4字节 */
	tftlcd_dev.framebuffer = LCD_FRAMEBUF_ADDR;	
	tftlcd_dev.backcolor = LCD_WHITE;	/* 背景色为白色 */
	tftlcd_dev.forecolor = LCD_BLACK;	/* 前景色为黑色 */
    /* 初始化ELCDIF的CTRL寄存器
     * bit [31] 0 : 停止复位
     * bit [19] 1 : 旁路计数器模式
     * bit [17] 1 : LCD工作在dotclk模式
     * bit [15:14] 00 : 输入数据不交换
     * bit [13:12] 00 : CSC不交换
     * bit [11:10] 11 : 24位总线宽度
     * bit [9:8]   11 : 24位数据宽度,也就是RGB888
     * bit [5]     1  : elcdif工作在主模式
     * bit [1]     0  : 所有的24位均有效
	 */
	 LCDIF->CTRL |= (1 << 19) | (1 << 17) | (0 << 14) | (0 << 12) |
	 				(3 << 10) | (3 << 8) | (1 << 5) | (0 << 1);
    /*
     * 初始化ELCDIF的寄存器CTRL1
     * bit [19:16]  : 0X7 ARGB模式下，传输24位数据，A通道不用传输
	 */	
	 LCDIF->CTRL1 = 0X7 << 16; 
	 /*
      * 初始化ELCDIF的寄存器TRANSFER_COUNT寄存器
      * bit [31:16]  : 高度
      * bit [15:0]   : 宽度
	  */
	LCDIF->TRANSFER_COUNT  = (tftlcd_dev.height << 16) | (tftlcd_dev.width << 0);
	/*
     * 初始化ELCDIF的VDCTRL0寄存器
     * bit [29] 0 : VSYNC输出
     * bit [28] 1 : 使能ENABLE输出
     * bit [27] 0 : VSYNC低电平有效
     * bit [26] 0 : HSYNC低电平有效
     * bit [25] 0 : DOTCLK上升沿有效
     * bit [24] 1 : ENABLE信号高电平有效
     * bit [21] 1 : DOTCLK模式下设置为1
     * bit [20] 1 : DOTCLK模式下设置为1
     * bit [17:0] : vsw参数
	 */
	LCDIF->VDCTRL0 = 0;	//先清零
    LCDIF->VDCTRL0 = (0 << 29) | (1 << 28) | (0 << 27) |
					 (0 << 26) | (0 << 25) | (1 << 24) |
					 (1 << 21) | (1 << 20) | (tftlcd_dev.vspw << 0);
    /*
	 * 初始化ELCDIF的VDCTRL1寄存器
	 * 设置VSYNC总周期
	 */  
	LCDIF->VDCTRL1 = tftlcd_dev.height + tftlcd_dev.vspw + tftlcd_dev.vfpd + tftlcd_dev.vbpd;  //VSYNC周期 
	 /*
	  * 初始化ELCDIF的VDCTRL2寄存器
	  * 设置HSYNC周期
	  * bit[31:18] ：hsw
	  * bit[17:0]  : HSYNC总周期
	  */ 
	LCDIF->VDCTRL2 = (tftlcd_dev.hspw << 18) | (tftlcd_dev.width + tftlcd_dev.hspw + tftlcd_dev.hfpd + tftlcd_dev.hbpd);
	/*
	 * 初始化ELCDIF的VDCTRL3寄存器
	 * 设置HSYNC周期
	 * bit[27:16] ：水平等待时钟数
	 * bit[15:0]  : 垂直等待时钟数
	 */ 
	LCDIF->VDCTRL3 = ((tftlcd_dev.hbpd + tftlcd_dev.hspw) << 16) | (tftlcd_dev.vbpd + tftlcd_dev.vspw);
	/*
	 * 初始化ELCDIF的VDCTRL4寄存器
	 * 设置HSYNC周期
	 * bit[18] 1 : 当使用VSHYNC、HSYNC、DOTCLK的话此为置1
	 * bit[17:0]  : 宽度
	 */ 
	
	LCDIF->VDCTRL4 = (1<<18) | (tftlcd_dev.width);
	/*
     * 初始化ELCDIF的CUR_BUF和NEXT_BUF寄存器
     * 设置当前显存地址和下一帧的显存地址
	 */
	LCDIF->CUR_BUF = (unsigned int)tftlcd_dev.framebuffer;
	LCDIF->NEXT_BUF = (unsigned int)tftlcd_dev.framebuffer;
}

void lcd_gpioConfig(void)
{
	/* 1、IO初始化复用功能 */
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA00_LCDIF_DATA00,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA01_LCDIF_DATA01,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA02_LCDIF_DATA02,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA03_LCDIF_DATA03,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA04_LCDIF_DATA04,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA05_LCDIF_DATA05,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA06_LCDIF_DATA06,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA07_LCDIF_DATA07,0);
	
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA08_LCDIF_DATA08,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA09_LCDIF_DATA09,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA10_LCDIF_DATA10,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA11_LCDIF_DATA11,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA12_LCDIF_DATA12,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA13_LCDIF_DATA13,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA14_LCDIF_DATA14,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA15_LCDIF_DATA15,0);

	IOMUXC_SetPinMux(IOMUXC_LCD_DATA16_LCDIF_DATA16,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA17_LCDIF_DATA17,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA18_LCDIF_DATA18,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA19_LCDIF_DATA19,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA20_LCDIF_DATA20,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA21_LCDIF_DATA21,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA22_LCDIF_DATA22,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_DATA23_LCDIF_DATA23,0);

	IOMUXC_SetPinMux(IOMUXC_LCD_CLK_LCDIF_CLK,0);	
	IOMUXC_SetPinMux(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0);	
	IOMUXC_SetPinMux(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0);
	IOMUXC_SetPinMux(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0);

	IOMUXC_SetPinMux(IOMUXC_GPIO1_IO08_GPIO1_IO08,0);			/* 背光BL引脚      */
	IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);				

	/* 2、配置LCD IO属性	
	 *bit 16:0 HYS关闭
	 *bit [15:14]: 0 默认22K上拉
	 *bit [13]: 0 pull功能
	 *bit [12]: 0 pull/keeper使能 
	 *bit [11]: 0 关闭开路输出
	 *bit [7:6]: 10 速度100Mhz
	 *bit [5:3]: 111 驱动能力为R0/7
	 *bit [0]: 1 高转换率
	 */
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA00_LCDIF_DATA00,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA01_LCDIF_DATA01,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA02_LCDIF_DATA02,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA03_LCDIF_DATA03,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA04_LCDIF_DATA04,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA05_LCDIF_DATA05,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA06_LCDIF_DATA06,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA07_LCDIF_DATA07,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA08_LCDIF_DATA08,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA09_LCDIF_DATA09,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA10_LCDIF_DATA10,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA11_LCDIF_DATA11,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA12_LCDIF_DATA12,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA13_LCDIF_DATA13,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA14_LCDIF_DATA14,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA15_LCDIF_DATA15,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA16_LCDIF_DATA16,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA17_LCDIF_DATA17,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA18_LCDIF_DATA18,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA19_LCDIF_DATA19,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA20_LCDIF_DATA20,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA21_LCDIF_DATA21,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA22_LCDIF_DATA22,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_DATA23_LCDIF_DATA23,0xB9);

	IOMUXC_SetPinConfig(IOMUXC_LCD_CLK_LCDIF_CLK,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_ENABLE_LCDIF_ENABLE,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_HSYNC_LCDIF_HSYNC,0xB9);
	IOMUXC_SetPinConfig(IOMUXC_LCD_VSYNC_LCDIF_VSYNC,0xB9);

	IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO08_GPIO1_IO08,0xB9);	/* 背光BL引脚 */
    GPIO1->GDIR |=0x100;
    GPIO1->DR |=0x100;
}	

/*
 * @description		: LCD时钟初始化, LCD时钟计算公式如下：
 *                	  LCD CLK = 24 * loopDiv / prediv / div
 * @param -	loopDiv	: loopDivider值
 * @param -	prediv  : lcdifprediv值
 * @param -	div		: lcdifdiv值
 * @return 			: 无
 */
void lcd_clkconfig(unsigned char loopDiv, unsigned char prediv, unsigned char div)
{
	/* 先初始化video pll 
     * VIDEO PLL = OSC24M * (loopDivider + (denominator / numerator)) / postDivider
 	 *不使用小数分频器，因此denominator和numerator设置为0
 	 */
	CCM_ANALOG->PLL_VIDEO_NUM = 0;		/* 不使用小数分频器 */
	CCM_ANALOG->PLL_VIDEO_DENOM = 0;	
	/*
     * PLL_VIDEO寄存器设置
     * bit[13]:    1   使能VIDEO PLL时钟
     * bit[20:19]  2  设置postDivider为1分频
     * bit[6:0] : 32  设置loopDivider寄存器
	 */
	CCM_ANALOG->PLL_VIDEO =  (2 << 19) | (1 << 13) | (loopDiv << 0); 
    /*
     * MISC2寄存器设置
     * bit[31:30]: 0  VIDEO的post-div设置，时钟源来源于postDivider，1分频
	 */
	CCM_ANALOG->MISC2 &= ~(3 << 30);
	CCM_ANALOG->MISC2 = 0 << 30;
	/* LCD时钟源来源与PLL5，也就是VIDEO           PLL  */
	CCM->CSCDR2 &= ~(7 << 15);  	
	CCM->CSCDR2 |= (2 << 15);			/* 设置LCDIF_PRE_CLK使用PLL5 */
	/* 设置LCDIF_PRE分频 */
	CCM->CSCDR2 &= ~(7 << 12);		
	CCM->CSCDR2 |= (prediv - 1) << 12;	/* 设置分频  */
	/* 设置LCDIF分频 */
	CCM->CBCMR &= ~(7 << 23);					
	CCM->CBCMR |= (div - 1) << 23;				
	/* 设置LCD时钟源为LCDIF_PRE时钟 */
	CCM->CSCDR2 &= ~(7 << 9);					/* 清除原来的设置		 	*/
	CCM->CSCDR2 |= (0 << 9);					/* LCDIF_PRE时钟源选择LCDIF_PRE时钟 */
}

void lcd_reset(void)
{
	LCDIF->CTRL  = 1<<31; /* 强制复位 */
}

/*
 * @description	: 结束复位ELCDIF接口
 * @param 		: 无
 * @return 		: 无
 */
void lcd_noreset(void)
{
	LCDIF->CTRL  = 0<<31; /* 取消强制复位 */
}

/*
 * @description	: 使能ELCDIF接口
 * @param 		: 无
 * @return 		: 无
 */
void lcd_enable(void)
{
	LCDIF->CTRL |= 1<<0; /* 使能ELCDIF */
}