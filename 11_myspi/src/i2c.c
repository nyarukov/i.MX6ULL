#include "i2c.h"

static void I2C_Init(void);
static void I2C_Start(void);
static void I2C_Stop(void);
static void I2C_SendByte(uint8_t txdata);
static uint8_t I2C_ReceiveByte(void);
static void I2C_SendACK(bool ack);
static uint8_t I2C_ReceiveACK(void);

I2C_t IIC = {
    I2C_Init,
    I2C_Start,
    I2C_Stop,
    I2C_SendByte,
    I2C_ReceiveByte,
    I2C_SendACK,
    I2C_ReceiveACK,
};

void I2C_Init(void)
{
    // SCL
    IOMUXC_SetPinMux(IOMUXC_CSI_HSYNC_GPIO4_IO20, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_HSYNC_GPIO4_IO20, I2C_PAD);
    GPIO4->GDIR |=(1<<20);
    // SDA
    IOMUXC_SetPinMux(IOMUXC_CSI_VSYNC_GPIO4_IO19, 0);
    IOMUXC_SetPinConfig(IOMUXC_CSI_VSYNC_GPIO4_IO19, I2C_PAD);
    GPIO4->GDIR |=(1<<19);
}
void I2C_Start(void)
{
    I2C_SDA(1);
    I2C_SCL(1);
    delayus(4);
    I2C_SDA(0);
    delayus(5);
    I2C_SCL(0);
    delayus(4);
}
void I2C_Stop(void)
{
    I2C_SDA(0);
    delayus(4);
    I2C_SCL(1);
    delayus(5);
    I2C_SDA(1);
    delayus(4);
}
void I2C_SendByte(uint8_t txdata)
{
    uint8_t i;
    for(i=0;i<8;i++){
        I2C_SDA(txdata & 0x80);
        delayus(4);
        I2C_SCL(1);
        delayus(4);
        I2C_SCL(0);
        delayus(4);
        txdata<<=1;
    }
}
uint8_t I2C_ReceiveByte(void)
{
    I2C_SDA_PAD(0);
    uint8_t i,rxdata=0;
    for (i = 0; i <8; i++)
    {
        I2C_SCL(1);
        rxdata |= (I2C_SDA_READ<<i);
        delayus(4);
        I2C_SCL(0);
        delayus(4);
    }
    I2C_SDA_PAD(1);
    return rxdata;
}
void I2C_SendACK(bool ack)
{
    I2C_SDA(ack);
    delayus(4);
    I2C_SCL(1);
    delayus(4);
    I2C_SCL(0);
    delayus(4);
}
uint8_t I2C_ReceiveACK(void)
{
    I2C_SDA_PAD(0);
    uint8_t ACK=0;
    I2C_SCL(1);
    delayus(4);
    ACK=I2C_SDA_READ;
    delayus(4);
    I2C_SCL(0);
    delayus(4);
    I2C_SDA_PAD(1);
    return ACK;
}