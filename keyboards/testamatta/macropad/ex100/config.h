// Copyright 2023 Hideki Nakamura (@hide-key)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

#define MATRIX_ROWS 3
#define MATRIX_COLS 3

#define DIRECT_PINS { \
    { GP28, GP6, GP2 }, \
    { GP29, GP7, GP1 }, \
    { GP0 } \
}

#define ENCODERS_PAD_A { GP26, GP4 }
#define ENCODERS_PAD_B { GP27, GP3 }

#define DEBOUNCE 5

#define DYNAMIC_KEYMAP_LAYER_COUNT 1

#endif
