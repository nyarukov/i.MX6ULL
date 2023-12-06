#ifndef __GPIO_H
#define __GPIO_H

#include "common.h"

enum gpio_inout{
    gpio_input,
    gpio_output,
};

void gpio_direction(GPIO_Type *gpiox, uint8_t pin,enum gpio_inout direction);
void gpio_writebit(GPIO_Type *gpiox, uint8_t pin, uint8_t value);
uint8_t gpio_readbit(GPIO_Type *gpiox, uint8_t pin);
void exit_cmd(GPIO_Type *gpiox,uint8_t pin,uint8_t disable);
void exit_clearfilag(GPIO_Type *gpiox,uint8_t pin);
#endif // !__EXIT_H