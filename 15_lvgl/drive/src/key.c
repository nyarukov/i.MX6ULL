/*
 * @Author: Yusaka
 * @Date: 2023-11-18 18:57:25
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 16:56:42
 * @FilePath: /07_ech11/src/key.c
 * @Description: 
 */
/*
 * @Author: Yusaka
 * @Date: 2023-11-18 18:57:25
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-18 20:52:11
 * @FilePath: /04_exit/src/key.c
 * @Description: 
 */
#include "key.h"

void key_init(void){
   

    IOMUXC_SetPinMux(IOMUXC_UART1_CTS_B_GPIO1_IO18,0);
    IOMUXC_SetPinConfig(IOMUXC_UART1_CTS_B_GPIO1_IO18,0xF080);
    gpio_direction(GPIO1,18,gpio_input);
    GPIO1->EDGE_SEL &=~(1<<18);
    GPIO1->ICR2 |=(3<<4);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, GPIO1_io18_irqhandler, NULL);
    exit_cmd(GPIO1,18,ENABLE);
}

void GPIO1_io18_irqhandler(unsigned int giccIar, void *userParam){
    
    static u16 state=0;
    if(gpio_readbit(GPIO1,18)==0){
      state =!state;
      beep_set(state);
    }
    exit_clearfilag(GPIO1,18);

}

