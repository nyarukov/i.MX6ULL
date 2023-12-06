/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
#include "w25q32.h"

/* Definitions of physical drive number for each drive */
// #define DEV_SPI_FLASH			0	/* Example: Map Ramdisk to physical drive 0 */
// #define DEV_SD			1	/* Example: Map MMC/SD card to physical drive 1 */
// #define DEV_NAND			2	/* Example: Map USB MSD to physical drive 2 */

#define DEV_SPI_FLASH	0	/* Example: Map SPI_FLASH to physical drive 0 */
#define DEV_SD			1	/* Example: Map SD to physical drive 1 */
#define DEV_NAND		2	/* Example: Map NAND to physical drive 2 */

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case DEV_SPI_FLASH :
		stat=(W25Q32_ReadID()!=W25Q32)? STA_NOINIT : 0;
		return stat;
	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat;

	switch (pdrv) {
	case DEV_SPI_FLASH :
		W25Q32_Init();
		stat=RES_OK;
		return stat;

	}
	return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	DRESULT res;

	switch (pdrv) {
	case DEV_SPI_FLASH :
		W25Q32_ReadData(sector*4096,(u8*)buff,count*4096);
		res=RES_OK;
		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	switch (pdrv) {
	case DEV_SPI_FLASH :
	 	W25Q32_SectorErase(sector*4096,ERASE_4KB);
		W25Q32_PageProgram(sector*4096,(u8*)buff,count*4096);
		res=RES_OK;
		return res;
	}

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	switch (pdrv) {
	case DEV_SPI_FLASH :
		switch (cmd)
		{
		case CTRL_SYNC:
			return RES_OK;
			break;
		case GET_SECTOR_COUNT:
			*(DWORD*)buff=1024;
			return RES_OK;
			break;
		case GET_SECTOR_SIZE:
			*(WORD*)buff=4096;
			return RES_OK;
			break;
		case GET_BLOCK_SIZE:
			*(DWORD*)buff=1;
			return RES_OK;
			break;
		default:
			return RES_PARERR;
		}
	}
	return RES_PARERR;
}

