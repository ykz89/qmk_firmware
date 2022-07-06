/**
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
 * Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
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

#ifdef OLED_ENABLE
#    include "oled_driver.h"
#endif // OLED_ENABLE

enum bstiq_layers {
    LAYER_BASE = 0,
    LAYER_MBO,
    LAYER_MEDIA,
    LAYER_NAV,
    LAYER_MOUSE,
    LAYER_SYM,
    LAYER_NUM,
    LAYER_FUN,
};

// Automatically enable sniping when the mouse layer is on.
#define DILEMMA_AUTO_SNIPING_ON_LAYER LAYER_MOUSE

#define BSP_NAV LT(LAYER_NAV, KC_BSPC)
#define ENT_MBO LT(LAYER_MBO, KC_ENT)
#define TAB_MED LT(LAYER_MEDIA, KC_TAB)
#define ESC_SYM LT(LAYER_SYM, KC_ESC)
#define SPC_NUM LT(LAYER_NUM, KC_SPC)
#define SPC_MBO LT(LAYER_MBO, KC_SPC)
#define MOUSE(KC) LT(LAYER_MOUSE, KC)

#define ESC_MED LT(LAYER_MEDIA, KC_ESC)
#define SPC_NAV LT(LAYER_NAV, KC_SPC)
#define TAB_FUN LT(LAYER_FUN, KC_TAB)
#define ENT_SYM LT(LAYER_SYM, KC_ENT)
#define BSP_NUM LT(LAYER_NUM, KC_BSPC)
#define DEL_PNT LT(LAYER_MBO, KC_DEL)
#define MOUSE(KC) LT(LAYER_MOUSE, KC)

#define USR_RDO KC_AGAIN
#define USR_PST S(KC_INS)
#define USR_CPY C(KC_INS)
#define USR_CUT S(KC_DEL)
#define USR_UND KC_UNDO

#define MS_L KC_MS_LEFT
#define MS_R KC_MS_RIGHT
#define MS_D KC_MS_DOWN
#define MS_U KC_MS_UP

#define WH_L KC_MS_WH_LEFT
#define WH_R KC_MS_WH_RIGHT
#define WH_D KC_MS_WH_DOWN
#define WH_U KC_MS_WH_UP

const uint16_t PROGMEM thumbcombos_del[] = {ENT_SYM, BSP_NUM, COMBO_END};
const uint16_t PROGMEM thumbcombos_esc[] = {SPC_NAV, TAB_FUN, COMBO_END};

combo_t key_combos[COMBO_COUNT] = {
  COMBO(thumbcombos_del, KC_DEL),
  COMBO(thumbcombos_esc, KC_ESC)
};

// clang-format off
/** Convenience macro. */
#define _KC_LAYOUT_wrapper(                                                                             \
         k00,      k01,      k02,      k03,      k04,      k05,      k06,      k07,      k08,      k09, \
         k10,      k11,      k12,      k13,      k14,      k15,      k16,      k17,      k18,      k19, \
         k20,      k21,      k22,      k23,      k24,      k25,      k26,      k27,      k28,      k29, \
         ...)                                                                                           \
    KC_##k00, KC_##k01, KC_##k02, KC_##k03, KC_##k04, KC_##k05, KC_##k06, KC_##k07, KC_##k08, KC_##k09, \
    KC_##k10, KC_##k11, KC_##k12, KC_##k13, KC_##k14, KC_##k15, KC_##k16, KC_##k17, KC_##k18, KC_##k19, \
    KC_##k20, KC_##k21, KC_##k22, KC_##k23, KC_##k24, KC_##k25, KC_##k26, KC_##k27, KC_##k28, KC_##k29, \
    __VA_ARGS__
#define KC_LAYOUT_wrapper(...) _KC_LAYOUT_wrapper(__VA_ARGS__)

/** Base layer with COLEMAK layout. */
#define LAYOUT_LAYER_BASE_COLEMAK KC_LAYOUT_wrapper(               \
       Q,    W,    F,    P,    B,    J,    L,    U,    Y, QUOT, \
       A,    R,    S,    T,    G,    M,    N,    E,    I,    O, \
       Z,    X,    C,    D,    V,    K,    H, COMM,  DOT, SLSH, \
                SPC_NAV, TAB_FUN,    ENT_SYM, BSP_NUM)

/** Convenience key shorthands. */
#define U_NA KC_NO // Present but not available for use.
#define U_NU KC_NO // Available but not used.

/** Convenience row shorthands. */
#define ________________HOME_ROW_NA________________    U_NA,    U_NA,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_L______________ KC_LGUI, KC_LALT, KC_LSFT, KC_LCTL,    U_NA
#define ______________HOME_ROW_ALGR_L______________    U_NA, KC_ALGR,    U_NA,    U_NA,    U_NA
#define ______________HOME_ROW_GASC_R______________    U_NA, KC_LCTL, KC_LSFT, KC_LALT, KC_LGUI
#define ______________HOME_ROW_ALGR_R______________    U_NA,    U_NA,    U_NA, KC_ALGR,    U_NA

/** Layers. */

// Buttons.
#define LAYOUT_LAYER_MBO                                                                      \
    ________________HOME_ROW_NA________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________, KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1,    U_NA,  KC_DEL, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                                  U_NA,    U_NA,  KC_ENT,  KC_ENT

// Media.
#define LAYOUT_LAYER_MEDIA                                                                    \
    ________________HOME_ROW_NA________________, RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, \
    ______________HOME_ROW_GASC_L______________,    U_NU, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, \
    ______________HOME_ROW_ALGR_L______________,    U_NU,    U_NU,    U_NU,    U_NU,    U_NU, \
                                  U_NA,    U_NA, KC_MSTP, KC_MPLY

// Navigation.
#define LAYOUT_LAYER_NAV                                                                      \
    ________________HOME_ROW_NA________________, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    ______________HOME_ROW_GASC_L______________, KC_BSPC, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, \
    KC_BTN3, KC_ALGR, KC_BTN2, KC_BTN1,    U_NA,  KC_DEL, KC_HOME, KC_PGDN, KC_PGUP,  KC_END, \
                                  U_NA,    U_NA,  KC_ENT,  KC_ENT
// Mouse.
#define LAYOUT_LAYER_MOUSE                                                                    \
    S_D_MOD, USR_PST, USR_CPY, USR_CUT, USR_UND, USR_RDO, USR_PST, USR_CPY, USR_CUT, USR_UND, \
    DPI_MOD, DRGSCRL, KC_LSFT, DRGSCRL, _______,    U_NU,    MS_L,    MS_D,    MS_U,    MS_R, \
    USR_RDO, USR_PST, USR_CPY, KC_BTN3, USR_UND,    U_NU,    WH_L,    WH_D,    WH_U,    WH_R, \
                               KC_BTN1, KC_BTN2, KC_BTN1, KC_BTN3

// Symbols.
#define LAYOUT_LAYER_SYM                                                                      \
    KC_LCBR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RCBR, ________________HOME_ROW_NA________________, \
    KC_COLN,  KC_DLR, KC_PERC, KC_CIRC, KC_PLUS, ______________HOME_ROW_GASC_R______________, \
    KC_TILD, KC_EXLM,   KC_AT, KC_HASH, KC_MINS, ______________HOME_ROW_ALGR_R______________, \
                               KC_RPRN, KC_LPRN,    U_NA,    U_NA

// Numerals.
#define LAYOUT_LAYER_NUM                                                                      \
    KC_LBRC,    KC_7,    KC_8,    KC_9, KC_RBRC, ________________HOME_ROW_NA________________, \
    KC_SCLN,    KC_4,    KC_5,    KC_6,  KC_EQL, ______________HOME_ROW_GASC_R______________, \
     KC_GRV,    KC_1,    KC_2,    KC_3, KC_UNDS, ______________HOME_ROW_ALGR_R______________, \
                                  KC_0, KC_MINS,    U_NA,    U_NA

// Function keys.
#define LAYOUT_LAYER_FUN                                                                      \
     KC_F12,   KC_F7,   KC_F8,   KC_F9, KC_PSCR, ________________HOME_ROW_NA________________, \
     KC_F11,   KC_F4,   KC_F5,   KC_F6, KC_SLCK, ______________HOME_ROW_GASC_R______________, \
     KC_F10,   KC_F1,   KC_F2,   KC_F3, KC_PAUS, ______________HOME_ROW_ALGR_R______________,\
                                KC_APP,  KC_TAB,    U_NA,    U_NA

/**
 * Add Home Row mod to a layout.
 *
 * Expects a 10-key per row layout.  Adds support for GACS (Gui, Alt, Ctl, Shift)
 * home row.  The layout passed in parameter must contain at least 20 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_COLEMAK` defined above, eg.:
 *
 *     HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE_COLEMAK)
 */
#define _HOME_ROW_MOD_GACS(                                            \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,                  \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,                  \
    ...)                                                               \
             L00,         L01,         L02,         L03,         L04,  \
             R05,         R06,         R07,         R08,         R09,  \
      LGUI_T(L10), LALT_T(L11), LCTL_T(L12), LSFT_T(L13),        L14,  \
             R15,  RSFT_T(R16), RCTL_T(R17), LALT_T(R18), RGUI_T(R19), \
      __VA_ARGS__
#define HOME_ROW_MOD_GACS(...) _HOME_ROW_MOD_GACS(__VA_ARGS__)

/**
 * Add mouse layer keys to a layout.
 *
 * Expects a 10-key per row layout.  The layout passed in parameter must contain
 * at least 30 keycodes.
 *
 * This is meant to be used with `LAYOUT_LAYER_BASE_COLEMAK` defined above, eg.:
 *
 *     MOUSE_MOD(LAYOUT_LAYER_BASE_COLEMAK)
 */
#define _MOUSE_MOD(                                               \
    L00, L01, L02, L03, L04, R05, R06, R07, R08, R09,             \
    L10, L11, L12, L13, L14, R15, R16, R17, R18, R19,             \
    L20, L21, L22, L23, L24, R25, R26, R27, R28, R29,             \
    ...)                                                          \
            L00,        L01,        L02,        L03,        L04,  \
            R05,        R06,        R07,        R08,        R09,  \
            L10,        L11,        L12,        L13,        L14,  \
            R15,        R16,        R17,        R18,        R19,  \
            L20, MOUSE(L21),        L22,        L23,        L24,  \
            R25,        R26,        R27,        R28,  MOUSE(R29), \
      __VA_ARGS__
#define MOUSE_MOD(...) _MOUSE_MOD(__VA_ARGS__)

#define LAYOUT_wrapper(...) LAYOUT_split_3x5_2(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [LAYER_BASE] = LAYOUT_wrapper(
    MOUSE_MOD(HOME_ROW_MOD_GACS(LAYOUT_LAYER_BASE_COLEMAK))
  ),
  [LAYER_MBO] = LAYOUT_wrapper(LAYOUT_LAYER_MBO),
  [LAYER_MEDIA] = LAYOUT_wrapper(LAYOUT_LAYER_MEDIA),
  [LAYER_NAV] = LAYOUT_wrapper(LAYOUT_LAYER_NAV),
  [LAYER_MOUSE] = LAYOUT_wrapper(LAYOUT_LAYER_MOUSE),
  [LAYER_SYM] = LAYOUT_wrapper(LAYOUT_LAYER_SYM),
  [LAYER_NUM] = LAYOUT_wrapper(LAYOUT_LAYER_NUM),
  [LAYER_FUN] = LAYOUT_wrapper(LAYOUT_LAYER_FUN),
};
// clang-format on

#if defined(POINTING_DEVICE_ENABLE) && defined(DILEMMA_AUTO_SNIPING_ON_LAYER)
layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    dilemma_set_pointer_sniping_enabled(layer_state_cmp(state, DILEMMA_AUTO_SNIPING_ON_LAYER));
    return state;
}
#endif // POINTING_DEVICE_ENABLE && DILEMMA_AUTO_SNIPING_ON_LAYER

#ifdef RGB_MATRIX_ENABLE
// Forward-declare this helper function since it is defined in rgb_matrix.c.
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

#ifdef OLED_ENABLE
static uint16_t splash_screen_timer;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    splash_screen_timer = timer_read();
    return rotation;
}

static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        // Bastard Keyboards, 128x32px
        0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0x3c, 0x1c, 0x1e, 0x1e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 0x1e, 0x1c, 0x3c, 0x3c, 0x78, 0xf0, 0xe0, 0xe0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0x98, 0xf8, 0x70, 0x00, 0x00, 0xf0, 0xf8, 0xf8, 0xe0, 0x00, 0x00, 0xf0, 0xf8, 0x98, 0xb8, 0x30, 0x00, 0x18, 0xf8, 0xf8, 0x18, 0x18, 0x00, 0xf0, 0xf8, 0xf8, 0xe0, 0x00, 0x00, 0x60, 0xf0, 0x98, 0x98, 0xf8, 0xf8, 0x00, 0xf8, 0xf8, 0x18, 0xf8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0xf0, 0xfe, 0xff, 0x3f, 0x07, 0xff, 0xff, 0xff, 0x60, 0x70, 0x70, 0x70, 0xe0, 0xc0, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 0xe0, 0xf0, 0x30, 0x10, 0x03, 0x07, 0xff, 0xff, 0xfc, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x09, 0x0f, 0x0f, 0x00, 0x0e, 0x0f, 0x06, 0x07, 0x0f, 0x0c, 0x00, 0x0c, 0x0c, 0x09, 0x0f, 0x0f, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x0e, 0x0f, 0x06, 0x07, 0x0f, 0x0c, 0x00, 0x0e, 0x0f, 0x01, 0x01, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x08, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x0f, 0x7f, 0xff, 0xfc, 0xe0, 0x83, 0x0f, 0x1f, 0x18, 0x38, 0x38, 0x18, 0x1f, 0x0f, 0x07, 0x00, 0x00, 0x3f, 0x3f, 0x3f, 0x03, 0x07, 0x3f, 0xfe, 0xf0, 0xc0, 0xf0, 0xff, 0xff, 0x3f, 0x03, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xf8, 0xe0, 0xf8, 0x18, 0x00, 0xf8, 0xf8, 0xc8, 0xc8, 0xc8, 0x00, 0x08, 0x38, 0xf0, 0xe0, 0x78, 0x08, 0x00, 0xf8, 0xf8, 0xc8, 0xf8, 0xf8, 0x00, 0xf0, 0xf8, 0x18, 0x0c, 0xf8, 0xf8, 0x00, 0x80, 0xf8, 0x38, 0xf8, 0xe0, 0x00, 0x00, 0xf8, 0xf8, 0xc8, 0xf8, 0xf8, 0x00, 0xf8, 0xf8, 0x08, 0x08, 0xf8, 0xf8, 0x00, 0x78, 0xf8, 0xcc, 0xd8, 0x98, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x07, 0x0f, 0x1f, 0x1e, 0x3c, 0x3c, 0x38, 0x78, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x70, 0x78, 0x38, 0x3c, 0x1c, 0x1e, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x07, 0x0f, 0x08, 0x0f, 0x0f, 0x0c, 0x0c, 0x0c, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x00, 0x00, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x07, 0x03, 0x03, 0x07, 0x0c, 0x0c, 0x0f, 0x07, 0x00, 0x0f, 0x07, 0x03, 0x03, 0x0f, 0x0c, 0x00, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x00, 0x0f, 0x0f, 0x0c, 0x0c, 0x07, 0x07, 0x00, 0x06, 0x0e, 0x0c, 0x0f, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

bool oled_task_user(void) {
    render_logo();
    return false;
}
#endif
