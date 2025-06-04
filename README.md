# RPi4 bare-metal OS : A minimal operating system from scratch

A personal operating system project targeting the **Raspberry Pi 4**, starting from **bare-metal development** and gradually building up minimal OS functionalities.  
This project aims to explore how low-level systems work by building everything from scratch using C and assembly.

---

## Key Features

- **Bare-metal AArch64 kernel**
- **EL1 execution** with full control over ARMv8 exception levels
- **QEMU emulation support**
- **Bootloader-compatible `kernel8.img` output**
- **Exception and IRQ handling** with GIC-400 initialization
- **Round-robin task scheduler** with context switching
- **Bitmap-based page allocator**
- **UART driver** for serial console output

---

## Requirements

### Development Host
- Ubuntu 24.04 LTS
- Arm GNU Toolchain (`aarch64-none-elf-gcc`)
- QEMU 9.0 or higher (`qemu-system-aarch64`)
- `make`

### Target Hardware (Planned)
- Raspberry Pi 4 Model B

---

## Setup and Build

### Install Toolchain
```bash
# Downloads and Installs Arm GNU Toolchain
wget https://developer.arm.com/-/media/Files/downloads/gnu/14.2.rel1/binrel/arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-elf.tar.xz
tar -xf arm-gnu-toolchain-14.2.rel1-x86_64-aarch64-none-elf.tar.xz
```

### Install QEMU
```bash
# Dependency for QEMU 10.0.0
sudo apt install -y sphinx sphinx-rtd-theme ninja-build meson pkg-config libglib2.0-dev flex bison

# Downloads and Installs QEMU lastest version
wget https://download.qemu.org/qemu-10.0.0.tar.xz
tar xvJf qemu-10.0.0.tar.xz
cd qemu-10.0.0
./configure
make
```

### Set Environment
```bash
# ARM GNU Toolchain
export PATH="/data/opt/arm-gcc/bin:$PATH"

# QEMU
export QEMU_BIN_PATH="/data/opt/qemu-10.0.0/build"
```
Changes the paths to your own

### Build Targets
```bash
make          # default build
make debug    # build with debug symbols
make dump     # generate disassembly (kernel8.dump)
```

## Run with QEMU

```bash
./run-qemu.sh         # normal run
./run-qemu.sh debug   # with -s -S for GDB debugging
```

To debug with GDB:
```bash
aarch64-none-elf-gdb build/kernel8.elf
(gdb) target remote localhost:1234
```

---

## Notes
