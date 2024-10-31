// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DIGITIZER_MOTION_PIN GP28
#define DIGITIZER_MOTION_PIN_ACTIVE_LOW yes
#define MXT_SWITCH_XY
#define MXT_SENSOR_WIDTH_MM 91
#define MXT_SENSOR_HEIGHT_MM 156

// TODO: Tweak these if the sensor tracks poorly
#define MXT_GAIN 5
#define MXT_TOUCH_THRESHOLD 14
#define MXT_TOUCH_HYST 8
#define MXT_INTERNAL_TOUCH_HYST 3
#define MXT_INTERNAL_TOUCH_THRESHOLD 8

#define I2C1_CLOCK_SPEED 1000000