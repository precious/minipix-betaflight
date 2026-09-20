/*
 * This file is part of Cleanflight and Betaflight.
 *
 * Cleanflight and Betaflight are free software. You can redistribute
 * this software and/or modify this software under the terms of the
 * GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * Cleanflight and Betaflight are distributed in the hope that they
 * will be useful, but WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software.
 *
 * If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#define TARGET_BOARD_IDENTIFIER "MPIX"
#define USBD_PRODUCT_STRING     "Betaflight Mini Pix"

/* Gyro / accelerometer */
#define USE_SPI
#define USE_SPI_DEVICE_1

#define SPI1_SCK_PIN            PA5
#define SPI1_MISO_PIN           PA6
#define SPI1_MOSI_PIN           PA7

#define USE_GYRO
#define USE_GYRO_SPI_MPU6500
#define USE_ACC
#define USE_ACC_SPI_MPU6500

#define GYRO_1_CS_PIN           PC15
#define GYRO_1_SPI_INSTANCE     SPI1

#define USE_EXTI
#define USE_GYRO_EXTI
#define GYRO_1_EXTI_PIN         PC14
#define USE_MPU_DATA_READY_SIGNAL

/* Barometer */
#define USE_SPI_DEVICE_2

#define SPI2_SCK_PIN            PB13
#define SPI2_MISO_PIN           PB14
#define SPI2_MOSI_PIN           PB15

#define USE_BARO
#define USE_BARO_LPS22HB

#define BARO_SPI_INSTANCE       SPI2
#define BARO_CS_PIN             PC2

/* Magnetometer */
#define USE_I2C
#define USE_I2C_DEVICE_1

#define I2C1_SCL                PB8
#define I2C1_SDA                PB9

#define USE_MAG
#define USE_MAG_QMC5883

/* UARTs */
#define USE_VCP

#define USE_UART2
#define UART2_TX_PIN            PD5
#define UART2_RX_PIN            PD6

#define USE_UART3
#define UART3_TX_PIN            PD8
#define UART3_RX_PIN            PD9

#define USE_UART4
#define UART4_TX_PIN            PA0
#define UART4_RX_PIN            PA1

#define SERIAL_PORT_COUNT       4

/* SBUS inverter */
#define USE_INVERTER
#define SBUS_RX_PIN             PC13

/* PPM */
#define USE_RX_PPM
#define PPM_PIN                 PB0

/* RSSI */
#define USE_ADC
#define RSSI_ADC_PIN            PC1

/* SD card */
#define USE_SDCARD
#define USE_SDCARD_SDIO
#define ENABLE_BLACKBOX_LOGGING_ON_SDCARD_BY_DEFAULT

/* LEDs */
#define LED0_PIN                PB1
#define LED1_PIN                PC5
#define LED2_PIN                PE12

/* Battery / voltage monitoring */
#define VBUS_SENS_PIN           PA4

/* I/O ports */
#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         0xffff
#define TARGET_IO_PORTE         0xffff

#define USABLE_TIMER_CHANNEL_COUNT 5
#define USED_TIMERS             (TIM_N(1) | TIM_N(3))
