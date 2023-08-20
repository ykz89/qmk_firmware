# Build Options
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
MOUSEKEY_ENABLE = no        # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no         # Enable support for HD44780 based LCDs
UNICODE_ENABLE = yes        # Unicode support
SPLIT_KEYBOARD = no         # Split common
VIA_ENABLE = yes
LTO_ENABLE = yes

# Specify the directories
QUANTUM_DIR=./quantum
PICO_SDK_PATH=./lib/pico-sdk/

# Specify the required source files from the Pico SDK
SRC += $(QUANTUM_DIR)/keyboards/testamatta/macropad/ex100/ex100.c
SRC += $(PICO_SDK_PATH)src/rp2_common/hardware/adc.c
SRC += $(PICO_SDK_PATH)src/common/pico_time/time.c

# Include paths
INCLUDE_PATHS += -I$(PICO_SDK_PATH)src/common/pico_base/include/
INCLUDE_PATHS += -I$(PICO_SDK_PATH)src/common/pico_time/include/
INCLUDE_PATHS += -I$(PICO_SDK_PATH)src/common/pico_util/include/
INCLUDE_PATHS += -I$(PICO_SDK_PATH)src/common/pico_sync/include/
