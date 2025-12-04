/**
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
 * Copyright 2023 casuanoob <casuanoob@hotmail.com> (@casuanoob)
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

#include QMK_KEYBOARD_H
#include "digitizer.h"
#include "host.h"

enum dilemma_keymap_layers {
    LAYER_BASE = 0,
    LAYER_FUNCTION,
    LAYER_NAVIGATION,
    LAYER_MEDIA,
    LAYER_POINTER,
    LAYER_NUMERAL,
    LAYER_SYMBOLS,
};


static uint8_t digitizer_button_state = 0;

// Automatically enable sniping-mode on the pointer layer.
// #define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_POINTER

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAVIGATION, KC_SPC)
#define TAB_FUN LT(LAYER_FUNCTION, KC_TAB)
#define ENT_SYM LT(LAYER_SYMBOLS, KC_ENT)
#define BSP_NUM LT(LAYER_NUMERAL, KC_BSPC)
#define PT_Z LT(LAYER_POINTER, KC_Z)
#define PT_SLSH LT(LAYER_POINTER, KC_SLSH)

#ifndef POINTING_DEVICE_ENABLE
#    define DRGSCRL KC_NO
#    define DPI_MOD KC_NO
#    define S_D_MOD KC_NO
#    define SNIPING KC_NO
#endif // !POINTING_DEVICE_ENABLE

// clang-format off
/** \brief QWERTY layout (3 rows, 10 columns). */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_split_3x5_3(
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
       LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G, KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O),
       PT_Z,    RALT_T(KC_X),    KC_C,    KC_D,    KC_V,    KC_K,    KC_H, KC_COMM,  RALT_T(KC_DOT), PT_SLSH,
                      ESC_MED, SPC_NAV, TAB_FUN, ENT_SYM, BSP_NUM, KC_DEL
  ),

/*
 * Layers used on the Dilemma.
 *
 * These layers started off heavily inspired by the Miryoku layout, but trimmed
 * down and tailored for a stock experience that is meant to be fundation for
 * further personalization.
 *
 * See https://github.com/manna-harbour/miryoku for the original layout.
 */

/**
 * \brief Function layer.
 *
 * Secondary right-hand layer has function keys mirroring the numerals on the
 * primary layer with extras on the pinkie column, plus system keys on the inner
 * column. App is on the tertiary thumb key and other thumb keys are duplicated
 * from the base layer to enable auto-repeat.
 */
  [LAYER_FUNCTION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR,   KC_F7,   KC_F8,   KC_F9,  KC_F12,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_SCRL,   KC_F4,   KC_F5,   KC_F6,  KC_F11,
    XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX, KC_PAUS,   KC_F1,   KC_F2,   KC_F3,  KC_F10,
                      XXXXXXX, XXXXXXX, _______, XXXXXXX, XXXXXXX, _______
  ),

/**
 * \brief Navigation layer.
 *
 * Primary right-hand layer (left home thumb) is navigation and editing. Cursor
 * keys are on the home position, line and page movement below, clipboard above,
 * caps lock and insert on the inner column. Thumb keys are duplicated from the
 * base layer to avoid having to layer change mid edit and to enable auto-repeat.
 */
  [LAYER_NAVIGATION] = LAYOUT_split_3x5_3(
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, CW_TOGG, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
    XXXXXXX, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX,  KC_INS, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,
                      XXXXXXX, _______, XXXXXXX,  KC_ENT, KC_BSPC, _______
  ),

/**
 * \brief Media layer.
 *
 * Tertiary left- and right-hand layer is media and RGB control.  This layer is
 * symmetrical to accomodate the left- and right-hand trackball.
 */
  [LAYER_MEDIA] = LAYOUT_split_3x5_3(
    XXXXXXX, RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX, XXXXXXX, RM_PREV, RM_TOGG, RM_NEXT, XXXXXXX,
    KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT, KC_MPRV, KC_VOLD, KC_MUTE, KC_VOLU, KC_MNXT,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                      _______, KC_MPLY, KC_MSTP, KC_MSTP, KC_MPLY, KC_MUTE
  ),

/** \brief Mouse emulation and pointer functions. */
  [LAYER_POINTER] = LAYOUT_split_3x5_3(
    QK_BOOT,  EE_CLR, XXXXXXX, DPI_MOD, S_D_MOD, S_D_MOD, DPI_MOD, XXXXXXX,  EE_CLR, QK_BOOT,
    KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    _______, DRGSCRL, SNIPING, MS_BTN3, XXXXXXX, XXXXXXX, MS_BTN3, SNIPING, DRGSCRL, _______,
                      MS_BTN3, MS_BTN2, MS_BTN1, MS_BTN1, MS_BTN2, MS_BTN3
  ),

/**
 * \brief Numeral layout.
 *
 * Primary left-hand layer (right home thumb) is numerals and symbols. Numerals
 * are in the standard numpad locations with symbols in the remaining positions.
 * `KC_DOT` is duplicated from the base layer.
 */
  [LAYER_NUMERAL] = LAYOUT_split_3x5_3(
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_GRAVE,   KC_1,    KC_2,    KC_3, KC_BSLS, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
                       KC_DOT,    KC_0, KC_MINS, XXXXXXX, _______, XXXXXXX
  ),

/**
 * \brief Symbols layer.
 *
 * Secondary left-hand layer has shifted symbols in the same locations to reduce
 * chording when using mods with shifted symbols. `KC_LPRN` is duplicated next to
 * `KC_RPRN`.
 */
  [LAYER_SYMBOLS] = LAYOUT_split_3x5_3(
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI,
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, KC_RALT, XXXXXXX,
                      KC_LPRN, KC_RPRN, KC_UNDS, _______, XXXXXXX, XXXXXXX
  ),
};
// clang-format on

#ifdef POINTING_DEVICE_ENABLE
#    ifdef DILEMMA_AUTO_SNIPING_ON_LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#    endif // DILEMMA_AUTO_SNIPING_ON_LAYER
#endif     // POINTING_DEVICE_ENABLE

#ifdef ENCODER_MAP_ENABLE
// clang-format off
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [LAYER_BASE]       = {ENCODER_CCW_CW(MS_WHLD, MS_WHLU),  ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
    [LAYER_FUNCTION]   = {ENCODER_CCW_CW(KC_DOWN, KC_UP),    ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
    [LAYER_NAVIGATION] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_MEDIA] = {ENCODER_CCW_CW(KC_PGDN, KC_PGUP),  ENCODER_CCW_CW(KC_VOLU, KC_VOLD)},
    [LAYER_POINTER]    = {ENCODER_CCW_CW(RM_HUED, RM_HUEU),  ENCODER_CCW_CW(RM_SATD, RM_SATU)},
    [LAYER_NUMERAL]    = {ENCODER_CCW_CW(RM_VALD, RM_VALU),  ENCODER_CCW_CW(RM_SPDD, RM_SPDU)},
    [LAYER_SYMBOLS]    = {ENCODER_CCW_CW(RM_PREV, RM_NEXT), ENCODER_CCW_CW(KC_LEFT, KC_RGHT)},
};
// clang-format on
#endif // ENCODER_MAP_ENABLE


#ifdef MACOS_TRACKPAD_MODE
#include "pointing_device.h"
#include "timer.h"

report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    mouse_report = pointing_device_task_user(mouse_report);

#if defined(DIGITIZER_ENABLE) && defined(DIGITIZER_FINGER_COUNT) && defined(DIGITIZER_CONTACT_COUNT)
    static uint32_t scan_time = 0;
    static int last_contacts = 0;
    static uint32_t inactivity_timer = 0;

    bool has_mouse_movement = (mouse_report.x != 0 || mouse_report.y != 0);

    digitizer_t digitizer_state = digitizer_get_state();
    bool has_buttons = (digitizer_state.button1 || digitizer_state.button2 || digitizer_state.button3);

    bool has_contacts = false;
    const int max_contacts = (DIGITIZER_FINGER_COUNT < DIGITIZER_CONTACT_COUNT) ? DIGITIZER_FINGER_COUNT : DIGITIZER_CONTACT_COUNT;
    for (int i = 0; i < max_contacts && i < DIGITIZER_CONTACT_COUNT; i++) {
        if (digitizer_state.contacts[i].type == FINGER && digitizer_state.contacts[i].tip) {
            has_contacts = true;
            break;
        }
    }

    if (!has_contacts && !has_buttons && !has_mouse_movement) {
        inactivity_timer = timer_read32();
        last_contacts = 0;
        scan_time = 0; // Reset scan_time on inactivity so it's recalculated when activity resumes
        return mouse_report;
    }

    // Digitizer report with button state from physical keys mapped to mouse buttons
    // macOS uses the Digitizer interface for trackpad pointing, so it expects button presses
    // to come from the same interface. We send buttons to BOTH interfaces:
    // - Mouse interface: For Linux/other OSes that use the Mouse interface
    // - Digitizer interface: For macOS which uses the Digitizer interface
    // Note: Only keys mapped to QK_MOUSE_BUTTON_1/2/3 are sent as digitizer buttons.
    // Other keys (KC_MUTE, DPI_INC, etc.) are sent through the keyboard HID interface.
    // Finger tap gestures are handled separately by the core digitizer gesture system.
    report_digitizer_t digitizer_report = {
        .report_id = REPORT_ID_DIGITIZER,
        .scan_time = 0,
        .contact_count = 0,
        // .button1 = digitizer_state.button1, // Key mapped to QK_MOUSE_BUTTON_1 (left click)
        // .button2 = digitizer_state.button2, // Key mapped to QK_MOUSE_BUTTON_2 (right click)
        // .button3 = digitizer_state.button3, // Key mapped to QK_MOUSE_BUTTON_3 (middle click)
        .reserved2 = 0
    };

    int contacts = 0;

    if (has_contacts) {
        for (int i = 0; i < max_contacts && i < DIGITIZER_CONTACT_COUNT; i++) {
            if (digitizer_state.contacts[i].type == FINGER && digitizer_state.contacts[i].tip) {
                contacts++;

                if (digitizer_report.contact_count < DIGITIZER_FINGER_COUNT) {
                    digitizer_report.fingers[digitizer_report.contact_count] = (digitizer_finger_report_t){
                        .confidence = digitizer_state.contacts[i].confidence,
                        .tip = 1,
                        .reserved = 0,
                        .contact_id = i,
                        .reserved2 = 0,
                        .x = digitizer_state.contacts[i].x,
                        .y = digitizer_state.contacts[i].y
                    };
                    digitizer_report.contact_count++;
                }
            }
        }
    }

    // Initialize or reset scan_time when contacts first appear after inactivity
    if (scan_time == 0 && contacts > 0) {
        scan_time = timer_read32();
    } else if (last_contacts == 0 && contacts > 0 && timer_elapsed32(inactivity_timer) > DIGITIZER_INACTIVITY_TIMEOUT_MS) {
        scan_time = timer_read32();
    }
    inactivity_timer = timer_read32();
    last_contacts = contacts;

    // Calculate scan_time in 100us ticks (Microsoft PTP requirement)
    if (scan_time != 0) {
        uint32_t scan = timer_elapsed32(scan_time);
        digitizer_report.scan_time = scan * DIGITIZER_SCAN_TIME_MULTIPLIER;
    }

    host_digitizer_send(&digitizer_report);
#endif

    return mouse_report;
}
#endif

void pointing_device_keycode_handler(uint16_t keycode, bool pressed) {
    if (IS_MOUSEKEY_BUTTON(keycode)) {
        uint8_t button_idx = keycode - QK_MOUSE_BUTTON_1;

        // Limit to buttons 1-3 (digitizer supports up to 3 buttons)
        if (button_idx > 2) {
            return;
        }

        uint8_t button_mask = 1 << button_idx;

        if (pressed) {
            digitizer_button_state |= button_mask;
        } else {
            digitizer_button_state &= ~button_mask;
        }

        // Send buttons to both interfaces for cross-platform compatibility:
        // - Digitizer interface: macOS expects buttons from the same interface it uses for pointing
        // - Mouse interface: Linux/other OSes use the Mouse interface for both pointing and buttons
#if defined(DIGITIZER_ENABLE)
        report_digitizer_t digitizer_report = {
            .report_id = REPORT_ID_DIGITIZER,
            .fingers = {},
            .scan_time = 0,
            .contact_count = 0,
            // .button1 = (digitizer_button_state & 0x01) ? 1 : 0,
            // .button2 = (digitizer_button_state & 0x02) ? 1 : 0,
            // .button3 = (digitizer_button_state & 0x04) ? 1 : 0,
            .reserved2 = 0
        };
        host_digitizer_send(&digitizer_report);
#endif

        report_mouse_t mouse_report = pointing_device_get_report();
        mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, pressed, button_idx);
        pointing_device_set_report(mouse_report);
        pointing_device_send();
    }
}

// bool digitizer_task_kb(digitizer_t *digitizer_state) {
//     // Update digitizer button state from physical button state tracked in keycode handler
//     // digitizer_state->button1 = (digitizer_button_state & 0x01) ? 1 : 0;
//     // digitizer_state->button2 = (digitizer_button_state & 0x02) ? 1 : 0;
//     // digitizer_state->button3 = (digitizer_button_state & 0x04) ? 1 : 0;

//     return digitizer_task_user(digitizer_state);
// }
