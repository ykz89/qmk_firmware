/*
Copyright 2022 aki27

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "quantum.h"
#include <math.h>
#include "cocot46plus.h"
#include "wait.h"
#include "debug.h"
#include <stdio.h>



// Invert vertical scroll direction
#define COCOT_SCROLL_INVERT

// Enable scroll mode while SCRL_MO key is hold
// #define COCOT_SCROLL_MOMENTARY

// #define COCOT_DRAGSCROLL_FIXED

/*
#define COCOT_CPI_OPTIONS { 375, 875, 1375 }
#define COCOT_CPI_DEFAULT 1

#define COCOT_SCROLL_DIVIDERS { 1, 2, 4 }
#define COCOT_SCROLL_DIV_DEFAULT 0

#define COCOT_ROTATION_ANGLE { -60, -30, 0, 30, 60 }
#define COCOT_ROTATION_DEFAULT 0
*/


#ifndef COCOT_CPI_OPTIONS
#    define COCOT_CPI_OPTIONS { 500, 750, 1000, 1250 }
#    ifndef COCOT_CPI_DEFAULT
#       define COCOT_CPI_DEFAULT 1
#    endif
#endif
#ifndef COCOT_CPI_DEFAULT
#    define COCOT_CPI_DEFAULT 1
#endif

#ifndef COCOT_SCROLL_DIVIDERS
#    define COCOT_SCROLL_DIVIDERS { 1, 2, 4 }
#    ifndef COCOT_SCROLL_DIV_DEFAULT
#       define COCOT_SCROLL_DIV_DEFAULT 1
#    endif
#endif
#ifndef COCOT_SCROLL_DIV_DEFAULT
#    define COCOT_SCROLL_DIV_DEFAULT 1
#endif


#ifndef COCOT_ROTATION_ANGLE
#    define COCOT_ROTATION_ANGLE { -45, 0, 45 }
#    ifndef COCOT_ROTATION_DEFAULT
#       define COCOT_ROTATION_DEFAULT 2
#    endif
#endif
#ifndef COCOT_ROTATION_DEFAULT
#    define COCOT_ROTATION_DEFAULT 2
#endif


/*
#ifndef COCOT_DRAGSCROLL_CPI
#    define COCOT_DRAGSCROLL_CPI 375  // Fixed-CPI Drag Scroll
#endif
#ifndef COCOT_DRAGSCROLL_MULTIPLIER
#    define COCOT_DRAGSCROLL_MULTIPLIER 0.75  // Variable-CPI Drag Scroll
#endif
*/


keyboard_config_t keyboard_config;
uint16_t cpi_array[] = COCOT_CPI_OPTIONS;
uint16_t scrl_div_array[] = COCOT_SCROLL_DIVIDERS;
uint16_t angle_array[] = COCOT_ROTATION_ANGLE;
#define CPI_OPTION_SIZE (sizeof(cpi_array) / sizeof(uint16_t))
#define SCRL_DIV_SIZE (sizeof(scrl_div_array) / sizeof(uint16_t))
#define ANGLE_SIZE (sizeof(angle_array) / sizeof(uint16_t))


// Trackball State
bool     is_scroll_mode    = false;
bool     BurstState        = false;  // init burst state for Trackball module
uint16_t MotionStart       = 0;      // Timer for accel, 0 is resting state

 
void pointing_device_init_kb(void) {
    // set the CPI.
    pointing_device_set_cpi(cpi_array[keyboard_config.cpi_idx]);
}


report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {

    uint16_t deg = angle_array[keyboard_config.rotation_angle];
    double rad = deg * (M_PI / 180);
    uint16_t x_rev, y_rev;
    x_rev =  + mouse_report.x * cos(rad) + mouse_report.y * sin(rad);
    y_rev =  - mouse_report.x * sin(rad) + mouse_report.y * cos(rad);

    switch (get_highest_layer(layer_state | default_layer_state)) {
    case 1:
    case 2:
        is_scroll_mode = true;
        break;
    default:
        is_scroll_mode = false;
        break;
    }

    if (is_scroll_mode) {
        mouse_report.h = x_rev / scrl_div_array[keyboard_config.scrl_div];

        #ifdef COCOT_SCROLL_INVERT
                // Invert vertical scroll direction
                mouse_report.v = -y_rev / scrl_div_array[keyboard_config.scrl_div];
        #else
                mouse_report.v = y_rev / scrl_div_array[keyboard_config.scrl_div];
        #endif

        mouse_report.x = 0;
        mouse_report.y = 0;
    } else {
        mouse_report.x = x_rev;
        mouse_report.y = y_rev;
    }

    return pointing_device_task_user(mouse_report);
}



bool process_record_kb(uint16_t keycode, keyrecord_t* record) {
    // xprintf("KL: kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    
    if (!process_record_user(keycode, record)) return false;

    if (keycode == CPI_SW && record->event.pressed) {
        keyboard_config.cpi_idx = (keyboard_config.cpi_idx + 1) % CPI_OPTION_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
        pointing_device_set_cpi(cpi_array[keyboard_config.cpi_idx]);
    }

    if (keycode == SCRL_SW && record->event.pressed) {
        keyboard_config.scrl_div = (keyboard_config.scrl_div + 1) % SCRL_DIV_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
    }
    
    if (keycode == ANGL_SW && record->event.pressed) {
        keyboard_config.rotation_angle = (keyboard_config.rotation_angle + 1) % ANGLE_SIZE;
        eeconfig_update_kb(keyboard_config.raw);
    }
    

    if (keycode == SCRL_MO && record->event.pressed) {
        { is_scroll_mode ^= 1; }
        // pointing_device_set_cpi(is_scroll_mode ? cpi_array[keyboard_config.cpi_idx] * scrl_div_array[keyboard_config.scrl_div] : cpi_array[keyboard_config.cpi_idx]);
    }

    if (keycode == SCRL_TO) {
        { is_scroll_mode ^= 1; }
    }

    return true;
}


void eeconfig_init_kb(void) {
    keyboard_config.cpi_idx = COCOT_CPI_DEFAULT;
    keyboard_config.scrl_div = COCOT_SCROLL_DIV_DEFAULT;
    keyboard_config.rotation_angle = COCOT_ROTATION_DEFAULT;
    eeconfig_update_kb(keyboard_config.raw);
    eeconfig_init_user();
}


void matrix_init_kb(void) {
    // is safe to just read CPI setting since matrix init
    // comes before pointing device init.
    keyboard_config.raw = eeconfig_read_kb();
    if (keyboard_config.cpi_idx > CPI_OPTION_SIZE) {
        eeconfig_init_kb();
    }
    matrix_init_user();
}


// OLED utility
#ifdef OLED_ENABLE


oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}


static const char PROGMEM cocot_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
    0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
    0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4,
    0};

void render_logo(void) {
    oled_write_P(cocot_logo, false);
};

void oled_write_layer_state(void) {

    // oled_write_P(PSTR("L:"), false);
    // int cpi = pointing_device_get_cpi();
    int cpi = cpi_array[keyboard_config.cpi_idx];
    int scroll_div = scrl_div_array[keyboard_config.scrl_div];
    int angle = angle_array[keyboard_config.rotation_angle];
    char buf1[5];
    char buf2[2];
    char buf3[4];
    snprintf(buf1, 5, "%4d", cpi);
    snprintf(buf2, 2, "%1d", scroll_div);
    snprintf(buf3, 4, "%3d", angle);

    switch (get_highest_layer(layer_state | default_layer_state)) {
        case 0:
            oled_write_P(PSTR("Base "), false);
            break;
        case 1:
            oled_write_P(PSTR("Lower"), false);
            break;
        case 2:
            oled_write_P(PSTR("Raise"), false);
            break;
        case 3:
            oled_write_P(PSTR("Mouse"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
            break;
    }
    oled_write_P(PSTR(" / "), false);
    oled_write(buf1, false);
    oled_write_P(PSTR(" / "), false);
    oled_write(buf2, false);
    oled_write_P(PSTR(" /"), false);
    oled_write(buf3, false);
}

#endif

