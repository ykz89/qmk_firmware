#include QMK_KEYBOARD_H
#include "keymap.h"

#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#define GAMING DF(_GAMING)
#define QWERTY DF(_QWERTY)
#define COLEMAK DF(_COLEMAK)

#define U_RDO C(KC_Y)
#define U_PST C(KC_V)
#define U_CPY C(KC_C)
#define U_CUT C(KC_X)
#define U_UND C(KC_Z)

#define NAV LT(_NAV, KC_SPC)
#define MOUSE LT(_MOUSE, KC_TAB)
#define MEDIA LT(_MEDIA, KC_ESC)
#define NUM LT(_NUM, KC_BSPC)
#define FUN LT(_FUN, KC_DEL)
#define SYM LT(_SYM, KC_ENT)

enum layer_number {
  _QWERTY = 0,
  _COLEMAK,
  _GAMING,
  _NAV,
  _MOUSE,
  _MEDIA,
  _NUM,
  _FUN,
  _SYM,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
    KC_ESC   , KC_1         , KC_2         , KC_3         , KC_4         , KC_5 ,                          KC_6 , KC_7         , KC_8         , KC_9           , KC_0            , KC_GRV         ,
    KC_TAB   , KC_Q         , KC_W         , KC_E         , KC_R         , KC_T ,                          KC_Y , KC_U         , KC_I         , KC_O           , KC_P            , KC_MINS        ,
    KC_LSFT  , LGUI_T(KC_A) , LALT_T(KC_S) , LCTL_T(KC_D) , LSFT_T(KC_F) , KC_G ,                          KC_H , LSFT_T(KC_J) , LCTL_T(KC_K) , LALT_T(KC_L)   , LGUI_T(KC_SCLN) , KC_QUOT        ,
    KC_LCTRL , KC_Z         , ALGR_T(KC_X) , KC_C         , KC_V         , KC_B , KC_LBRC ,      KC_RBRC , KC_N , KC_M         , KC_COMM      , ALGR_T(KC_DOT) , KC_SLSH         , RSFT_T(KC_ENT) ,
                                             XXXXXXX      , MEDIA        , NAV  , MOUSE   ,      SYM     , NUM  , FUN          , COLEMAK
  ),

  [_COLEMAK] = LAYOUT(
    KC_ESC   , KC_1         , KC_2         , KC_3         , KC_4         , KC_5 ,                          KC_6 , KC_7         , KC_8         , KC_9           , KC_0         , KC_GRV         ,
    KC_TAB   , KC_Q         , KC_W         , KC_F         , KC_P         , KC_B ,                          KC_J , KC_L         , KC_U         , KC_Y           , KC_SCLN      , KC_MINS        ,
    KC_LSFT  , LGUI_T(KC_A) , LALT_T(KC_R) , LCTL_T(KC_S) , LSFT_T(KC_T) , KC_G ,                          KC_M , LSFT_T(KC_N) , LCTL_T(KC_E) , LALT_T(KC_I)   , LGUI_T(KC_O) , KC_QUOT        ,
    KC_LCTRL , KC_Z         , ALGR_T(KC_X) , KC_C         , KC_D         , KC_V , KC_LBRC ,      KC_RBRC , KC_K , KC_H         , KC_COMM      , ALGR_T(KC_DOT) , KC_SLSH      , RSFT_T(KC_ENT) ,
                                             XXXXXXX      , MEDIA        , NAV  , MOUSE   ,      SYM     , NUM  , FUN          , GAMING
  ),

  [_GAMING] = LAYOUT(
    KC_ESC  , KC_1 , KC_2 , KC_3 , KC_4 , KC_5   ,                          _______ , _______ , _______ , _______ , _______ , _______ ,
    KC_TAB  , KC_Q , KC_W , KC_E , KC_R , KC_T   ,                          _______ , _______ , _______ , _______ , _______ , _______ ,
    KC_LSFT , KC_A , KC_S , KC_D , KC_F , KC_G   ,                          _______ , _______ , _______ , _______ , _______ , _______ ,
    KC_LCTL , KC_Z , KC_X , KC_C , KC_V , KC_B   , KC_I    ,      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
                            KC_V , KC_M , KC_SPC , KC_LALT ,      _______ , _______ , _______ , QWERTY
  ),

  [_NAV] = LAYOUT(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          U_RDO   , U_PST   , U_CPY   , U_CUT   , U_UND   , XXXXXXX ,
    XXXXXXX , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , XXXXXXX ,                          KC_CAPS , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , XXXXXXX ,
    XXXXXXX , XXXXXXX , KC_ALGR , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX , KC_INS  , KC_HOME , KC_PGDN , KC_PGUP , KC_END  , XXXXXXX ,
                                  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      KC_ENT  , KC_BSPC , KC_DEL  , XXXXXXX
  ),

  [_MOUSE] = LAYOUT(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          U_RDO   , U_PST   , U_CPY   , U_CUT   , U_UND   , XXXXXXX ,
    XXXXXXX , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , XXXXXXX ,                          XXXXXXX , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , XXXXXXX ,
    XXXXXXX , XXXXXXX , KC_ALGR , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , XXXXXXX ,
                                  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      KC_BTN1 , KC_BTN3 , KC_BTN2 , XXXXXXX
  ),

  [_MEDIA] = LAYOUT(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          RGB_TOG , RGB_MOD , RGB_HUI , RGB_SAI , RGB_VAI , XXXXXXX ,
    XXXXXXX , KC_LGUI , KC_LALT , KC_LCTL , KC_LSFT , XXXXXXX ,                          XXXXXXX , KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT , XXXXXXX ,
    XXXXXXX , XXXXXXX , KC_ALGR , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
                                  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,      KC_MSTP , KC_MPLY , KC_MUTE , XXXXXXX
  ),

  [_NUM] = LAYOUT(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_LBRC , KC_7    , KC_8    , KC_9    , KC_RBRC ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_SCLN , KC_4    , KC_5    , KC_6    , KC_EQL  ,                          XXXXXXX , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , XXXXXXX ,
    XXXXXXX , KC_GRV  , KC_1    , KC_2    , KC_3    , KC_BSLS , XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ALGR , XXXXXXX , XXXXXXX ,
                                  XXXXXXX , KC_DOT  , KC_0    , KC_MINS ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
  ),

  [_SYM] = LAYOUT(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_LCBR , KC_AMPR , KC_ASTR , KC_LPRN , KC_RCBR ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_COLN , KC_DLR  , KC_PERC , KC_CIRC , KC_PLUS ,                          XXXXXXX , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , XXXXXXX ,
    XXXXXXX , KC_TILD , KC_EXLM , KC_AT   , KC_HASH , KC_PIPE , XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ALGR , XXXXXXX , XXXXXXX ,
                                  XXXXXXX , KC_LPRN , KC_RPRN , KC_UNDS ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
  ),

  [_FUN] = LAYOUT(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_F12  , KC_F7   , KC_F8   , KC_F9   , KC_PSCR ,                          XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_F11  , KC_F4   , KC_F5   , KC_F6   , KC_SLCK ,                          XXXXXXX , KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , XXXXXXX ,
    XXXXXXX , KC_F10  , KC_F1   , KC_F2   , KC_F3   , KC_PAUS , XXXXXXX ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_ALGR , XXXXXXX , XXXXXXX ,
                                  XXXXXXX , KC_APP  , KC_SPC  , KC_TAB  ,      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
  ),
};


int RGB_current_mode;

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

void animate_luna(void);
const char *read_logo(void);

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
}

void render_wpm(void) {
#ifdef WPM_ENABLE
    uint8_t n = get_current_wpm();
    char wpm_counter[4];
    wpm_counter[3] = '\0';
    wpm_counter[2] = '0' + n % 10;
    wpm_counter[1] = ( n /= 10) % 10 ? '0' + (n) % 10 : (n / 10) % 10 ? '0' : ' ';
    wpm_counter[0] = n / 10 ? '0' + n / 10 : ' ';

    oled_write_P(PSTR("  WPM: "), false);
    oled_write(wpm_counter, false);
#endif
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_write_P(PSTR("  Base Layer: "), false);
        switch (get_highest_layer(default_layer_state)) {
            case _COLEMAK:
                oled_write_ln_P(PSTR("Colemak"), false);
                break;
            case _QWERTY:
                oled_write_ln_P(PSTR("Qwerty\n"), false);
                break;
            case _GAMING:
                oled_write_ln_P(PSTR("Gaming\n"), false);
                break;
        }
        oled_write_P(PSTR("  Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case _NAV:
                oled_write_P(PSTR("Nav\n\n"), false);
                break;
            case _MOUSE:
                oled_write_P(PSTR("Mouse\n\n"), false);
                break;
            case _MEDIA:
                oled_write_P(PSTR("Media\n\n"), false);
                break;
            case _NUM:
                oled_write_P(PSTR("Num\n\n"), false);
                break;
            case _FUN:
                oled_write_P(PSTR("Fun\n\n"), false);
                break;
            case _SYM:
                oled_write_P(PSTR("Sym\n\n"), false);
                break;
            default:
                oled_write_P(PSTR("Base\n\n"), false);
        }
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.num_lock ? PSTR("  NUM ") : PSTR("    "), false);
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
        oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);
        oled_write_P(PSTR("\n\n"), false);

        render_wpm();
    } else {
        oled_write(read_logo(), false);
        animate_luna();
    }
}
#endif // OLED_DRIVER_ENABLE

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {

    if (index == 0) { // Left
        switch (biton32(layer_state)) {
            case _QWERTY:
                // Move whole words. Hold shift to select while moving.
                if (clockwise) {
                    tap_code16(C(KC_RGHT));
                } else {
                    tap_code16(C(KC_LEFT));
                }
                break;
            case _MOUSE:
                // Move mouse up and down
                if (clockwise) {
                    tap_code16(C(KC_MS_D));
                } else {
                    tap_code16(C(KC_MS_U));
                }
                break;
            default:
                // History scrubbing. For Adobe products, hold shift while moving
                // backward to go forward instead.
                if (clockwise) {
                    tap_code16(C(KC_Z));
                } else {
                    tap_code16(C(KC_Y));
                }
                break;
        }
    } else if (index == 1) { // Right
        switch (biton32(layer_state)) {
            case _QWERTY:
                // Scrolling with PageUp and PgDn.
                if (clockwise) {
                    tap_code(KC_PGDN);
                } else {
                    tap_code(KC_PGUP);
                }
                break;
            case _MOUSE:
                // Move mouse left and right
                if (clockwise) {
                    tap_code16(C(KC_MS_R));
                } else {
                    tap_code16(C(KC_MS_L));
                }
                break;
            default:
                // Scroll through tabs
                if (clockwise) {
                    tap_code16(C(KC_TAB));
                } else {
                    tap_code16(S(C(KC_TAB)));
                }
                break;
        }
    }
    return true;
}
#endif
