/*
 * @Author: Yusaka
 * @Date: 2023-11-16 18:36:01
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 01:36:23
 * @FilePath: /porject/src/led.c
 * @Description: 
 */
#include "led.h"

void led_init(enum led_id id){
    switch(id){
        case led_r:
            IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER3_GPIO5_IO03,0);
            IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER3_GPIO5_IO03,IOMUXC_PAD_CONFIG);
            GPIO5->GDIR |=0x8;
            break;
        case led_g:
            IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER7_GPIO5_IO07,0);
            IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER7_GPIO5_IO07,IOMUXC_PAD_CONFIG);
            GPIO5->GDIR |=0x80;
            break;
        case led_b:
            IOMUXC_SetPinMux(IOMUXC_SNVS_SNVS_TAMPER4_GPIO5_IO04,0);
            IOMUXC_SetPinConfig(IOMUXC_SNVS_SNVS_TAMPER4_GPIO5_IO04,IOMUXC_PAD_CONFIG);
            GPIO5->GDIR |=0x10;
            break;
    }
    
    led_set(id, false);
    
}

void led_set(enum led_id id, bool state){
    
    uint32_t control_bit=0; 
        switch (id)
        {
        case led_r:
            control_bit=0x8;
            break;
        case led_g:
            control_bit=0x80;
            break;
        case led_b:
            control_bit=0x10;
            break;
        
        default:
            break;
        }
        // 根据state设置对应的GPIO状态
    if (state) {
        GPIO5->DR &= ~control_bit;  // 开启LED
    } else {
        GPIO5->DR |= control_bit;  // 关闭LED
    }
}
