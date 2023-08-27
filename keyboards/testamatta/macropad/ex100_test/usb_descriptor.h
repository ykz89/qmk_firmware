#ifndef USB_DESCRIPTOR_H
#define USB_DESCRIPTOR_H

#include "tusb.h"

// 追加：新しいデスクリプタのヘッダーファイル
// #include "tmk_core/protocol/vusb/usbconfig.h"
/*
lib/chibios-contrib/ext/nxp-middleware-usb/output/source/device/class/usb_device_class.h
lib/vusb/examples/hid-custom-rq/firmware/main.c
lib/vusb/examples/hid-data/firmware/main.c
lib/vusb/examples/hid-mouse/firmware/main.c
lib/vusb/tests/usbconfig.h
lib/vusb/usbdrv/usbconfig-prototype.h
lib/vusb/usbdrv/usbdrv.h
tmk_core/protocol/vusb/usbconfig.h
*/

// 実際のHIDレポートデスクリプタの内容
// extern const uint8_t keyboard_hid_report_descriptor[];
// #define KEYBOARD_HID_DESC_SIZE  (sizeof(keyboard_hid_report_descriptor)/sizeof(uint8_t))  // これは配列が完全に定義されている場所でしか使用できません
#define KEYBOARD_HID_DESC_SIZE  64

// 新しい定義
// #define HID_REPORT_DESC_SIZE  sizeof(hidReportDescriptor)  // または usbHidReportDescriptor
// #define HID_REPORT_DESC_SIZE  sizeof(usbHidReportDescriptor)  // または hidReportDescriptor

// こちらを追加
#ifndef TUSB_DESC_HID
#define TUSB_DESC_HID 0x21  // この値は適切な値に設定する必要があります。
#endif
// ここまで

// 既存の宣言をコメントアウトまたは削除
// extern const uint8_t keyboard_hid_report_descriptor[KEYBOARD_HID_DESC_SIZE];

// 新しい宣言
// extern const uint8_t hidReportDescriptor[HID_REPORT_DESC_SIZE];  // または usbHidReportDescriptor
// extern const uint8_t usbHidReportDescriptor[HID_REPORT_DESC_SIZE];  // または hidReportDescriptor

// 以下はその他のコード（変更なし）
extern const tusb_desc_device_t device_descriptor;

#define HID_KEYBOARD_ENDPOINT_IN      0x81
#define HID_KEYBOARD_ENDPOINT_OUT     0x01
#define HID_KEYBOARD_EPIN_SIZE        64
#define HID_KEYBOARD_EPOUT_SIZE       64

#define KEYBOARD_EPSIZE              8  // 適切な値に設定してください。
#define SHARED_EPSIZE                8  // 同上
#define CONSOLE_EPSIZE               8  // 同上
#define CDC_NOTIFICATION_EPSIZE      16 // 適切な値に設定してください。

#define CONSOLE_IN_EPNUM             2  // 適切な値に設定してください。
#define CONSOLE_OUT_EPNUM            3  // 同上
#define KEYBOARD_IN_EPNUM            1  // 同上
#define SHARED_IN_EPNUM              4  // 同上
#define MOUSE_IN_EPNUM               5  // 同上

#define SHARED_INTERFACE             1  // 同上

#define KEYBOARD_INTERFACE           0  // 適切な値に設定してください。

uint16_t get_usb_descriptor(uint16_t wValue, uint16_t wIndex, uint16_t wLength, const void** const descriptor);
extern uint8_t const config_descriptor[];
void init_usb(void);  // USBの初期化関数のプロトタイプ。実際の関数は実装する必要があります。

#endif // USB_DESCRIPTOR_H
