// Copyright 2022 aki27 (@aki27kbd)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include "config_common.h"
#define OLED_FONT_H "keyboards/aki27/cocot36plus/lib/glcdfont.c"


/* VIA */
#define DYNAMIC_KEYMAP_LAYER_COUNT 8


/* key matrix size */
#define MATRIX_COLS 10
#define MATRIX_ROWS 4


/* tapping term */
#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 200
#define IGNORE_MOD_TAP_INTERRUPT


/* Encoder */
#define ENCODERS_PAD_A { GP28 }
#define ENCODERS_PAD_B { GP29 }
#define ENCODER_RESOLUTION 2

/* Matrix*/
#define MATRIX_COL_PINS { GP25, GP24, GP23, GP22, GP21, GP15, GP14, GP13, GP12, GP11 }
//#define MATRIX_COL_PINS { GP25, GP3, GP8, GP9, GP21, GP15, GP14, GP13, GP12, GP11 }
#define MATRIX_ROW_PINS { GP20, GP19, GP18, GP17 }

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW


/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#undef LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#undef LOCKING_RESYNC_ENABLE


/* RGB LED */
#define WS2812_PIO_USE_PIO1
#define RGB_DI_PIN GP0

#ifdef RGBLIGHT_ENABLE
    #define RGBLED_NUM 45
    #define RGBLIGHT_LIMIT_VAL 80
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17

    // #define RGBLIGHT_ANIMATIONS
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
#endif


/* RGB MATRIX */
#define DRIVER_LED_TOTAL 45

#ifdef RGB_MATRIX_ENABLE
  #define RGB_MATRIX_KEYPRESSES // reacts to keypresses
//  #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
  #define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects
  #define RGB_DISABLE_TIMEOUT 120000 // number of milliseconds to wait until rgb automatically turns off
//  #define RGB_DISABLE_AFTER_TIMEOUT 0 // OBSOLETE: number of ticks to wait until disabling effects
  #define RGB_DISABLE_WHEN_USB_SUSPENDED true// turn off effects when suspended
//  #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
//  #define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
  #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 240 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
//  #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_LEFT_RIGHT // Sets the default mode, if none has been set
//  #define RGB_MATRIX_STARTUP_HUE 0 // Sets the default hue value, if none has been set
//  #define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set
//  #define RGB_MATRIX_STARTUP_VAL 50 // Sets the default brightness value, if none has been set
//  #define RGB_MATRIX_STARTUP_SPD 127 // Sets the default animation speed, if none has been set
#define RGB_MATRIX_HUE_STEP 4
#define RGB_MATRIX_SAT_STEP 4
#define RGB_MATRIX_VAL_STEP 4
#define RGB_MATRIX_SPD_STEP 4
//  #define RGB_MATRIX_DISABLE_KEYCODES // disables control of rgb matrix by keycodes (must use code functions to control the feature)
//  #define RGB_MATRIX_SPLIT { X, Y }     // (Optional) For split keyboards, the number of LEDs connected on each half. X = left, Y = Right.
                                        // If RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR

#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SPLASH
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL
#endif


/* OLED */

#ifdef OLED_ENABLE
#    undef RP_I2C_USE_I2C0
#    define RP_I2C_USE_I2C0 FALSE
#    undef RP_I2C_USE_I2C1
#    define RP_I2C_USE_I2C1 TRUE
#    define I2C_DRIVER I2CD2
#    define I2C1_SDA_PIN GP26
#    define I2C1_SCL_PIN GP27
#endif


/* Trackball */

#ifdef POINTING_DEVICE_ENABLE

#    undef RP_SPI_USE_SPI0
#    define RP_SPI_USE_SPI0 TRUE
#    undef RP_SPI_USE_SPI1
#    define RP_SPI_USE_SPI1 FALSE
#    define SPI_DRIVER SPID0

//#    define SPI_SCK_PIN GP22 //6
//#    define SPI_MISO_PIN GP24 //4
//#    define SPI_MOSI_PIN GP23 //7
#    define SPI_SCK_PIN GP2
#    define SPI_MISO_PIN GP4
#    define SPI_MOSI_PIN GP3

#endif


#ifndef PMW33XX_CS_PIN
#    define PMW33XX_CS_PIN GP1
#endif



#define POINTING_DEVICE_ROTATION_180


/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
