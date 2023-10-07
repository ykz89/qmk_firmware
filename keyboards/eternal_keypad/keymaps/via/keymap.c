/* Copyright 2021 duckyb
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

enum layer_names {
    _BASE = 0,
    _ARROW,
    _FN,
    _ADJUST
};

enum custom_keycodes {
    KC_SPC1 = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Base Layer
   * ,------------------------------------.
   * |     |  Esc |  1|  2|  3|  4|  5|  6|
   * |	   |------+---+---+---+---+---+---|
   * |     |  Tab |  Q|  W|  E|  R|  T|  Y|
   * |----||------+---+---+---+---+---+---|
   * | F9 || LCtrl|  A|  S|  D|  F|  G|  H|
   * |----||------+---+---+---+---+---+---|
   * | F2 || Shift|  Z|  X|  C|  V|  B|  N|
   * |----||------------------------------|
   * | F3 || F13 |  F14 | K | Space/1 |Alt|
   * `----'`------------------------------'
   */
    [_BASE] = LAYOUT(
		        KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,
		        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y,
		KC_F9, KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H,
		KC_F2, KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N,
		KC_F3, KC_F13, KC_F14, KC_K, KC_SPC1, KC_LALT
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            case KC_SPC1:
                if(record->event.pressed) {
                    SEND_STRING("  1");
                }
                break;
        }
    return true;
};
