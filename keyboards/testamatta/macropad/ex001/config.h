#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x1d8c
#define PRODUCT_ID      0x1101
#define DEVICE_VER      0x0001
#define MANUFACTURER    "hide-key"
#define PRODUCT         "testamatta MacroPad EX001"

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 5

#define MATRIX_ROW_PINS { 28, 26, 14, 4, 6, 8}
#define MATRIX_COL_PINS { 27, 15, 13, 5, 7 }

#define DIODE_DIRECTION COL2ROW

#define DEBOUNCE 5

// #define SERIAL_USART_FULL_DUPLEX
// #define SERIAL_USART_TX_PIN GP0
// #define SERIAL_USART_RX_PIN GP1

#define SERIAL_DEBUG

#define TAPPING_TERM 500
#define PERMISSIVE_HOLD

#define SERIAL_PIO_USE_PIO1


#define NUMBER_OF_ENCODERS 1
#define ENCODERS_PAD_A { GP11 }
#define ENCODERS_PAD_B { GP12 }
#define ENCODER_RESOLUTION 4

// #define ENCODER_DIRECTION_FLIP
