#ifndef CONFIG_H
#define CONFIG_H

// #include "config_common.h"

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

// ホールエフェクトセンサのピン設定
#define HALL_SENSOR_PIN_W GP6
#define HALL_SENSOR_PIN_A GP29
#define HALL_SENSOR_PIN_S GP7
#define HALL_SENSOR_PIN_D GP1
#define HALL_SENSOR_PIN_SPC GP0

#define EEPROM_HALL_EFFECT_THRESHOLD_ADDR 0

#endif
