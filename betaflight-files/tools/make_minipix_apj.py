#!/usr/bin/env python3
"""Create an APJ image for the existing Mini Pix PX4/ArduPilot bootloader."""
import base64, json, subprocess, sys, zlib
FLASH_START = 0x08004000
BOARD_ID = 3
BOARD_REVISION = 0

def main():
    if len(sys.argv) != 3:
        raise SystemExit(f"usage: {sys.argv[0]} INPUT_ELF OUTPUT_APJ")
    elf, output = sys.argv[1:]
    hex_path = output + ".tmp.hex"
    objcopy = "arm-none-eabi-objcopy"
    try:
        subprocess.run([objcopy, "-O", "ihex", elf, hex_path], check=True)
    except FileNotFoundError:
        objcopy = "./tools/gcc-arm-none-eabi-7-2018-q2-update/bin/arm-none-eabi-objcopy"
        subprocess.run([objcopy, "-O", "ihex", elf, hex_path], check=True)
    data, upper = {}, 0
    with open(hex_path, encoding="ascii") as f:
        for line in f:
            raw = bytes.fromhex(line.strip()[1:])
            count = raw[0]; addr = int.from_bytes(raw[1:3], "big"); typ = raw[3]
            payload = raw[4:4 + count]
            if typ == 4:
                upper = int.from_bytes(payload, "big") << 16
            elif typ == 0:
                base = upper + addr
                for i, b in enumerate(payload): data[base + i] = b
    if FLASH_START not in data:
        raise RuntimeError("No firmware found at 0x08004000")
    end = max(a for a in data if a >= FLASH_START) + 1
    image = bytearray([0xFF]) * (end - FLASH_START)
    for a, b in data.items():
        if FLASH_START <= a < end: image[a - FLASH_START] = b
    apj = {"board_id": BOARD_ID, "board_revision": BOARD_REVISION,
           "image_size": len(image),
           "image": base64.b64encode(zlib.compress(bytes(image))).decode("ascii")}
    with open(output, "w", encoding="utf-8") as f: json.dump(apj, f, separators=(",", ":"))
    print(f"Created {output}: {len(image)} bytes")

if __name__ == "__main__": main()
