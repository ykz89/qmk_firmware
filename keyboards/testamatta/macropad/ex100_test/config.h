#ifndef CONFIG_H
#define CONFIG_H

// こちらを追加
#define STR_MANUFACTURER 1
#define STR_PRODUCT      2
#define STR_SERIAL       3
// ここまで

// #include "config_common.h"

// Disable all parameter assertions
#define PARAM_ASSERTIONS_ENABLE_ALL 0
#define PARAM_ASSERTIONS_DISABLE_ALL 1

#define MATRIX_ROWS 3
#define MATRIX_COLS 3

#define DIRECT_PINS { \
    { GP28, GP6, GP2 }, \
    { GP29, GP7, GP1 }, \
    { GP0 } \
}

#define ENCODERS_PAD_A { GP26, GP4 }
#define ENCODERS_PAD_B { GP27, GP3 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 1

#endif
