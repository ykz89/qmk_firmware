// #undef PROCYON_50_42
// #define PROCYON_42_50
// #define MXT_INVERT_Y
// #define MXT_INVERT_X

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#define MACOS_TRACKPAD_MOD

// macOS trackpad mode configuration
// Timeout before resetting scan_time after inactivity (Microsoft PTP requirement)
#define DIGITIZER_INACTIVITY_TIMEOUT_MS 1000
// Multiplier to convert timer ticks to 100us units (Microsoft PTP requires scan_time in 100us ticks)
#define DIGITIZER_SCAN_TIME_MULTIPLIER 10
