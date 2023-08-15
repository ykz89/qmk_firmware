#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
	K00, K01, \
    K33, K34, \
	K10, K11, \
    K43, K44, \
	K20, K21, K22, \
    K53, K54 \
) { \
	{ K00, K01, XXX, XXX, XXX }, \
	{ K10, K11, XXX, XXX, XXX }, \
	{ K20, K21, K22, XXX, XXX }, \
	{ XXX, XXX, XXX, K33, K34 }, \
	{ XXX, XXX, XXX, K43, K44 }, \
	{ XXX, XXX, XXX, K53, K54 }  \
}
