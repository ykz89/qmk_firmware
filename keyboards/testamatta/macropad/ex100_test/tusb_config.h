#ifndef _TUSB_CONFIG_H_
#define _TUSB_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------
// COMMON CONFIGURATION
//--------------------------------------------------------------------

#define CFG_TUSB_MCU               OPT_MCU_RP2040  // Your MCU type, e.g., OPT_MCU_RP2040 for Raspberry Pi Pico
#define CFG_TUSB_RHPORT0_MODE      OPT_MODE_DEVICE
#define CFG_TUSB_OS                OPT_OS_NONE
#define CFG_TUSB_DEBUG             0

// #define TUSB_OPT_DEVICE_ENABLED    1 // *********************************************************************
// #define TUSB_OPT_HOST_ENABLED      0 // *********************************************************************

//--------------------------------------------------------------------
// DEVICE MODE CONFIGURATION
//--------------------------------------------------------------------

#define CFG_TUD_ENDPOINT0_SIZE      64
#define CFG_TUD_CONFIG_TOTAL        1
#define CFG_TUD_TASK_QUEUE_SZ       16

#define CFG_TUD_HID                 1
#define CFG_TUD_CDC                 0
#define CFG_TUD_MSC                 0
#define CFG_TUD_HUB                 0
#define CFG_TUD_AUDIO               0
#define CFG_TUD_MIDI                0
#define CFG_TUD_DFU                 0
#define CFG_TUD_VENDOR              0

// Vendor class buffer size
#define CFG_TUD_VENDOR_EPSIZE       64

#ifdef __cplusplus
}
#endif

#endif // _TUSB_CONFIG_H_
