# MCU = RP2040
# BOOTLOADER = rp2040

TINYUSB = yes

KEYBOARD_TYPE = ANSI

CONSOLE_ENABLE = yes

DYNAMIC_KEYMAP_ENABLE = yes
DYNAMIC_KEYMAP_LAYER_COUNT = 1

ENCODER_ENABLE = yes

# adc.cの追加
SRC += lib/pico-sdk/src/rp2_common/hardware_adc/adc.c

# インクルードパスの追加
CFLAGS += -Ilib/pico-sdk/src/rp2_common/hardware_adc/include
CFLAGS += -Ilib/tinyusb/src
CFLAGS += -Ikeyboards/testamatta/macropad/ex100_test/
