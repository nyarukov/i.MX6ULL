/*
 * @Author: Yusaka
 * @Date: 2023-10-05 12:22:59
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 09:54:05
 * @FilePath: /04_exit/src/beep.c
 * @Description: 
 */
#include "beep.h"

void beep_init(void){
	IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER0_GPIO5_IO00,0);
	IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER0_GPIO5_IO00,BEEP_PAD_CONFIG);
	GPIO5->GDIR |= 0x1;
}

void beep_set(bool stae){
	if(stae==1)
		GPIO5->DR |= 0x1;
	else
		GPIO5->DR &= ~(0x1);
}
