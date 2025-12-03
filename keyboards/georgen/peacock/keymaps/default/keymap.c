// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "digitizer.h"
#include "host.h"

enum peacock_keycodes {
    LMB_TOGGLE = QK_USER_0,
    DPI_INC,
    DPI_DEC
};

// Track button state for digitizer interface
static uint8_t digitizer_button_state = 0;

const uint16_t PROGMEM etch_a_sketch_combo[] = { KC_LGUI, KC_ENTER, COMBO_END };
combo_t key_combos[] = {
    COMBO(etch_a_sketch_combo, TG(2))
};

#ifdef PEACOCK_ENCODER_BODGE
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(QK_MOUSE_BUTTON_1, QK_MOUSE_BUTTON_2, LT(1, QK_MOUSE_BUTTON_3), DPI_INC, DPI_DEC),
                                                              [1] = LAYOUT(QK_BOOT, QK_RGB_MATRIX_MODE_NEXT, KC_TRNS, QK_RGB_MATRIX_MODE_PREVIOUS, EE_CLR),
                                                              [2] = LAYOUT(LMB_TOGGLE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};
#else
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {[0] = LAYOUT(KC_MUTE, QK_MOUSE_BUTTON_1, QK_MOUSE_BUTTON_2, LT(1, QK_MOUSE_BUTTON_3), DPI_INC, DPI_DEC, C(KC_C)),
                                                              [1] = LAYOUT(KC_TRNS, QK_BOOT, QK_RGB_MATRIX_MODE_NEXT, KC_TRNS, QK_RGB_MATRIX_MODE_PREVIOUS, EE_CLR, KC_TRNS),
                                                              [2] = LAYOUT(KC_TRNS, LMB_TOGGLE, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
                                                              [3] = LAYOUT(KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)};
#endif

const uint8_t INDICATOR_LED = 5;

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU),  ENCODER_CCW_CW(KC_UP, KC_DOWN)  },
    [1] = { ENCODER_CCW_CW(QK_RGB_MATRIX_HUE_DOWN, QK_RGB_MATRIX_HUE_UP),   ENCODER_CCW_CW(QK_RGB_MATRIX_SATURATION_DOWN, QK_RGB_MATRIX_SATURATION_UP)  },
    [2] = { ENCODER_CCW_CW(QK_MOUSE_CURSOR_LEFT, QK_MOUSE_CURSOR_RIGHT),   ENCODER_CCW_CW(QK_MOUSE_CURSOR_UP, QK_MOUSE_CURSOR_DOWN)  },
    [3] = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS),  ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    switch(get_highest_layer(layer_state|default_layer_state)) {
        case 3:
            rgb_matrix_set_color(INDICATOR_LED, RGB_BLUE);
            break;
        case 2:
            rgb_matrix_set_color(INDICATOR_LED, RGB_RED);
            break;
        case 1:
            rgb_matrix_set_color(INDICATOR_LED, RGB_GREEN);
            break;
        default:
            rgb_matrix_set_color(INDICATOR_LED, RGB_OFF);
            break;
    }
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // If we are etch-a-sketching. Ensure the mouse button is released.
    mousekey_clear();
    return state;
}

bool shutdown_kb(bool jump_to_bootloader) {
    if (!shutdown_user(jump_to_bootloader)) {
        return false;
    }
    void rgb_matrix_update_pwm_buffers(void);
    if (jump_to_bootloader) {
        rgb_matrix_set_color_all(RGB_RED);
    }
    else {
        rgb_matrix_set_color_all(RGB_OFF);
    }
    rgb_matrix_update_pwm_buffers();
    return true;
}

#ifdef MACOS_TRACKPAD_MODE
#include "pointing_device.h"
#include "timer.h"
// Override pointing_device_task_kb to send digitizer reports for macOS
// This ensures digitizer reports are sent even when digitizer_send_mouse_reports is true
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    // Call default behavior first
    mouse_report = pointing_device_task_user(mouse_report);
    
    // Also send digitizer report so macOS can use Digitizer interface
    digitizer_t digitizer_state = digitizer_get_state();
    report_digitizer_t digitizer_report = {
        .report_id = REPORT_ID_DIGITIZER,
        .scan_time = 0,
        .contact_count = 0,
        .button1 = digitizer_state.button1,
        .button2 = digitizer_state.button2,
        .button3 = digitizer_state.button3,
        .reserved2 = 0
    };
    
    // Track scan_time for digitizer reports
    static uint32_t scan_time = 0;
    static int last_contacts = 0;
    static uint32_t inactivity_timer = 0;
    int contacts = 0;
    
    // Count active contacts and build finger reports
    for (int i = 0; i < DIGITIZER_FINGER_COUNT && i < DIGITIZER_CONTACT_COUNT; i++) {
        if (digitizer_state.contacts[i].type == FINGER) {
            bool finger_active = digitizer_state.contacts[i].tip;
            if (finger_active) {
                contacts++;
            }
            
            // Include all fingers (active and lifted) in report
            digitizer_report.fingers[digitizer_report.contact_count] = (digitizer_finger_report_t){
                .confidence = digitizer_state.contacts[i].confidence,
                .tip = finger_active ? 1 : 0,
                .reserved = 0,
                .contact_id = i,
                .reserved2 = 0,
                .x = digitizer_state.contacts[i].x,
                .y = digitizer_state.contacts[i].y
            };
            if (finger_active) {
                digitizer_report.contact_count++;
            }
        }
    }
    
    // Reset scan_time after inactivity
    if (last_contacts == 0 && contacts > 0 && timer_elapsed32(inactivity_timer) > 1000) {
        scan_time = timer_read32();
    }
    inactivity_timer = timer_read32();
    last_contacts = contacts;
    
    // Microsoft requires scan_time in 100us ticks
    if (scan_time > 0) {
        uint32_t scan = timer_elapsed32(scan_time);
        digitizer_report.scan_time = scan * 10;
    }
    
    // Send digitizer report whenever there's any activity
    if (digitizer_report.contact_count > 0 || digitizer_report.button1 || 
        digitizer_report.button2 || digitizer_report.button3 ||
        mouse_report.x != 0 || mouse_report.y != 0) {
        host_digitizer_send(&digitizer_report);
    }
    
    return mouse_report;
}
#endif

// Override pointing_device_keycode_handler to also update digitizer buttons
// This ensures buttons work on macOS which uses the Digitizer interface
void pointing_device_keycode_handler(uint16_t keycode, bool pressed) {
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        uint8_t button_idx = keycode - QK_MOUSE_BUTTON_1;
        uint8_t button_mask = 1 << button_idx;
        
        // Update digitizer button state
        if (pressed) {
            digitizer_button_state |= button_mask;
        } else {
            digitizer_button_state &= ~button_mask;
        }
        
        // Send digitizer report immediately for macOS compatibility
        report_digitizer_t digitizer_report = {
            .report_id = REPORT_ID_DIGITIZER,
            .fingers = {},
            .scan_time = 0,
            .contact_count = 0,
            .button1 = (digitizer_button_state & 0x01) ? 1 : 0,
            .button2 = (digitizer_button_state & 0x02) ? 1 : 0,
            .button3 = (digitizer_button_state & 0x04) ? 1 : 0,
            .reserved2 = 0
        };
        host_digitizer_send(&digitizer_report);
        
        // Update mouse report (default behavior for Linux/other systems)
        report_mouse_t mouse_report = pointing_device_get_report();
        mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, pressed, button_idx);
        pointing_device_set_report(mouse_report);
        pointing_device_send();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t* record) {
    switch (keycode) {
        case LMB_TOGGLE:
        {
            static bool lmb_held = false;
            if (record->event.pressed) {
                lmb_held = !lmb_held;
            }
            if (lmb_held) {
                mousekey_on(QK_MOUSE_BUTTON_1);
            }
            else {
                mousekey_off(QK_MOUSE_BUTTON_1);
            }
            break;
        }
        case DPI_INC:
        {
            uint16_t dpi = pointing_device_get_cpi();
            dpi += 100;
            if (dpi > 1200) dpi=100;
            pointing_device_set_cpi(dpi);
            break;
        }
        case DPI_DEC:
        {
            uint16_t dpi = pointing_device_get_cpi();
            dpi -= 100;
            if (dpi < 100) dpi=1200;
            pointing_device_set_cpi(dpi);
            break;
        }
    }
    return true;
}

// Override digitizer_task_kb to include button state from physical buttons
bool digitizer_task_kb(digitizer_t *digitizer_state) {
    // Update digitizer buttons from physical button state
    digitizer_state->button1 = (digitizer_button_state & 0x01) ? 1 : 0;
    digitizer_state->button2 = (digitizer_button_state & 0x02) ? 1 : 0;
    digitizer_state->button3 = (digitizer_button_state & 0x04) ? 1 : 0;
    
    return digitizer_task_user(digitizer_state);
}
