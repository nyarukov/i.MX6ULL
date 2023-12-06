/*
 * @Author: Yusaka
 * @Date: 2023-11-25 16:51:25
 * @LastEditors: Yusaka
 * @LastEditTime: 2023-11-25 17:03:07
 * @FilePath: /09_iic/src/mpu6050.c
 * @Description:
 */
#include "mpu6050.h"

static void MPU6050_init(void);
static uint8_t MPU6050_ID(void);
static void MPU6050_Send(uint8_t RegAddress, uint8_t Data);
static uint8_t MPU6050_Read(uint8_t RegAddress);
static void MPU6050_ReadData(void);

MPU6050_t mpu6050 = {
    .Init = MPU6050_init,
    .ID = MPU6050_ID,
    .ReadData=MPU6050_ReadData
};

void MPU6050_init(void)
{
    IIC.Init();
    MPU6050_Send(MPU6050_POWER1, 0x80);
    delayms(1000);
    MPU6050_Send(MPU6050_POWER1, 0x01);
    MPU6050_Send(MPU6050_POWER2, 0x00);
    // MPU6050_Send(MPU6050_INT_ENABLE, 0x00);
    // MPU6050_Send(MPU6050_FIFO_EN, 0x00);

    MPU6050_Send(MPU6050_SMPRT_DIV, 0x9);
    MPU6050_Send(MPU6050_CONFIG, 0x06);
    MPU6050_Send(MPU6050_GYRO_CONFIG, 0x18);
    MPU6050_Send(MPU6050_ACCEL_CONFIG, 0x18);
}

uint8_t MPU6050_ID(void)
{
    return MPU6050_Read(MPU6050_WHO_AM_I);
}

void MPU6050_Send(uint8_t RegAddress, uint8_t Data)
{
    IIC.Start();
    IIC.SendByte(MPU6050_ADDRESS);
    IIC.ReceiveACK();
    IIC.SendByte(RegAddress);
    IIC.ReceiveACK();
    IIC.SendByte(Data);
    IIC.ReceiveACK();
    IIC.Stop();
}
uint8_t MPU6050_Read(uint8_t RegAddress)
{
    uint8_t RegData;
    IIC.Start();
    IIC.SendByte(MPU6050_ADDRESS);
    IIC.ReceiveACK();
    IIC.SendByte(RegAddress);
    IIC.ReceiveACK();
    IIC.Start();
    IIC.SendByte(MPU6050_ADDRESS | 0x01);
    IIC.ReceiveACK();
    RegData = IIC.ReceiveByte();
    IIC.SendACK(1);
    IIC.Stop();
    return RegData;
}

void MPU6050_ReadData(void){
    mpu6050.ACCEL_XOUT=(MPU6050_Read(MPU6050_ACCEL_XOUT_H)<<8)|(MPU6050_Read(MPU6050_ACCEL_XOUT_L));
    mpu6050.ACCEL_YOUT=(MPU6050_Read(MPU6050_ACCEL_YOUT_H)<<8)|(MPU6050_Read(MPU6050_ACCEL_YOUT_L));
    mpu6050.ACCEL_ZOUT=(MPU6050_Read(MPU6050_ACCEL_ZOUT_H)<<8)|(MPU6050_Read(MPU6050_ACCEL_ZOUT_L));
    mpu6050.GYRO_XOUT=(MPU6050_Read(MPU6050_GYRO_XOUT_H)<<8)|(MPU6050_Read(MPU6050_GYRO_XOUT_L));
    mpu6050.GYRO_YOUT=(MPU6050_Read(MPU6050_GYRO_YOUT_H)<<8)|(MPU6050_Read(MPU6050_GYRO_YOUT_L));
    mpu6050.GYRO_ZOUT=(MPU6050_Read(MPU6050_GYRO_ZOUT_H)<<8)|(MPU6050_Read(MPU6050_GYRO_ZOUT_L));
    mpu6050.TEMP=(MPU6050_Read(MPU6050_TEMP_OUT_H)<<8)|(MPU6050_Read(MPU6050_TEMP_OUT_L));
}