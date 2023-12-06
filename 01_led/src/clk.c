/*
 * @Author: Yusaka
 * @Date: 2023-10-05 13:24:01
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-16 01:49:35
 * @FilePath: /porject/src/clk.c
 * @Description: 
 */
#include "clk.h"

/**
 * @函数名称: clk_enable
 * @功能描述: 使能时钟
 * @输入参数: void
 * @输出参数: void
 * @返 回 值: void
 */
void clk_enable(void)
{
	CCM->CCGR0 = 0XFFFFFFFF;
	CCM->CCGR1 = 0XFFFFFFFF;
	CCM->CCGR2 = 0XFFFFFFFF;
	CCM->CCGR3 = 0XFFFFFFFF;
	CCM->CCGR4 = 0XFFFFFFFF;
	CCM->CCGR5 = 0XFFFFFFFF;
	CCM->CCGR6 = 0XFFFFFFFF;
}

