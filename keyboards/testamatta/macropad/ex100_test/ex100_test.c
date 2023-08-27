#include "ex100_test.h"

#define EEPROM_HALL_EFFECT_THRESHOLD_ADDR 0x00

#ifdef PARAM_ASSERTIONS_ENABLED
#undef PARAM_ASSERTIONS_ENABLED
#endif
#define PARAM_ASSERTIONS_ENABLED(x) 0

#include "keyboard.h"
#include "quantum.h"
#include "eeprom.h"
#include "lib/pico-sdk/src/rp2_common/hardware_adc/include/hardware/adc.h"
#include "hardware/gpio.h"
#include "lib/pico-sdk/src/common/pico_time/include/pico/time.h"

#define HALL_SENSOR_PIN_W GP6
#define HALL_SENSOR_PIN_A GP29
#define HALL_SENSOR_PIN_S GP7
#define HALL_SENSOR_PIN_D GP1
#define HALL_SENSOR_PIN_SPC GP0

// 一度だけ変数を定義する
static uint16_t hall_effect_threshold = 512;
static uint8_t encoder_turns = 0;

void ex100_adc_setup(void) {
    adc_init();
    adc_gpio_init(HALL_SENSOR_PIN_W);
    adc_gpio_init(HALL_SENSOR_PIN_A);
    adc_gpio_init(HALL_SENSOR_PIN_S);
    adc_gpio_init(HALL_SENSOR_PIN_D);
    adc_gpio_init(HALL_SENSOR_PIN_SPC);
}

uint16_t ex100_analogRead(uint32_t pin) {
    adc_select_input(pin);
    return adc_read();
}

void matrix_init_user(void) {
    ex100_adc_setup();
    hall_effect_threshold = eeprom_read_word((uint16_t*)EEPROM_HALL_EFFECT_THRESHOLD_ADDR);
    if (hall_effect_threshold == 0xFFFF || hall_effect_threshold > 1023) {
        hall_effect_threshold = 512;
    }
}

void matrix_scan_user(void) {
    uint16_t analogValue_W = ex100_analogRead(HALL_SENSOR_PIN_W);
    uint16_t analogValue_A = ex100_analogRead(HALL_SENSOR_PIN_A);
    uint16_t analogValue_S = ex100_analogRead(HALL_SENSOR_PIN_S);
    uint16_t analogValue_D = ex100_analogRead(HALL_SENSOR_PIN_D);
    uint16_t analogValue_SPC = ex100_analogRead(HALL_SENSOR_PIN_SPC);

    if (analogValue_W > hall_effect_threshold) register_code(KC_W);
    else unregister_code(KC_W);

    if (analogValue_A > hall_effect_threshold) register_code(KC_A);
    else unregister_code(KC_A);

    if (analogValue_S > hall_effect_threshold) register_code(KC_S);
    else unregister_code(KC_S);

    if (analogValue_D > hall_effect_threshold) register_code(KC_D);
    else unregister_code(KC_D);

    if (analogValue_SPC > hall_effect_threshold) register_code(KC_SPC);
    else unregister_code(KC_SPC);
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            encoder_turns++;
            if (encoder_turns == 10) {
                if (hall_effect_threshold < 1016) {
                    hall_effect_threshold += 8;
                }
                eeprom_write_word((uint16_t*)EEPROM_HALL_EFFECT_THRESHOLD_ADDR, hall_effect_threshold);
                encoder_turns = 0;
            }
        } else {
            encoder_turns--;
            if (encoder_turns == -10) {
                if (hall_effect_threshold > 7) {
                    hall_effect_threshold -= 8;
                }
                eeprom_write_word((uint16_t*)EEPROM_HALL_EFFECT_THRESHOLD_ADDR, hall_effect_threshold);
                encoder_turns = 0;
            }
        }
    }

    if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true; // 通常のQMKのencoderの処理をバイパスする場合はfalseを返します。
}
