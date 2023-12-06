/*
 * @Author: Yusaka
 * @Date: 2023-11-20 10:04:20
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 16:44:24
 * @FilePath: /07_ech11/include/encoder.h
 * @Description: 
 */
#ifndef __ENCONDER_H
#define __ENCONDER_H

#include "common.h"
#include "beep.h"


#define ENCODER_PAD_CONFIG	(SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz| \
							ODE_0_OPEN_DRAIN_DISABLED | PKE_1_PULL_KEEPER_ENABLED| \
							PUE_1_PULL_SELECTED | PUS_0_100K_OHM_PULL_DOWN | HYS_0_HYSTERESIS_DISABLED)

extern int32_t i;
void encoder_init(void);
void encoder_handler(unsigned int giccIar, void *param);
#endif // !__ENCONDER_H