#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "quantum.h"

void ex100_adc_setup(void);
uint16_t ex100_analogRead(uint32_t pin);

/* #define HALL_SENSOR_PIN_W GP6
#define HALL_SENSOR_PIN_A GP29
#define HALL_SENSOR_PIN_S GP7
#define HALL_SENSOR_PIN_D GP1
#define HALL_SENSOR_PIN_SPC GP0 */

// KC_NOを排除したLAYOUT マクロの定義
#define LAYOUT( \
    K00, K01, K02, \
    K10, K11, K12, \
    K21  \
) { \
    { K00, K01, K02 }, \
    { K10, K11, K12 }, \
    { K21 }  \
}

#endif
