/*
 * @Author: Yusaka
 * @Date: 2023-11-16 18:36:37
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-18 20:24:17
 * @FilePath: /04_exit/include/led.h
 * @Description: 
 */
#ifndef __LED_H
#define __LED_H

#include "common.h"
#include "stdbool.h"

#define LED_PAD_CONFIG	(SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz| \
							ODE_0_OPEN_DRAIN_DISABLED | PKE_0_PULL_KEEPER_DISABLED| \
							PUE_0_KEEPER_SELECTED | PUS_0_100K_OHM_PULL_DOWN | HYS_0_HYSTERESIS_DISABLED)



enum led_id{
    led_r=0,
    led_g,
    led_b,
};

void led_init(enum led_id id);
void led_set(enum led_id id, bool state);

#endif // !__LED_H