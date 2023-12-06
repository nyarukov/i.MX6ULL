/*
 * @Author: Yusaka
 * @Date: 2023-11-16 18:36:37
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-25 14:48:44
 * @FilePath: /09_iic/include/led.h
 * @Description: 
 */
#ifndef __LED_H
#define __LED_H

#include "common.h"

#define LED_PAD_CONFIG	(SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz| \
							ODE_0_OPEN_DRAIN_DISABLED | PKE_1_PULL_KEEPER_ENABLED| \
							PUE_1_PULL_SELECTED | PUS_0_100K_OHM_PULL_DOWN | HYS_0_HYSTERESIS_DISABLED)

typedef enum{
    led_r=0x01,
    led_g=0x02,
    led_b=0x03,
}led_id;

typedef struct{
    void (*init)(led_id id);
    void (*set)(led_id id, bool state);
}LED_t;

extern LED_t led;

#endif // !__LED_H