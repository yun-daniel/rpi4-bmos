#!/bin/bash


# --- QEMU Env. Var. Settings ---
QEMU_SYSTEM="qemu-system-aarch64"
QEMU_BIN="${QEMU_BIN_PATH}/${QEMU_SYSTEM}"

MACHINE="raspi4b"
CPU="cortex-a72"
MEMORY="2G"
KERNEL_IMAGE="build/kernel8.img"


# --- QEMU Executable Check ---
if [ ! -x "${QEMU_BIN}" ]; then
    echo "Error: QEMU executable not found or not executable: ${QEMU_BIN}"
    exit 1
fi

# --- QEMU Version Check ---
QEMU_VERSION_STR=$("${QEMU_BIN}" --version | head -n1)
QEMU_VERSION_NUM=$(echo "$QEMU_VERSION_STR" | grep -oP '\d+\.\d+\.\d+' | head -n1)
QEMU_VERSION_MAJOR=$(echo "$QEMU_VERSION_NUM" | cut -d. -f1)

if [ "$QEMU_VERSION_MAJOR" -lt 9 ]; then
    echo "Error: QEMU version 9.0 or higher is required. Current version: $QEMU_VERSION_NUM"
    exit 1
fi

# --- Debug Mode Check ---
DEBUG_MODE="disabled"
DEBUG_OPTIONS=""
if [ "$1" == "debug" ]; then
    DEBUG_MODE="enabled"
    DEBUG_OPTIONS="-s -S"
fi


# --- Display Settings ---
echo "Launching QEMU with:"
echo "  QEMU        : ${QEMU_BIN}"
echo "  Version     : ${QEMU_VERSION_NUM}"
echo "  Machine     : ${MACHINE}"
echo "  CPU         : ${CPU}"
echo "  Memory      : ${MEMORY}"
echo "  Kernel      : ${KERNEL_IMAGE}"
echo "  Debug Mode  : ${DEBUG_MODE} ${DEBUG_OPTIONS}"


# --- Run QEMU ---
${QEMU_BIN} \
    -M ${MACHINE} \
    -cpu ${CPU} \
    -m ${MEMORY} \
    -nographic \
    -serial mon:stdio \
    -kernel ${KERNEL_IMAGE} \
    ${DEBUG_OPTIONS}
