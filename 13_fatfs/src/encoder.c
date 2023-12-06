/*
 * @Author: Yusaka
 * @Date: 2023-11-20 10:04:57
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 17:23:07
 * @FilePath: /07_ech11/src/encoder.c
 * @Description:
 */
#include "encoder.h"

void encoder_init(void)
{
    /*SW*/
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO05_GPIO1_IO05, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO05_GPIO1_IO05, ENCODER_PAD_CONFIG);
    gpio_direction(GPIO5,5,gpio_input);
    GPIO1->EDGE_SEL &= ~(1 << 5);
    GPIO1->ICR1 |= (0 << 5 * 2);
    /*A*/
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO02_GPIO1_IO02, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO02_GPIO1_IO02, ENCODER_PAD_CONFIG);
    gpio_direction(GPIO5,2,gpio_input);
    GPIO1->EDGE_SEL &= ~(1 << 2);
    GPIO1->ICR1 |= (2 << 2 * 2);
    /*B*/
    IOMUXC_SetPinMux(IOMUXC_GPIO1_IO04_GPIO1_IO04, 0);
    IOMUXC_SetPinConfig(IOMUXC_GPIO1_IO04_GPIO1_IO04, ENCODER_PAD_CONFIG);
    gpio_direction(GPIO5,4,gpio_input);
    GPIO1->EDGE_SEL &= ~(1 << 4);
    GPIO1->ICR1 |= (2 << 2 * 4);

    GIC_EnableIRQ(GPIO1_Combined_0_15_IRQn);
    system_register_irqhandler(GPIO1_Combined_0_15_IRQn, encoder_handler, NULL);
    exit_cmd(GPIO1, 5, ENABLE);
    exit_cmd(GPIO1, 2, ENABLE);
    exit_cmd(GPIO1, 4, ENABLE);
}
int32_t i = 0;
void encoder_handler(unsigned int giccIar, void *param)
{
    static u8 state = 0;
    if (((GPIO1->DR) >> 5 & (0x1)) == 0)
    {
        state = !state;
        beep_set(state);
    }
    if (!(gpio_readbit(GPIO1,2)) || ((GPIO1->DR) >> 4 & (0x1)))
    {
        i--;
    }
    if (!(gpio_readbit(GPIO1,4)) || (gpio_readbit(GPIO1,2)))
    {
        i++;
    }
    exit_clearfilag(GPIO1, 5);
    exit_clearfilag(GPIO1, 2);
    exit_clearfilag(GPIO1, 4);
}
