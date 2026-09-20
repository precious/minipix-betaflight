# Install Betaflight 4.1.1 on RadioLink Mini Pix

## 1. Mac prerequisites

Install Apple's command-line tools:

```sh
xcode-select --install
```

Install Python 3 if the Mac does not have it:

```sh
brew install python
```

If Homebrew is not installed, install it from the official Homebrew website first.

## 2. Clone Betaflight 4.1.1

Let's say all projects will be in the same root directory: betaflight, ardupilot, minipix-betaflight (the current one).
Set an env variables that points to that root directory:

```
export REPOSITORIES_ROOT="~/projects/"
```

then

```sh
cd $REPOSITORIES_ROOT
git clone https://github.com/precious/minipix-betaflight.git
```

then

```sh
cd $REPOSITORIES_ROOT
git clone https://github.com/betaflight/betaflight.git
cd betaflight
git checkout 4.1.1
git submodule update --init --recursive
```

## 3. Copy the Mini Pix files

Copy everything from this package's `betaflight-files/` directory into the Betaflight repository, preserving paths.

```sh
cp -R "$REPOSITORIES_ROOT/minipix-betaflight/betaflight-files/." "$REPOSITORIES_ROOT/betaflight"
```

## 4. Install the exact ARM compiler used by Betaflight 4.1.1

From the Betaflight repository:

```sh
make arm_sdk_install
```

This installs the ARM GCC 7.3.1 toolchain into `betaflight/tools/`.

## 5. Build Betaflight

```sh
make MINIPIX
```

The important output is:

```text
obj/betaflight_4.1.1_MINIPIX.bin
obj/betaflight_4.1.1_MINIPIX.hex
obj/main/betaflight_MINIPIX.elf
```

## 6. Create the `.apj` file for the Mini Pix bootloader

Run:

```sh
python3 tools/make_minipix_apj.py obj/main/betaflight_MINIPIX.elf obj/betaflight_4.1.1_MINIPIX.apj
```

The script creates an ArduPilot/PX4 bootloader-compatible `.apj` image with board ID `3`, which is the board ID reported by this Mini Pix bootloader.

## 7. Prepare the ArduPilot uploader

```sh
cd $REPOSITORIES_ROOT
git clone https://github.com/ArduPilot/ardupilot.git
cd ardupilot
python3 -m venv .venv
source .venv/bin/activate
pip install pyserial
```

## 8. Check that the Mini Pix bootloader is reachable

Connect the Mini Pix by USB and run:

```sh
ls /dev/cu.*
```

The bootloader port will normally look like `/dev/cu.usbmodem01`.

Verify it:

```sh
python3 Tools/scripts/uploader.py --port /dev/cu.usbmodem01 --identify
```

You should see approximately:

```text
Found board 3,0 bootloader rev 5
Chip:
  family: STM32F40x
  flash size: 1032192
  board_type: 3
  board_rev: 0
```

## 9. Flash Betaflight

From the Betaflight repository, with the Mini Pix still connected:

```sh
cd $REPOSITORIES_ROOT/betaflight
$REPOSITORIES_ROOT/ardupilot/.venv/bin/python3 \
  $REPOSITORIES_ROOT/ardupilot/Tools/scripts/uploader.py \
  --port /dev/cu.usbmodem01 \
  obj/betaflight_4.1.1_MINIPIX.apj
```

Adjust the paths if your two repositories are in different directories.

Successful flashing ends with:

```text
Erase  : [====================] 100.0%
Program: [====================] 100.0%
Verify : [====================] 100.0%
Rebooting.
```

## 10. Verify Betaflight

After reboot, reconnect to the new USB serial port using Betaflight Configurator.

Open **CLI** and enter:

```text
version
```

Expected result contains:

```text
Betaflight / MINIPIX (MPIX) 4.1.1
```

At this point the Mini Pix is running Betaflight.
