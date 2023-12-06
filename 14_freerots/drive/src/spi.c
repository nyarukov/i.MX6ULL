#include "spi.h"

void spi_init(ECSPI_Type *ecspi){
    ecspi->CONREG  =0;
    ecspi->CONREG |= (7 <<20);  //突发长度8个bit

    /* SPI CLK = (SourceCLK / PER_DIVIDER) / (2^POST_DIVEDER)
     * 比如我们现在要设置SPI时钟为6MHz，那么PER_DIVEIDER和POST_DEIVIDER设置如下：
     * PER_DIVIDER = 0X9。
     * POST_DIVIDER = 0X0。
     * SPI CLK = 60000000/(0X9 + 1) = 60000000=6MHz
	 */
    ecspi->CONREG &=~((0XF << 12) | (0XF << 8)); //清除PER_DIVDER和POST_DIVEDER 
    ecspi->CONREG |= (0X9 << 12);   //设置SPI CLK = 6MHz
    
    ecspi->CONREG |= (1<<4);    //spi通道模式选择0
    ecspi->CONREG |= (1<<3);    //向TXFIFO写入数据以后立即开启SPI突发
    ecspi->CONREG |= (1<<0);    //使能ECSPI

    ecspi->CONFIGREG =0;        //设置通道寄存器

    ecspi->PERIODREG =0x2000;   //设置采样周期寄存器,读取数据的时候每次之间间隔
}

void spi_send(ECSPI_Type *ecspi, uint8_t data){
	uint32_t  spitxdata = data;
    /* 选择通道0 */
	ecspi->CONREG &= ~(3 << 18);
	ecspi->CONREG |= (0 << 18);
  	while((ecspi->STATREG & (1 << 0)) == 0){} 	/* 等待发送FIFO为空 */
    ecspi->TXDATA = spitxdata;
}

uint8_t spi_recv(ECSPI_Type *ecspi){
    uint32_t  spirxdata = 0;
 /* 选择通道0 */
	ecspi->CONREG &= ~(3 << 18);
	ecspi->CONREG |= (0 << 18);
    while((ecspi->STATREG & (1 << 3)) == 0){
        delay(100);
        spirxdata = 0;
        break;
    }/* 等待接收FIFO有数据 */
		spirxdata = ecspi->RXDATA;
	return spirxdata;
}
