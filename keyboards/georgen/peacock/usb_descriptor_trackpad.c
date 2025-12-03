// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "usb_descriptor.h"

#ifdef MACOS_TRACKPAD_MODE
// Trackpad (Digitizer) descriptor that mirrors the mouse report structure but uses Digitizer usage page.
const USB_Descriptor_HIDReport_Datatype_t PROGMEM TrackpadReport[] = {
    HID_RI_USAGE_PAGE(8, 0x0D),            // Digitizers
    HID_RI_USAGE(8, 0x05),                 // Touch Pad
    HID_RI_COLLECTION(8, 0x01),            // Application
        HID_RI_USAGE_PAGE(8, 0x01),        // Generic Desktop
        HID_RI_USAGE(8, 0x01),             // Pointer
        HID_RI_COLLECTION(8, 0x00),        // Physical
            // Buttons (8 bits)
            HID_RI_USAGE_PAGE(8, 0x09),    // Button
            HID_RI_USAGE_MINIMUM(8, 0x01), // Button 1
            HID_RI_USAGE_MAXIMUM(8, 0x08), // Button 8
            HID_RI_LOGICAL_MINIMUM(8, 0x00),
            HID_RI_LOGICAL_MAXIMUM(8, 0x01),
            HID_RI_REPORT_COUNT(8, 0x08),
            HID_RI_REPORT_SIZE(8, 0x01),
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_ABSOLUTE),

            // X/Y position (2 or 4 bytes)
            HID_RI_USAGE_PAGE(8, 0x01),    // Generic Desktop
            HID_RI_USAGE(8, 0x30),         // X
            HID_RI_USAGE(8, 0x31),         // Y
#            ifndef MOUSE_EXTENDED_REPORT
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x08),
#            else
            HID_RI_LOGICAL_MINIMUM(16, -32767),
            HID_RI_LOGICAL_MAXIMUM(16,  32767),
            HID_RI_REPORT_COUNT(8, 0x02),
            HID_RI_REPORT_SIZE(8, 0x10),
#            endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            // Vertical wheel (1 or 2 bytes)
            HID_RI_USAGE(8, 0x38),     // Wheel
#            ifndef WHEEL_EXTENDED_REPORT
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
#            else
            HID_RI_LOGICAL_MINIMUM(16, -32767),
            HID_RI_LOGICAL_MAXIMUM(16,  32767),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x10),
#            endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

            // Horizontal wheel (1 or 2 bytes)
            HID_RI_USAGE_PAGE(8, 0x0C),// Consumer
            HID_RI_USAGE(16, 0x0238),  // AC Pan
#            ifndef WHEEL_EXTENDED_REPORT
            HID_RI_LOGICAL_MINIMUM(8, -127),
            HID_RI_LOGICAL_MAXIMUM(8, 127),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x08),
#            else
            HID_RI_LOGICAL_MINIMUM(16, -32767),
            HID_RI_LOGICAL_MAXIMUM(16,  32767),
            HID_RI_REPORT_COUNT(8, 0x01),
            HID_RI_REPORT_SIZE(8, 0x10),
#            endif
            HID_RI_INPUT(8, HID_IOF_DATA | HID_IOF_VARIABLE | HID_IOF_RELATIVE),

        HID_RI_END_COLLECTION(0),
    HID_RI_END_COLLECTION(0),
};
#endif

