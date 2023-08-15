#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    LAYOUT(
        KC_ESC,  KC_F1,   KC_MUTE,   ENC1,    ENC2,
        KC_TAB,  KC_Q,    KC_W,      KC_E,    KC_R,
        KC_CAPS, KC_A,    KC_S,      KC_D,    KC_F,
        KC_LSFT, KC_Z,    KC_X,      KC_C,    KC_V,
        KC_LCTL, KC_LGUI, KC_LALT,   KC_SPC),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_NO, KC_NO,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    keypos_t key;
    if (index == 0) {
        if (clockwise) {
            key.row = 5, key.col = 0;
        } else {
            key.row = 5, key.col = 1;
        }
        tap_code(keymap_key_to_keycode(layer_switch_get_layer(key), key));
    }
    if (index == 1) {
        if (clockwise) {
            key.row = 5, key.col = 2;
        } else {
            key.row = 5, key.col = 3;
        }
        tap_code(keymap_key_to_keycode(layer_switch_get_layer(key), key));
    }
    return false;
}
