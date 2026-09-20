/*
*****************************************************************************
**
**  File        : stm32_flash_minipix.ld
**
**  Abstract    : Linker script for RadioLink Mini Pix / STM32F405.
**
*****************************************************************************
*/

/*
0x08000000 to 0x080FFFFF  1024K full flash,
0x08000000 to 0x08003FFF   16K ArduPilot bootloader,
0x08004000 to 0x080FFFFF 1008K Betaflight firmware.
*/

/* Specify the memory areas */
MEMORY
{
    FLASH (rx)        : ORIGIN = 0x08004000, LENGTH = 10K
    FLASH_CUSTOM_DEFAULTS (r) : ORIGIN = 0x08006800, LENGTH = 6K
    FLASH_CONFIG (r)  : ORIGIN = 0x08008000, LENGTH = 16K
    FLASH1 (rx)       : ORIGIN = 0x0800C000, LENGTH = DEFINED(USE_CUSTOM_DEFAULTS_EXTENDED) ? 976K : 992K
    FLASH_CUSTOM_DEFAULTS_EXTENDED (r): ORIGIN = DEFINED(USE_CUSTOM_DEFAULTS_EXTENDED) ? 0x080FC000 : 0x08100000, LENGTH = DEFINED(USE_CUSTOM_DEFAULTS_EXTENDED) ? 16K : 0K

    SYSTEM_MEMORY (rx): ORIGIN = 0x1FFF0000, LENGTH = 29K

    RAM (rwx)         : ORIGIN = 0x20000000, LENGTH = 128K
    CCM (rwx)         : ORIGIN = 0x10000000, LENGTH = 64K
    BACKUP_SRAM (rwx) : ORIGIN = 0x40024000, LENGTH = 4K
    MEMORY_B1 (rx)    : ORIGIN = 0x60000000, LENGTH = 0K
}

REGION_ALIAS("STACKRAM", CCM)
REGION_ALIAS("FASTRAM", CCM)
REGION_ALIAS("VECTAB", RAM)

INCLUDE "stm32_flash_split.ld"
