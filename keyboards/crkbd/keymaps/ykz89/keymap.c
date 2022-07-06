// Copyright 2022 @ykz89
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
    _COLEMAK,
    _NAV,
    _MOUSE,
    _MEDIA,
    _NUM,
    _FUN,
    _SYM,
};

// Custom keycodes for layer keys
// Dual function escape with left command
#define NAV LT(_NAV, KC_SPC)
#define MOUSE LT(_MOUSE, KC_TAB)
#define MEDIA LT(_MEDIA, KC_ESC)
#define NUM LT(_NUM, KC_BSPC)
#define FUN LT(_FUN, KC_DEL)
#define SYM LT(_SYM, KC_ENT)

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //,-----------------------------------------.                                   ,---------------------------------------------.
     KC_TAB,  KC_Q,  KC_W,  KC_F,  KC_P,  KC_B,                                     KC_J,  KC_L,  KC_U,  KC_Y,  KC_QUOT, KC_MINS,
  //|------+------+------+------+------+------|                                   |------+------+-------+------+-------+--------|
    KC_LSFT,  LGUI_T(KC_A),  LALT_T(KC_R),  LCTL_T(KC_S),  LSFT_T(KC_T),  KC_G,     KC_M, LSFT_T(KC_N), LCTL_T(KC_E), LALT_T(KC_I), LGUI_T(KC_O), KC_SCLN,
  //|------+------+------+------+------+------|                                   |------+------+-------+------+-------+--------|
    KC_LCTRL,  KC_Z,  ALGR_T(KC_X),  KC_C,  KC_D,  KC_V,                            KC_K , KC_H, KC_COMM, ALGR_T(KC_DOT), KC_SLSH, KC_RSHIFT,
  //|------+------+------+------+------+------+------|                            |------+------+------+-------+------+-------+--------|
                               MEDIA,NAV, MOUSE,                                    SYM  , NUM  , FUN
                              //`--------------------'                            `--------------------'
  ),

  [_NAV] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,      U_RDO   , U_PST   , U_CPY   , U_CUT   , U_UND   , XXXXXXX ,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT,XXXXXXX,          KC_CAPS , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , XXXXXXX ,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, XXXXXXX,KC_ALGR,XXXXXXX,XXXXXXX,XXXXXXX,                KC_INS  , KC_HOME , KC_PGDN , KC_PGUP , KC_END  , XXXXXXX,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    XXXXXXX, XXXXXXX,XXXXXXX,   KC_ENT, KC_BSPC,KC_DEL
                                  //`--------------------'  `--------------------'
  ),

  [_MOUSE] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,      U_RDO   , U_PST   , U_CPY   , U_CUT   , U_UND   , XXXXXXX ,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT,XXXXXXX,          XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , XXXXXXX ,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, XXXXXXX,KC_ALGR,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    XXXXXXX, XXXXXXX,XXXXXXX,   KC_BTN1, KC_BTN3,KC_BTN2
                                  //`--------------------'  `--------------------'
  ),

  [_MEDIA] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,      RGB_TOG , RGB_MOD , RGB_HUI , RGB_SAI , RGB_VAI , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT,XXXXXXX,          XXXXXXX , KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, XXXXXXX,KC_ALGR,XXXXXXX,XXXXXXX,XXXXXXX,                XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    XXXXXXX, XXXXXXX,XXXXXXX,  KC_MSTP , KC_MPLY , KC_MUTE
                                  //`--------------------'  `--------------------'
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     XXXXXXX , KC_LBRC , KC_7    , KC_8    , KC_9    , KC_RBRC,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_SCLN , KC_4    , KC_5    , KC_6    , KC_EQL ,        XXXXXXX , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_GRV  , KC_1    , KC_2    , KC_3    , KC_BSLS,        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_DOT  , KC_0    , KC_MINS,   XXXXXXX , XXXXXXX , XXXXXXX
                                  //`--------------------'  `--------------------'
  ),

  [_SYM] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     XXXXXXX , KC_LCBR , KC_AMPR , KC_ASTR , KC_LPRN , KC_RCBR,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_COLN , KC_DLR  , KC_PERC , KC_CIRC , KC_PLUS ,        XXXXXXX , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_PIPE,        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_LPRN , KC_RPRN , KC_UNDS,   XXXXXXX , XXXXXXX , XXXXXXX
                                  //`--------------------'  `--------------------'
  ),

  [_FUN] = LAYOUT_split_3x6_3(
  //,---------------------------------------------.                ,-----------------------------------------.
     XXXXXXX , KC_F12  , KC_F7   , KC_F8   , KC_F9   , KC_PSCR ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_SLCK ,        XXXXXXX , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , XXXXXXX,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
    XXXXXXX, KC_F10  , KC_F1   , KC_F2   , KC_F3   , KC_PAUS,        XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                    KC_APP  , KC_SPC  , KC_TAB,   XXXXXXX , XXXXXXX , XXXXXXX
                                  //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_layer_state(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _COLEMAK:
            oled_write_ln_P(PSTR("Base \n"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("Nav  \n"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse\n"), false);
            break;
        case _MEDIA:
            oled_write_ln_P(PSTR("Media\n"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Num  \n"), false);
            break;
        case _FUN:
            oled_write_ln_P(PSTR("Fun  \n"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Sym  \n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("     \n"), false);
            break;
    }
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_state(void) {
    uint8_t led_usb_state = host_keyboard_leds();
    oled_write_P(IS_LED_ON(led_usb_state, USB_LED_CAPS_LOCK)   ? PSTR("CAPS ") : PSTR("     "), false);
}

bool oled_task_user(void) {
    render_space();
    render_logo();
    render_space();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
    render_space();
    render_layer_state();
    render_space();
    render_state();
    return false;
}
#endif

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
