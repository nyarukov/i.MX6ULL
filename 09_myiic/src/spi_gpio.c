/*
 * @Author: Yusaka
 * @Date: 2023-11-21 16:14:53
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-21 21:21:01
 * @FilePath: /09_spi/src/spi_gpio.c
 * @Description:
 */
#include "spi_gpio.h"


void spi1_gpio_init(void)
{
    // CS0
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA05_GPIO4_IO26, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA05_GPIO4_IO26, 0x10b0);
    gpio_direction(GPIO4,26,gpio_output);
    gpio_writebit(GPIO4,26,GPIO_RESET);
    
    // SCLK
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA04_ECSPI1_SCLK, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA04_ECSPI1_SCLK, 0x10b0);
    // MISO
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA07_ECSPI1_MISO, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA07_ECSPI1_MISO, 0x10b0);
    // MOSI
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA06_ECSPI1_MOSI, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA06_ECSPI1_MOSI, 0x10b0);
}

void spi2_gpio_init(void)
{
    // CS0
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA01_GPIO4_IO22, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA01_GPIO4_IO22, 0x10b0);
    gpio_direction(GPIO4,22,gpio_output);
    gpio_writebit(GPIO4,22,GPIO_RESET);
    // SCLK
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA00_ECSPI2_SCLK, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA00_ECSPI2_SCLK, 0x10b0);
    // MISO
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA03_ECSPI2_MISO, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA03_ECSPI2_MISO, 0x10b0);
    // MOSI
    IOMUXC_SetPinMux(IOMUXC_CSI_DATA02_ECSPI2_MOSI, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_DATA02_ECSPI2_MOSI, 0x10b0);
}