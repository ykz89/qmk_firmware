#include "ex001.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	LAYOUT(
		KC_0, KC_1,              KC_2, KC_3,
        KC_4, KC_5,              KC_6, KC_7,
        KC_8, KC_TRNS, KC_SPACE, KC_TRNS, KC_9),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

	LAYOUT(
		KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS,		   KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
/*    } else if (index == 1) { // Second encoder
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        } */
    }
    return false;
}
