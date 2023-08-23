/**
 * Copyright 2021 Charly Delay <charly@codesink.dev> (@0xcharly)
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

enum skeletyl_keymap_layers {
    BASE = 0,
    LOWER,
    RAISE,
    EXTEND,
    ADJUST,
};

enum custom_keycodes {
    KC_CCCV = SAFE_RANGE
};

#define SFT_SPC MT(MOD_LSFT, KC_SPC)
#define FUN_TAB LT(FUNCTION, KC_TAB)
#define _L_PTR(KC) LT(LAYER_POINTER, KC)

const uint16_t PROGMEM q_w[] = {KC_Q, KC_W, COMBO_END};
const uint16_t PROGMEM d_v[] = {KC_C, KC_V, COMBO_END};
combo_t key_combos[] = {
    COMBO(q_w, KC_ESC),
    COMBO(d_v, KC_CCCV), // keycodes with modifiers are possible too!
};

// clang-format off
#define LAYOUT_BASE                                                                              \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,     KC_Y,   KC_QUOT, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,     KC_I,      KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM,  KC_DOT, KC_SLSH, \
                MO(LOWER),  SFT_SPC, FUN_TAB LT,    KC_ENT,  KC_BSPC,  MO(RAISE)

/** Convenience row shorthands. */
#define _______________DEAD_HALF_ROW_______________ XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
#define ______________HOME_ROW_GACS_L______________ KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX
#define ______________HOME_ROW_GACS_R______________ XXXXXXX, KC_LSFT, KC_LCTL, KC_LALT, KC_LGUI
#define ____________OSM_HOME_ROW_GACS_L____________ OSM(MOD_LGUI), OSM(MOD_LALT), OSM(MOD_LCTL), OSM(MOD_LSFT), XXXXXXX
#define ____________OSM_HOME_ROW_GACS_R____________ XXXXXXX, OSM(MOD_LSFT), OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI)

#define LAYOUT_LOWER                                                                           \
    KC_MPRV, KC_VOLD, KC_MPLY, KC_VOLU, KC_MNXT,  XXXXXXX, KC_HOME,   KC_UP,  KC_END, KC_PGUP, \
    ____________OSM_HOME_ROW_GACS_L____________,  XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, \
    XXXXXXX, XXXXXXX, KC_MUTE, XXXXXXX, XXXXXXX,  XXXXXXX, KC_LPRN, KC_SCLN, KC_RPRN, XXXXXXX, \
                      _______, _______, _______,  _______,  _______, _______

#define LAYOUT_RAISE                                                                          \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, XXXXXXX,XXXXXXX,ALGR(KC_5),XXXXXXX, XXXXXXX, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ____________OSM_HOME_ROW_GACS_R____________, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_PIPE, KC_GRV,   KC_DOT, KC_UNDS, KC_MINS, XXXXXXX, \
                      _______, _______, _______, _______, _______, _______

#define LAYOUT_EXTEND                                                                         \
    KC_LPRN,    KC_7,    KC_8,    KC_9, KC_RPRN, KC_SCRL,   KC_F7,   KC_F8,   KC_F9,  KC_F10, \
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, KC_CAPS,   KC_F4,   KC_F5,   KC_F6,  KC_F11, \
       KC_0,    KC_1,    KC_2,    KC_3, KC_BSLS, _______,   KC_F1,   KC_F2,   KC_F3,  KC_F12, \
                      _______, _______, _______, _______, _______, _______

/** \brief Mouse emulation and pointer functions. */
#define LAYOUT_ADJUST                                                                       \
    _______________DEAD_HALF_ROW_______________, _______________DEAD_HALF_ROW_______________, \
    ____________OSM_HOME_ROW_GACS_L____________, ____________OSM_HOME_ROW_GACS_R____________, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
                      KC_BTN2, KC_BTN1, KC_BTN3, KC_BTN3, KC_BTN1, KC_BTN2

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_3(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE] = LAYOUT_wrapper(LAYOUT_BASE),
  [RAISE] = LAYOUT_wrapper(LAYOUT_RAISE),
  [LOWER] = LAYOUT_wrapper(LAYOUT_LOWER),
  [EXTEND] = LAYOUT_wrapper(LAYOUT_EXTEND),
  [ADJUST] = LAYOUT_wrapper(LAYOUT_ADJUST),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LOWER, RAISE, EXTEND);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_CCCV:  // One key copy/paste
            if (record->event.pressed) {
                copy_paste_timer = timer_read();
            } else {
                if (timer_elapsed(copy_paste_timer) > TAPPING_TERM) {  // Hold, copy
                    tap_code16(LCTL(KC_C));
                } else { // Tap, paste
                    tap_code16(LCTL(KC_V));
                }
            }
            break;
    }
    return true;
}

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in
// rgb_matrix.c.
void rgb_matrix_update_pwm_buffers(void);
#endif

void shutdown_user(void) {
#ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom();
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
    rgblight_setrgb_red();
#endif // RGBLIGHT_ENABLE
#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_set_color_all(RGB_RED);
    rgb_matrix_update_pwm_buffers();
#endif // RGB_MATRIX_ENABLE
}
