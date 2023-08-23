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

#define LWR_SPC MT(MOD_LSFT, KC_SPC)
#define RSE_BSPC LT(RAISE, KC_BSPC)
#define _L_ADJUST(KC) LT(ADJUST, KC)

enum combo_events {
  L_SHIFT_COMBO,    // LM2 and LM3 => TD_SFT
  R_SHIFT_COMBO,    // RM2 and RM3 => RD_SFT
  CAPS_LOCK_COMBO,  // LT3 and RT3 => activate Caps Lock.
  CAPS_WORD_COMBO,  // LT2 and RT2 => activate Caps Word.
  ESAPE_COMBO,      // LT3 and LT4 => Esc
  BACKSPACE_COMBO,  // RB1 and RB2 => Backspace
  BACKWORD_COMBO,   // RB1 and RB3 => Backspace
  DELETE_COMBO,     // RT3 and RT4 => Delete
  ENTER_COMBO,      // RB3 and RB4 => Enter
  L_MOUSE_COMBO,    // RB2 and RB3 => MBTN1
  R_MOUSE_COMBO,    // RM3 and RB3 => MBTN2
  M_MOUSE_COMBO,    // RM1 and RM1 => MBTN3
  DRGSCRL_COMBO,    // RB1 and RB2 => Dragscroll
  COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t d_v[] PROGMEM = {KC_C, KC_V, COMBO_END};
const uint16_t l_shift_combo[] PROGMEM = {KC_R, KC_S, COMBO_END};
const uint16_t r_shift_combo[] PROGMEM = {KC_E, KC_I, COMBO_END};
const uint16_t caps_lock_combo[] PROGMEM = {KC_W, KC_Y, COMBO_END};
const uint16_t caps_word_combo[] PROGMEM = {KC_F, KC_U, COMBO_END};
const uint16_t escape_combo[] PROGMEM = {KC_Q, KC_W, COMBO_END};
const uint16_t backspace_combo[] PROGMEM = {KC_H, KC_COMM, COMBO_END};
const uint16_t backword_combo[] PROGMEM = {KC_H, KC_DOT, COMBO_END};
const uint16_t delete_combo[] PROGMEM = {KC_Y, KC_UNDS, COMBO_END};
const uint16_t dquo_combo[] PROGMEM = {KC_U, KC_Y, COMBO_END};
const uint16_t enter_combo[] PROGMEM = {KC_DOT, KC_QUOT, COMBO_END};
const uint16_t l_mouse_combo[] PROGMEM = {KC_COMM, KC_DOT, COMBO_END};
const uint16_t r_mouse_combo[] PROGMEM = {KC_DOT, KC_I, COMBO_END};
const uint16_t m_mouse_combo[] PROGMEM = {KC_H, KC_N, COMBO_END};
const uint16_t drgscrl_combo[] PROGMEM = {KC_K, KC_H, COMBO_END};

combo_t key_combos[] = {
    COMBO(d_v, KC_CCCV),
    [L_SHIFT_COMBO] = COMBO(l_shift_combo, TD_SFT),
    [R_SHIFT_COMBO] = COMBO(r_shift_combo, RD_SFT),
    [CAPS_LOCK_COMBO] = COMBO(caps_lock_combo, KC_CAPS),
    [CAPS_WORD_COMBO] = COMBO(caps_word_combo, CW_TOGG),
    [ESCAPE_COMBO] = COMBO(escape_combo, KC_ESC),
    [V_COMBO] = COMBO(kc_v_combo, KC_V),
    [Q_COMBO] = COMBO(kc_q_combo, KC_Q),
    [Z_COMBO] = COMBO(kc_z_combo, KC_Z),
    [BACKSPACE_COMBO] = COMBO(backspace_combo, KC_BSPC),
    [BACKWORD_COMBO] = COMBO(backword_combo, C(KC_BSPC)),
    [DELETE_COMBO] = COMBO(delete_combo, KC_DEL),
    [DQUO_COMBO] = COMBO(dquo_combo, KC_DQUO),
    [ENTER_COMBO] = COMBO(enter_combo, KC_ENT),
    [L_MOUSE_COMBO] = COMBO(l_mouse_combo, KC_BTN1),
    [R_MOUSE_COMBO] = COMBO(r_mouse_combo, KC_BTN2),
    [M_MOUSE_COMBO] = COMBO(m_mouse_combo, KC_BTN3),
    [DRGSCRL_COMBO] = COMBO(drgscrl_combo, DRGSCRL),
};

// clang-format off
#define LAYOUT_BASE                                                                              \
       KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,     KC_Y,   KC_QUOT, \
       KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,     KC_I,      KC_O, \
       KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM,  KC_DOT, KC_SLSH, \
                    MO(LOWER), LWR_SPC, KC_TAB,  KC_ENT, RSE_BSPC,  MO(RAISE)

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
