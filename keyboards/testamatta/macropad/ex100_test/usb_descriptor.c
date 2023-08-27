#include "usb_descriptor.h"
#include "config.h"

// 上書きする必要がある場合は以下で行う
// #define VENDOR_ID       0x1234
// #define PRODUCT_ID      0x5678
// #define DEVICE_VER      0x0001

#ifndef HID_KEYBOARD_ENDPOINT_IN
#define HID_KEYBOARD_ENDPOINT_IN 0x81
#endif

#ifndef HID_KEYBOARD_ENDPOINT_OUT
#define HID_KEYBOARD_ENDPOINT_OUT 0x01
#endif

#define HID_KEYBOARD_EPIN_SIZE       64
#define HID_KEYBOARD_EPOUT_SIZE      64

#define STR_MANUFACTURER 1
#define STR_PRODUCT      2
#define STR_SERIAL       3

#define REPORT_ID_KEYBOARD 0x01
#define REPORT_ID_MOUSE 0x02

const uint8_t keyboard_hid_report_descriptor[/*... size ...*/] = {
    0x05, 0x01,       // USAGE_PAGE (Generic Desktop)
    0x09, 0x06,       // USAGE (Keyboard)
    0xa1, 0x01,       // COLLECTION (Application)
    0x05, 0x07,       //   USAGE_PAGE (Keyboard)
    0x19, 0xe0,       //   USAGE_MINIMUM (Keyboard LeftControl)
    0x29, 0xe7,       //   USAGE_MAXIMUM (Keyboard Right GUI)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x01,       //   LOGICAL_MAXIMUM (1)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x95, 0x08,       //   REPORT_COUNT (8)
    0x81, 0x02,       //   INPUT (Data,Var,Abs)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x75, 0x08,       //   REPORT_SIZE (8)
    0x81, 0x03,       //   INPUT (Cnst,Var,Abs)
    0x95, 0x05,       //   REPORT_COUNT (5)
    0x75, 0x01,       //   REPORT_SIZE (1)
    0x05, 0x08,       //   USAGE_PAGE (LEDs)
    0x19, 0x01,       //   USAGE_MINIMUM (Num Lock)
    0x29, 0x05,       //   USAGE_MAXIMUM (Kana)
    0x91, 0x02,       //   OUTPUT (Data,Var,Abs)
    0x95, 0x01,       //   REPORT_COUNT (1)
    0x75, 0x03,       //   REPORT_SIZE (3)
    0x91, 0x03,       //   OUTPUT (Cnst,Var,Abs)
    0x95, 0x06,       //   REPORT_COUNT (6)
    0x75, 0x08,       //   REPORT_SIZE (8)
    0x15, 0x00,       //   LOGICAL_MINIMUM (0)
    0x25, 0x65,       //   LOGICAL_MAXIMUM (101)
    0x05, 0x07,       //   USAGE_PAGE (Keyboard)
    0x19, 0x00,       //   USAGE_MINIMUM (Reserved (no event indicated))
    0x29, 0x65,       //   USAGE_MAXIMUM (Keyboard Application)
    0x81, 0x00,       //   INPUT (Data,Ary,Abs)
    0xc0              // END_COLLECTION
};

const tusb_desc_device_t device_descriptor = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = TUSB_CLASS_MISC,
    .bDeviceSubClass    = MISC_SUBCLASS_COMMON,
    .bDeviceProtocol    = MISC_PROTOCOL_IAD,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,
    .idVendor           = VENDOR_ID,
    .idProduct          = PRODUCT_ID,
    .bcdDevice          = DEVICE_VER,
    .iManufacturer      = STR_MANUFACTURER,
    .iProduct           = STR_PRODUCT,
    .iSerialNumber      = STR_SERIAL,
    .bNumConfigurations = 1
};

// Configuration descriptor
uint8_t const config_descriptor[] = {
    // Interface descriptor
    0x09,           // bLength: Interface Descriptor size
    TUSB_DESC_INTERFACE,  // bDescriptorType: Interface
    0x00,           // bInterfaceNumber: Number of Interface
    0x00,           // bAlternateSetting: Alternate setting
    0x02,           // bNumEndpoints
    0x03,           // bInterfaceClass: HID
    0x01,           // bInterfaceSubClass: 1=BOOT, 0=no boot
    0x02,           // bInterfaceProtocol: 0=none, 1=keyboard, 2=mouse
    0x00,           // iInterface:

    // HID descriptor
    0x09,           // bLength: HID Descriptor size
    TUSB_DESC_HID,  // bDescriptorType: HID
    0x11, 0x01,     // bcdHID: HID Class Spec release number を 0x0111 から 0x11, 0x01 に変更
    0x00,           // bCountryCode: Hardware target country
    0x01,           // bNumDescriptors: Number of HID class descriptors to follow
    0x22,           // bDescriptorType
    sizeof(keyboard_hid_report_descriptor),  // wItemLength: Total length of Report descriptor

    // Endpoint 1 descriptor
    0x07,                                   // bLength: Endpoint Descriptor size
    TUSB_DESC_ENDPOINT,                      // bDescriptorType: Endpoint
    HID_KEYBOARD_ENDPOINT_IN,                // bEndpointAddress: Endpoint Address (IN)
    0x03,                                   // bmAttributes: Interrupt transfer type
    HID_KEYBOARD_EPIN_SIZE,                 // wMaxPacketSize:
    0x05,                                   // bInterval:

    // Endpoint 2 descriptor
    0x07,                                   // bLength: Endpoint Descriptor size
    TUSB_DESC_ENDPOINT,                      // bDescriptorType: Endpoint
    HID_KEYBOARD_ENDPOINT_OUT,               // bEndpointAddress: Endpoint Address (OUT)
    0x03,                                   // bmAttributes: Interrupt transfer type
    HID_KEYBOARD_EPOUT_SIZE,                // wMaxPacketSize:
    0x05                                    // bInterval:
};

// この部分で新しい関数やタスクを定義することが可能です。
// 例:
// void my_custom_function(void) {
//     // do something
// }

tusb_desc_device_t const desc_device = {
    .bLength            = sizeof(tusb_desc_device_t),
    .bDescriptorType    = TUSB_DESC_DEVICE,
    .bcdUSB             = 0x0200,
    .bDeviceClass       = TUSB_CLASS_UNSPECIFIED,
    .bDeviceSubClass    = TUSB_CLASS_UNSPECIFIED,
    .bDeviceProtocol    = TUSB_CLASS_UNSPECIFIED,
    .bMaxPacketSize0    = CFG_TUD_ENDPOINT0_SIZE,

/*  .idVendor           = VENDOR_ID,
    .idProduct          = PRODUCT_ID,
    .bcdDevice          = 0x0100,

    .iManufacturer      = STR_MANUFACTURER,
    .iProduct           = STR_PRODUCT,
    .iSerialNumber      = STR_SERIAL,
*/

    .bNumConfigurations = 1
};

uint8_t const desc_hid_report[] = {
    TUD_HID_REPORT_DESC_KEYBOARD(HID_REPORT_ID(REPORT_ID_KEYBOARD)),
    TUD_HID_REPORT_DESC_MOUSE   (HID_REPORT_ID(REPORT_ID_MOUSE))
};

uint16_t get_usb_descriptor(uint16_t wValue, uint16_t wIndex, uint16_t wLength, const void** const descriptor) {
    // USBデスクリプター取得関数の実装はこちら。
    // 通常この部分は変更不要。
    return 0;
};

// この関数は外部から呼び出されることを想定しています。
// たとえば、キーボードイベントが発生した時など。
void send_hid_report(uint8_t *report, uint8_t len) {
    if (tud_hid_ready()) {
        tud_hid_report(0, report, len);
    }
};

// init_usb関数の実装は以下
void init_usb(void) {
    // こちらにUSBの初期化に必要なコードを追加
    // TinyUSBライブラリの初期化
    tusb_init();
};

// 通常、メインループまたはRTOSタスクで次の関数を呼び出します。
// これはusb_descriptor.c以外で行うことが一般的ですが、必要ならこちらにも追加できます。
void usb_task(void) {
    // TinyUSBデバイスタスク
    tud_task();
};

