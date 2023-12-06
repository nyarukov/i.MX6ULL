#ifndef __MYSPI_H
#define __MYSPI_H

#include "common.h"


#define MYSPI_CS(n)         ((n)? (GPIO4->DR |= (1<<22)): (GPIO4->DR &= ~(1<<22)))
#define MYSPI_SCLK(n)       ((n)? (GPIO4->DR |= (1<<24)): (GPIO4->DR &= ~(1<<24)))
#define MYSPI_MOSI(n)       ((n)? (GPIO4->DR |= (1<<28)): (GPIO4->DR &= ~(1<<28)))
#define MYSPI_MISO          ((GPIO4->PSR)>>26 & 0x1)

#define MYSPI_PAD           (SRE_0_SLOW_SLEW_RATE | DSE_7_R0_7 | SPEED_2_MEDIUM_100MHz | \
                            ODE_0_OPEN_DRAIN_DISABLED | PKE_1_PULL_KEEPER_ENABLED | \
                            PUS_3_22K_OHM_PULL_UP | HYS_0_HYSTERESIS_DISABLED)

#define MYSPI1_PAD           (SRE_0_SLOW_SLEW_RATE | DSE_0_OUTPUT_DRIVER_DISABLED | SPEED_2_MEDIUM_100MHz | \
                            ODE_0_OPEN_DRAIN_DISABLED | PKE_1_PULL_KEEPER_ENABLED | \
                            PUS_3_22K_OHM_PULL_UP | HYS_0_HYSTERESIS_DISABLED)

void MYSPI_Init(void);
uint8_t MYSPI_SendByte(uint8_t data);

#endif 