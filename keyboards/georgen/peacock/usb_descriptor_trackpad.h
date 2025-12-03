// Copyright 2024 George Norton (@george-norton)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "usb_descriptor.h"

#ifdef MACOS_TRACKPAD_MODE
// Trackpad report descriptor - defined in usb_descriptor_trackpad.c
extern const USB_Descriptor_HIDReport_Datatype_t PROGMEM TrackpadReport[];
#endif

