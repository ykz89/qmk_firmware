#pragma once

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.

#ifdef COMBO_ENABLE
#    define COMBO_COUNT 6
#    define COMBO_TERM 200
#endif

#define AZOTEQ_IQS5XX_TPS65
#define AZOTEQ_IQS5XX_TAP_ENABLE true
#define AZOTEQ_IQS5XX_TWO_FINGER_TAP_ENABLE true
#define AZOTEQ_IQS5XX_PRESS_AND_HOLD_ENABLE true
#define AZOTEQ_IQS5XX_SWIPE_X_ENABLE true
#define AZOTEQ_IQS5XX_SWIPE_Y_ENABLE true
#define AZOTEQ_IQS5XX_ZOOM_ENABLE true
#define AZOTEQ_IQS5XX_SCROLL_ENABLE true

#define I2C1_SDA_PIN        GP10
#define I2C1_SCL_PIN        GP11

