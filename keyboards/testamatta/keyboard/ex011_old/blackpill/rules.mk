# MCU name
MCU = STM32F411
BOARD = BLACKPILL_STM32_F411

# Bootloader selection
BOOTLOADER = tinyuf2

# Build Options
#   Change yes to no to disable
#
KEYBOARD_SHARED_EP = yes

BOOTMAGIC_ENABLE = no      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = no            # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
DYNAMIC_MACRO_ENABLE = no  # Dynamic macros
CONSOLE_ENABLE = no         # Console for debug

CUSTOM_MATRIX = lite        # Substitute custom matrix
SRC += matrix.c

VIA_ENABLE = yes

# MCU_FAMILY = PICO
# MCU_SERIES = RP2040
# MCU = cortex-m0plus

ENCODER_ENABLE = yes
