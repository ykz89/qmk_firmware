#pragma once

#include "quantum.h"

enum custom_keycodes {
    KC_EX1 = SAFE_RANGE,
    KC_EX2
};

#define ENC1 KC_EX1
#define ENC2 KC_EX2

#define LAYOUT( \
    K00, K01, K02, ENC1, ENC2, \
    K10, K11, K12, K13, K14, \
    K20, K21, K22, K23, K24, \
    K30, K31, K32, K33, K34, \
    K40, K41, K42, K43 \
) { \
    { K00,   K01,   K02,   KC_NO, KC_NO }, \
    { K10,   K11,   K12,   K13,   K14   }, \
    { K20,   K21,   K22,   K23,   K24   }, \
    { K30,   K31,   K32,   K33,   K34   }, \
    { K40,   K41,   K42,   K43,   KC_NO }, \
    { ENC1,  ENC2,  KC_NO, KC_NO, KC_NO } \
}
