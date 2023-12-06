/*
 * @Author: Yusaka
 * @Date: 2023-11-18 18:55:19
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 09:54:15
 * @FilePath: /04_exit/include/beep.h
 * @Description: 
 */
#ifndef __BEEP_H
#define __BEEP_H

#include "common.h"

#define BEEP_PAD_CONFIG	(SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz| \
							ODE_0_OPEN_DRAIN_DISABLED | PKE_0_PULL_KEEPER_DISABLED| \
							PUE_0_KEEPER_SELECTED | PUS_0_100K_OHM_PULL_DOWN | HYS_0_HYSTERESIS_DISABLED)

void beep_init(void);
void beep_set(bool stae);
#endif // !__BEEP_H