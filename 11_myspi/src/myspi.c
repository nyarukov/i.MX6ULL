#include "myspi.h"

void MYSPI_Init(void){
    //CS
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA01_GPIO4_IO22,0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA01_GPIO4_IO22,MYSPI_PAD);
    GPIO4->GDIR |=(1<<22);
    MYSPI_CS(1);
    //SCLK
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA03_GPIO4_IO24,0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA03_GPIO4_IO24,MYSPI_PAD);
    GPIO4->GDIR |=(1<<24);
    MYSPI_SCLK(1);
    //MISO
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA05_GPIO4_IO26,0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA05_GPIO4_IO26,MYSPI1_PAD);
    GPIO4->GDIR &=~(1<<26);
    //MOSI
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA07_GPIO4_IO28,0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA07_GPIO4_IO28,MYSPI_PAD);
    GPIO4->GDIR |=(1<<28);
    MYSPI_MOSI(1);
}
uint8_t MYSPI_SendByte(uint8_t data){
    MYSPI_CS(0);
    uint8_t i;
    for(i=0;i<8;i++){
        MYSPI_MOSI(data & 0x80);
        MYSPI_SCLK(1);
        data<<=1;
        data|=(MYSPI_MISO);
        MYSPI_SCLK(0);
    }
    MYSPI_CS(1);
    return data;
}