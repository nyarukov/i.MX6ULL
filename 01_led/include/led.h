/*
 * @Author: Yusaka
 * @Date: 2023-11-16 18:36:37
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-17 01:36:27
 * @FilePath: /porject/include/led.h
 * @Description: 
 */
#ifndef __LED_H
#define __LED_H

#include "common.h"
#include "stdbool.h"

enum led_id{
    led_r=0,
    led_g,
    led_b,
};

void led_init(enum led_id id);
void led_set(enum led_id id, bool state);

#endif // !__LED_H