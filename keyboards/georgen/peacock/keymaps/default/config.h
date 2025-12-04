// By default the sensor is tuned for a thin vinyl surface, to adjust for a 3mm acrylic surface set the following
// #define MXT_SURFACE_TYPE ACRYLIC

// macOS trackpad mode configuration
// Timeout before resetting scan_time after inactivity (Microsoft PTP requirement)
#define DIGITIZER_INACTIVITY_TIMEOUT_MS 1000
// Multiplier to convert timer ticks to 100us units (Microsoft PTP requires scan_time in 100us ticks)
#define DIGITIZER_SCAN_TIME_MULTIPLIER 10
