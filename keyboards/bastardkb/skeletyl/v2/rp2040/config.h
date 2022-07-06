/*
 * Copyright 2022 @ykz89
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* Sparkfun RP2040 */
/* Key matrix configuration. */
#define MATRIX_ROW_PINS \
    { GP26, GP5, GP4, GP9 }
#define MATRIX_COL_PINS \
    { GP28, GP15, GP6, GP7, GP8 }

/* Handedness. */
#define MASTER_RIGHT

// To use the handedness pin, resistors need to be installed on the adapter PCB.
// If so, uncomment the following code, and undefine MASTER_RIGHT above.
// #define SPLIT_HAND_PIN GP13
// #define SPLIT_HAND_PIN_LOW_IS_LEFT  // High -> right, Low -> left.

#undef SOFT_SERIAL_PIN
#define SERIAL_USART_TX_PIN GP1

#define SELECT_SOFT_SERIAL_SPEED 1

/* serial.c configuration (for split keyboard). */
#define SOFT_SERIAL_PIN GP1

/* RGB settings. */
#define RGB_DI_PIN GP0

/* I2C Pin mapping (OLED) */
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define I2C_DRIVER I2CD2

/* Splits enables */
#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_POINTING_ENABLE

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U
