// ハードウェアライブラリのアサーションを無効にする
#ifdef PARAM_ASSERTIONS_ENABLED
#undef PARAM_ASSERTIONS_ENABLED
#endif
#define PARAM_ASSERTIONS_ENABLED(x) 0

#include "keyboard.h"
#include "quantum.h"
#include "eeprom.h"

// RP2040のadc関数を利用するためのインクルード
#include "lib/pico-sdk/src/rp2_common/hardware_adc/include/hardware/adc.h"
#include "hardware/gpio.h"
#include "lib/pico-sdk/src/common/pico_time/include/pico/time.h"

#define HALL_SENSOR_PIN_W GP26
#define HALL_SENSOR_PIN_A GP27
#define HALL_SENSOR_PIN_S GP28
#define HALL_SENSOR_PIN_D GP29
#define HALL_SENSOR_PIN_SPC GP0

static uint16_t hall_effect_threshold = 512;  // Default ADC midpoint

// ADCの初期設定とピンの初期化
void adc_setup(void) {
    adc_init();
    adc_gpio_init(HALL_SENSOR_PIN_W);
    adc_gpio_init(HALL_SENSOR_PIN_A);
    adc_gpio_init(HALL_SENSOR_PIN_S);
    adc_gpio_init(HALL_SENSOR_PIN_D);
    adc_gpio_init(HALL_SENSOR_PIN_SPC);
}

// 与えられたピンからアナログ値を読み取る関数
uint16_t analogRead(uint8_t pin) {
    adc_select_input(pin);
    return adc_read();
}

void matrix_init_user(void) {
    adc_setup();
    hall_effect_threshold = eeprom_read_word((uint16_t*)EEPROM_HALL_EFFECT_THRESHOLD_ADDR);
    if (hall_effect_threshold == 0xFFFF) {
        hall_effect_threshold = 512;
    }
}

void matrix_scan_user(void) {
    uint16_t analogValue_W = analogRead(HALL_SENSOR_PIN_W);
    uint16_t analogValue_A = analogRead(HALL_SENSOR_PIN_A);
    uint16_t analogValue_S = analogRead(HALL_SENSOR_PIN_S);
    uint16_t analogValue_D = analogRead(HALL_SENSOR_PIN_D);
    uint16_t analogValue_SPC = analogRead(HALL_SENSOR_PIN_SPC);

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
            hall_effect_threshold++;
        } else {
            hall_effect_threshold--;
        }
        eeprom_write_word((uint16_t*)EEPROM_HALL_EFFECT_THRESHOLD_ADDR, hall_effect_threshold);
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return true;
}

int main(void) {
    matrix_init_user();

    while (1) {
        matrix_scan_user();
        sleep_ms(10);  // 10msのディレイ
    }

    return 0;
}
