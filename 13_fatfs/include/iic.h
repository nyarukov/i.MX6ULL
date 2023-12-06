#ifndef __IIC_H
#define __IIC_H

#include "common.h"
#include "delay.h"

#define IIC_PAD     (SRE_0_SLOW_SLEW_RATE | DSE_6_R0_6 | SPEED_2_MEDIUM_100MHz |       \
                        ODE_1_OPEN_DRAIN_ENABLED | PKE_0_PULL_KEEPER_DISABLED | PUS_3_22K_OHM_PULL_UP | \
                        HYS_0_HYSTERESIS_DISABLED)


#define IIC_SCL(n) ((n) ? (GPIO4->DR |= (1 << 20)) : (GPIO4->DR &= ~(1 << 20)))
#define IIC_SDA(n) ((n) ? (GPIO4->DR |= (1 << 19)) : (GPIO4->DR &= ~(1 << 19)))
#define SDA_PAD(n) ((n) ? (GPIO4->GDIR |= (1 << 19)) : (GPIO4->GDIR &= ~(1 << 19)))
#define SDA_Read ((GPIO4->PSR) >> 19 & 0x1)

typedef struct
{
    void (*Init)(void);
    void (*Start)(void);
    void (*Stop)(void);
    void (*SendACK)(bool value);
    uint8_t (*ReceiveACK)(void);
    void (*SendByte)(uint8_t txdata);
    uint8_t (*ReceiveByte)(void);
} IIC_t;

extern IIC_t IIC;

#endif // !__IIC_H