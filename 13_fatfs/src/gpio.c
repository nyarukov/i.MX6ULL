/*
 * @Author: Yusaka
 * @Date: 2023-11-20 10:17:54
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-21 21:20:34
 * @FilePath: /09_spi/src/gpio.c
 * @Description:
 */
#include "gpio.h"
/*
 *@brief Function 设置引脚方向
 */
void gpio_direction(GPIO_Type *gpiox, uint8_t pin, enum gpio_inout direction)
{
    if (direction == gpio_input)
        gpiox->GDIR &= ~(1 << pin);
    else
        gpiox->GDIR |= (1 << pin);
}
void gpio_writebit(GPIO_Type *gpiox, uint8_t pin, uint8_t value)
{
    if (value==GPIO_SET){
        
        gpiox->DR |= (1 << pin);
    }else{
        gpiox->DR &= ~(1 << pin);
    }
}
uint8_t gpio_readbit(GPIO_Type *gpiox, uint8_t pin)
{
    return ((gpiox->DR) >> pin & (0x1)) ? 1 : 0;
}

void exit_cmd(GPIO_Type *gpiox, uint8_t pin, u8 disable)
{
    if (disable)
        gpiox->IMR |= (1 << pin);
    else
        gpiox->IMR &= ~(1 << pin);
}
void exit_clearfilag(GPIO_Type *gpiox, uint8_t pin)
{
    gpiox->ISR |= (1 << pin);
}
