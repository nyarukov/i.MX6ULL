/*
 * @Author: Yusaka
 * @Date: 2023-11-18 18:57:25
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-20 11:43:27
 * @FilePath: /04_exit/src/key.c
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
    GPIO1->GDIR &=~(1<<18);
    GPIO1->EDGE_SEL &=~(1<<18);
    GPIO1->ICR2 |=(3<<4);
    GIC_EnableIRQ(GPIO1_Combined_16_31_IRQn);
    system_register_irqhandler(GPIO1_Combined_16_31_IRQn, (system_irq_handler_t)GPIO1_io18_irqhandler, NULL);
    
    GPIO1->IMR |=(1<<18);
    
    
}
bool key_read(void){
    return ((GPIO1->DR)>>18 & (0x1))? true : false;
}

void GPIO1_io18_irqhandler(unsigned int giccIar, void *userParam){
    
    static u16 state=0;
    static u16 i=0;
    if(key_read()==0){
      state =!state;
      beep_set(state);
      i++;
    }
    lcd_shownum(50, 26, i, 5, 16, LCD_WHITE);
    GPIO1->ISR |= (1<<18);

}

