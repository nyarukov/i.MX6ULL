#include "w25q32.h"

void W25Q32_Init(void)
{
    MYSPI_Init();
}
void W25Q32_ReadID(uint8_t *MID, uint16_t *DID)
{
    MYSPI_CS(0);
    MYSPI_SendByte(W25Q64_JEDEC_ID);
    *MID=MYSPI_SendByte(W25Q64_DUMMY_BYTE);
    *DID=(MYSPI_SendByte(W25Q64_DUMMY_BYTE)<<8) | MYSPI_SendByte(W25Q64_DUMMY_BYTE);
    MYSPI_CS(1);
}
void W25Q32_Enable(void)
{
    MYSPI_CS(0);
    MYSPI_SendByte(W25Q64_WRITE_ENABLE);
    MYSPI_CS(1);
}
void W25Q32_Disable(void)
{
    MYSPI_CS(0);
    MYSPI_SendByte(W25Q64_WRITE_DISABLE);
    MYSPI_CS(1);
}
void W25Q32_State(void)
{
    MYSPI_CS(0);
    MYSPI_SendByte(W25Q64_READ_STATUS_REGISTER_1);
    while (MYSPI_SendByte(W25Q64_DUMMY_BYTE) & 0x01);
    MYSPI_CS(1);
}
void W25Q32_PageProgram(uint32_t Address, uint8_t *DataArr, uint16_t length)
{
    W25Q32_Enable();
    MYSPI_CS(0);
    uint16_t i;
    MYSPI_SendByte(W25Q64_PAGE_PROGRAM);
    MYSPI_SendByte((Address >> 16) & 0xFF);
    MYSPI_SendByte((Address >> 8) & 0xFF);
    MYSPI_SendByte(Address & 0xFF);
    for (i = 0; i < length; i++)
    {
        MYSPI_SendByte(DataArr[i]);
    }
    MYSPI_CS(1);
    W25Q32_State();
}
void W25Q32_SectorErase(uint32_t Address, W25Q64_ERASE_Size Size)
{
    W25Q32_Enable();
    MYSPI_CS(0);
    MYSPI_SendByte(Size);
    MYSPI_SendByte((Address >> 16) & 0xFF);
    MYSPI_SendByte((Address >> 8) & 0xFF);
    MYSPI_SendByte(Address & 0xFF);
    MYSPI_CS(1);
    W25Q32_State();
}
void W25Q32_ReadData(uint32_t Address, uint8_t *DataArr, uint32_t length)
{
    MYSPI_CS(0);
    uint16_t i;
    MYSPI_SendByte(W25Q64_READ_DATA);
    MYSPI_SendByte((Address>>16) & 0xFF);
    MYSPI_SendByte((Address>>8) & 0xFF);
    MYSPI_SendByte(Address & 0xFF);
    for (i = 0; i < length; i++)
    {
        DataArr[i] = MYSPI_SendByte(W25Q64_DUMMY_BYTE);
    }
    MYSPI_CS(1);
}
