#include QMK_KEYBOARD_H

// NOTE_B0の再定義問題を回避
// #undef NOTE_B0
// #include "quantum/audio/musical_notes.h"

/* ,-----------------------.
 * | KC_ESC | KC_W  | KC_F1|
 * |--------|-------|------|
 * |  KC_A  | KC_S  | KC_D |
 * |--------|-------|------|
 * |        |KC_SPC |      |
 * `-----------------------' */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_W, KC_F1,
        KC_A,   KC_S, KC_D,
        KC_SPC
    )
};
