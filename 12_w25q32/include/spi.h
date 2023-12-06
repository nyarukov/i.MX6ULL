/*
 * @Author: Yusaka
 * @Date: 2023-11-21 21:06:15
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-21 21:29:56
 * @FilePath: /09_spi/include/spi.h
 * @Description: 
 */
#ifndef __SPI_H
#define __SPI_H

#include "common.h"
#include "delay.h"

void spi_init(ECSPI_Type *ecspi);
void spi_send(ECSPI_Type *ecspi, uint8_t data);
uint8_t spi_recv(ECSPI_Type *ecspi);

#endif