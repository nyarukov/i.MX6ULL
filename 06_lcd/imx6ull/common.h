/*
 * @Author: Yusaka
 * @Date: 2023-10-05 15:00:18
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-18 14:55:48
 * @FilePath: /05_spi/imx6ull/common.h
 * @Description: 
 */
#ifndef   __COMMON_H__
#define   __COMMON_H__

#include "fsl_iomuxc.h"
#include "pad_config.h"
#include "core_ca7.h"

#define IOMUXC_PAD_CONFIG	(SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz| \
							ODE_0_OPEN_DRAIN_DISABLED | PKE_1_PULL_KEEPER_ENABLED| \
							PUE_1_PULL_SELECTED | PUS_0_100K_OHM_PULL_DOWN | HYS_0_HYSTERESIS_DISABLED)


#endif
