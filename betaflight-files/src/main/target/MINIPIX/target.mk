F405_TARGETS    += $(TARGET)
HSE_VALUE       = 24000000

FEATURES        += VCP SDCARD_SDIO

TARGET_SRC = \
            drivers/accgyro/accgyro_spi_mpu6500.c \
            drivers/accgyro/accgyro_mpu6500.c \
            drivers/barometer/barometer_lps.c \
            drivers/compass/compass_qmc5883l.c
