# Betaflight 4.1.1 for RadioLink Mini Pix (by ChatGPT)

This package reproduces the working Mini Pix setup we built on 2026-09-20.

It is specifically for a RadioLink Mini Pix with the existing ArduPilot/PX4-compatible bootloader.

## Essential files in this folder

Copy the contents of `betaflight-files/` into the root of a fresh Betaflight 4.1.1 checkout (replace if already exists).

- `src/main/target/MINIPIX/target.h`
- `src/main/target/MINIPIX/target.c`
- `src/main/target/MINIPIX/target.mk`
- `src/link/stm32_flash_minipix.ld`
- `make/mcu/STM32F4.patch`
- `tools/make_minipix_apj.py`

## Build and flash

See `INSTALL.md`.
