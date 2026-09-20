# Betaflight 4.1.1 for RadioLink Mini Pix (by ChatGPT)

This package reproduces the working Mini Pix setup we built on 2026-09-20.

It is specifically for a **RadioLink Mini Pix (STM32F405)** with the existing **ArduPilot/PX4-compatible bootloader**.

## Why custom Betaflight files are required

The Mini Pix is **not supported by Betaflight 4.1.1 out of the box**. There is no standard Betaflight target that can simply be selected and flashed to this board.

The Mini Pix requires a custom target because its hardware differs from the standard Betaflight F405 targets:

- custom GPIO/pin assignments for the IMU, SPI, I2C, UARTs, LEDs, USB, etc.;
- custom target configuration and enabled peripherals;
- the Mini Pix uses a specific hardware oscillator frequency, which must be passed to the STM32 startup/system configuration through `HSE_VALUE`;
- the firmware must use the Mini Pix's particular flash layout.

### Flash layout

The Mini Pix has an existing bootloader occupying the beginning of the STM32 internal flash.

The bootloader occupies:

```text
0x08000000 - 0x08003FFF   16 KiB
```

Therefore Betaflight cannot be built as a normal firmware starting at 0x08000000.

The Betaflight image starts at:

```
0x08004000
```

There are also separate regions used by the Betaflight target for configuration/default data. The custom linker script describes this layout.

Because of these offsets and regions, a generic STM32F405 Betaflight firmware is *not interchangeable* with this Mini Pix firmware.

## Why Betaflight 4.1.1

This package is specifically based on the *Betaflight 4.1.1* source tree.

A different Betaflight version should not be substituted without checking its target/build system and adapting the Mini Pix target again. The target files and build system are version-specific.

## Why the ArduPilot uploader is used

The Mini Pix already contains an ArduPilot/PX4-compatible bootloader.

The bootloader identifies itself as:

```
board type: 3
board revision: 0
STM32F40x
bootloader protocol: 5
flash size: 1032192 bytes
```

It expects firmware in ArduPilot's `.apj` format.

Therefore we do not flash the normal Betaflight `.hex` file directly.

Instead:

1. Betaflight is compiled for the custom Mini Pix target.
1. The resulting firmware is converted into an `.apj` file with the required board metadata.
1. ArduPilot's `uploader.py` is used to communicate with the existing bootloader.
1. The uploader erases, programs and verifies the Betaflight firmware.
1. The bootloader reboots the board and Betaflight starts.

This does *not* mean that ArduPilot is installed on the board. The ArduPilot repository is only used for its bootloader uploader tool.

## Essential files in this folder

Copy the contents of `betaflight-files/` into the root of a fresh Betaflight 4.1.1 checkout, replacing existing files if necessary.

The custom files are:

* src/main/target/MINIPIX/target.h — Mini Pix hardware/pin configuration
* src/main/target/MINIPIX/target.c — Mini Pix target-specific initialization/configuration
* src/main/target/MINIPIX/target.mk — Mini Pix build configuration
* src/link/stm32_flash_minipix.ld — Mini Pix flash/RAM layout and bootloader offset
* make/mcu/STM32F4.mk — STM32F4 build configuration required for the Mini Pix target
* tools/make_minipix_apj.py — converts the built Betaflight image into the `.apj` format required by the bootloader

## Build and flash

See `INSTALL.md` for the complete reproducible procedure.