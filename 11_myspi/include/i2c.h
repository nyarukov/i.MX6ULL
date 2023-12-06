#ifndef __I2C_H
#define __I2C_H

#include "common.h"
#include "delay.h"

#define I2C_PAD         (SRE_0_SLOW_SLEW_RATE | DSE_7_R0_7 | SPEED_3_MAX_200MHz | \
                        ODE_1_OPEN_DRAIN_ENABLED | PKE_0_PULL_KEEPER_DISABLED | \
                        PUE_1_PULL_SELECTED | PUS_1_47K_OHM_PULL_UP | HYS_0_HYSTERESIS_DISABLED)

#define I2C_SCL(n)      ((n)? (GPIO4->DR |=1<<20):(GPIO4->DR &=~(1<<20)))
#define I2C_SDA(n)      ((n)? (GPIO4->DR |=1<<19):(GPIO4->DR &=~(1<<19)))
#define I2C_SDA_PAD(n)  ((n)? (GPIO4->GDIR |=1<<19):(GPIO4->GDIR &=~(1<<19)))
#define I2C_SDA_READ    ((GPIO4->PSR)>>19 &0x1)

typedef struct
{
    void (*Init)(void);
    void (*Start)(void);
    void (*Stop)(void);
    void (*SendByte)(uint8_t txdata);
    uint8_t (*ReceiveByte)(void);
    void (*SendACK)(bool ack);
    uint8_t (*ReceiveACK)(void);
}I2C_t;

extern I2C_t IIC;

#endif //!__I2C_H