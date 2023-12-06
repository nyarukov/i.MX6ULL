/*
 * @Author: Yusaka
 * @Date: 2023-11-18 18:56:51
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 10:01:26
 * @FilePath: /05_epit/include/key.h
 * @Description: 
 */
#ifndef _KEY_H
#define _KEY_H

#include "common.h"
#include <stdbool.h>
#include "pad_config.h"
#include "beep.h"
#include "int.h"
#include "delay.h"
#include "uart.h"
#include "lcd_draw.h"

#define KEY_PAD_CONFIG  (SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz |\
                        ODE_0_OPEN_DRAIN_DISABLED | PKE_0_PULL_KEEPER_DISABLED | \
                        PUE_0_KEEPER_SELECTED | PUS_0_100K_OHM_PULL_DOWN | HYS_1_HYSTERESIS_ENABLED)
enum key_id{
    Key1=1,
    KeyMax,
};

// typedef struct key_config {
//     enum key_id id;
//     void (*init)(enum key_id id);
//     bool (*read)(enum key_id id);
// }key_config_t;

void key_init(void);
bool key_read(void);
void GPIO1_io18_irqhandler(unsigned int giccIar, void *userParam);

#endif // !_KEY_H