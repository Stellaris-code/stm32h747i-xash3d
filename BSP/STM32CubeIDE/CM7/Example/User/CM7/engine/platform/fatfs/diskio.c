/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

#include "stm32h747i_discovery_sd.h"

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

#define CACHE_BLOCK_SIZE 512

#define LRU_CACHE_SIZE (512*1024)
#define LRU_ENTRIES (LRU_CACHE_SIZE/CACHE_BLOCK_SIZE)
#define PREFETCH_COUNT 16

typedef struct lru_entry_t
{
	uint32_t sector;
	uint32_t last_access;
} lru_entry_t;

lru_entry_t lru_info[LRU_ENTRIES];

#if 0
uint8_t cache_data[LRU_CACHE_SIZE];
#else
// Framebuffer used as a diskcache during loading screens
uint8_t* cache_data = 0x24000000;
#endif

DRESULT actual_disk_read(uint32_t sector, void* buff, uint32_t count)
{
	uint32_t status = BSP_SD_ReadBlocks(0, (uint32_t *)buff, sector, count);

	while(BSP_SD_GetCardState(0) != SD_TRANSFER_OK);

	return status != BSP_ERROR_NONE ? RES_ERROR : RES_OK;
}

static void* get_cache(uint32_t sector)
{
	uint32_t tick = HAL_GetTick();

	// scan to see if this sector is in the cache
	uint32_t oldest_entry = 0;
	uint32_t oldest_entry_access = 0xFFFFFFFF;
	for (int i = 0; i < LRU_ENTRIES; ++i)
	{
		if (lru_info[i].last_access < oldest_entry_access)
		{
			oldest_entry_access = lru_info[i].last_access;
			oldest_entry = i;
		}
		if (lru_info[i].last_access && lru_info[i].sector == sector)
		{
			lru_info[i].last_access = tick;
			return &cache_data[i * CACHE_BLOCK_SIZE];
		}
	}

	int prefetch = 0;
	if (oldest_entry + PREFETCH_COUNT < LRU_ENTRIES)
		prefetch = 1;

	if (prefetch)
	{
		DRESULT res = actual_disk_read(sector, &cache_data[oldest_entry * CACHE_BLOCK_SIZE], PREFETCH_COUNT);
		if (res == RES_ERROR)
			return 0;

		for (int i = 0; i < PREFETCH_COUNT; ++i)
		{
			lru_info[oldest_entry + i].sector = sector + i;
			lru_info[oldest_entry + i].last_access = tick;
		}

		return &cache_data[oldest_entry * CACHE_BLOCK_SIZE];
	}
	else
	{
		// Data is not in the cache, evict the oldest entry
		DRESULT res = actual_disk_read(sector, &cache_data[oldest_entry * CACHE_BLOCK_SIZE], 1);
		if (res == RES_ERROR)
			return 0;

		lru_info[oldest_entry].sector = sector;
		lru_info[oldest_entry].last_access = tick;

		return &cache_data[oldest_entry * CACHE_BLOCK_SIZE];
	}
}

static void cache_invalidate(uint32_t sector)
{
	for (int i = 0; i < LRU_ENTRIES; ++i)
	{
		if (lru_info[sector].sector == sector)
		{
			lru_info[sector].last_access = 0;
			return;
		}
	}
}

void disk_cache_flush()
{
	for (int i = 0; i < LRU_ENTRIES; ++i)
		lru_info[i].last_access = 0;
}

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	if (BSP_SD_IsDetected(pdrv) == SD_PRESENT)
	{
		return 0;
	}
	else
		return STA_NODISK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{

	return 0;
}


/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	for (int i = 0; i < count; ++i)
	{
		void* ptr = get_cache(sector + i);
		if (!ptr)
			return RES_ERROR;
		memcpy(buff + i*CACHE_BLOCK_SIZE, ptr, CACHE_BLOCK_SIZE);
	}
	return RES_OK;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

// To be safe, disable writes for now
#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
	for (int i = 0; i < count; ++i)
		cache_invalidate(sector + i);

	uint32_t status = RES_OK;
// <STM MOD>
#if 0
	status = BSP_SD_WriteBlocks(pdrv, (uint32_t *)buff, sector, count);

	while(BSP_SD_GetCardState(pdrv) != SD_TRANSFER_OK);
#endif

	return status != BSP_ERROR_NONE ? RES_ERROR : RES_OK;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	if(cmd == CTRL_SYNC) {
		return RES_OK;
	} else {
		// should never be called
		return RES_ERROR;
	}
}

