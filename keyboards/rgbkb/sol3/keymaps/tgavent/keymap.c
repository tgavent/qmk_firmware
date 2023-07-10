/*
 * ----------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <https://github.com/Legonut> wrote this file.  As long as you retain this
 * notice you can do whatever you want with this stuff. If we meet some day, and
 * you think this stuff is worth it, you can buy me a beer in return. David Rauseo
 * ----------------------------------------------------------------------------
 */

#include QMK_KEYBOARD_H
#include "print.h"
#include "os_detection.h"


/* Qwerty
 * ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐  ┌──────┬──────┬──────┬──────┬──────┬──────┬──────┐
 * │ GESC │   1  │   2  │   3  │   4  │   5  │   -  │  │   =  │   6  │   7  │   8  │   9  │   0  │ BkSp │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Tab  │   Q  │   W  │   E  │   R  │   T  │   [  │  │   ]  │   Y  │   U  │   I  │   O  │   P  │   \  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │FNCAPS│   A  │   S  │   D  │   F  │   G  │   (  │  │   )  │   H  │   J  │   K  │   L  │   ;  │   '  │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │Shift │   Z  │   X  │   C  │   V  │   B  │   {  │  │   }  │   N  │   M  │   ,  │   .  │   /  │Enter │
 * ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤  ├──────┼──────┼──────┼──────┼──────┼──────┼──────┤
 * │ Ctrl │  Win │  Alt │  RGB │ ADJ  │      │ DEL  │  │ Enter│      │  FN  │ Left │ Down │ Up   │Right │
 * └──────┴──────┴──────┴──────┴──────┤ Space├──────┤  ├──────┤ Space├──────┴──────┴──────┴──────┴──────┘
 *                                    │      │ DEL  │  │ Enter│      │
 *                                    └──────┴──────┘  └──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┬──────┐                ┌──────┬──────┬──────┬──────┬──────┬──────┐
 * │Vol Dn│Vol Up│Vol Dn│Vol Up│Vol Dn│Vol Up│                │Vol Dn│Vol Up│Vol Dn│Vol Up│Vol Dn│Vol Up│
 * └──────┴──────┴──────┴──────┴──────┴──────┘                └──────┴──────┴──────┴──────┴──────┴──────┘
 * ┌──────┬──────┬──────┬──────┬──────┐                              ┌──────┬──────┬──────┬──────┬──────┐
 * │Vol Dn│Vol Up│ Prev │ Play │ Next │                              │Vol Dn│Vol Up│ Prev │ Play │ Next │
 * └──────┴──────┴──────┴──────┴──────┘                              └──────┴──────┴──────┴──────┴──────┘
 */

enum sol_layers {
    _QWERTY,
    _FN,
    _ADJUST
};

enum sol_keycodes {
    // Disables touch processing
    TCH_TOG = SAFE_RANGE,
    MENU_BTN,
    MENU_UP,
    MENU_DN,
    RGB_RST,
    SS_HELLO,
    SS_CUT,
    SS_COPY,
    SS_PASTE,
    UNDO,
    ZOOM_IN,
    ZOOM_OUT,
};

#define FN        MO(_FN)
#define ADJUST    MO(_ADJUST)
#define QWERTY    DF(_QWERTY)
#define FN_CAPS   LT(_FN, KC_CAPS)
#define OS        detected_host_os()
#define IS_MAC_OS (OS == OS_MACOS || OS == OS_IOS)
//#define RGB_ADJ  LT(_ADJUST, RGB_TOG)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_QWERTY] = LAYOUT(
        QK_GESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    ZOOM_IN,                  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
        KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    ZOOM_OUT,                 KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
        FN_CAPS,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    SS_COPY,                  SS_CUT, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    SS_PASTE,                 UNDO,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_SENT,
        KC_LCTL,  KC_LGUI, KC_LALT, KC_LGUI, ADJUST,  KC_SPC,  KC_PGDN, KC_DEL, KC_ENT,  KC_PGUP, KC_SPC,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_RCTL,

        KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU,                                     KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU, KC_VOLD, KC_VOLU,
        KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MPRV,                                                       KC_VOLD, KC_VOLU, KC_MNXT, KC_MPLY, KC_MPRV
    ),

    [_FN] = LAYOUT(
        _______, AU_TOGG, MU_TOGG, MI_MOD,  _______, _______, _______,                    KC_F12,  RGB_MOD, _______, _______, _______, _______, _______,
        _______, KC_HOME, KC_UP,   KC_END,   QK_RBT, DB_TOGG, SS_HELLO,                    _______, _______, KC_7,    KC_8,    KC_9,    KC_PLUS, KC_PGUP,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, MENU_BTN, _______, RGB_HUI,                    _______, _______, KC_4,    KC_5,    KC_6,    KC_PCMM, KC_ENT,
        _______, RGB_TOG, RGB_VAD, RGB_VAI, RGB_SAD, RGB_SAI, RGB_HUD,                    _______, _______, KC_1,    KC_2,    KC_3,    KC_PEQL, FN,
        _______, CK_TOGG,   CK_UP, CK_DOWN,  ADJUST, RGB_TOG, _______,  QK_BOOT, _______, _______, _______, KC_0,    KC_0,    KC_DOT,  KC_ENT,  QWERTY,

        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

    [_ADJUST] = LAYOUT(
        QK_GESC, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,  _______,                    _______, KC_F6,    KC_F7,   KC_F8,    KC_F9,     KC_F10,  _______,
        KC_TAB,  KC_CIRC, KC_PIPE, KC_LBRC, KC_RBRC, KC_DLR, _______,                    _______, KC_EXLM,  KC_GRV,  KC_UP,    KC_HASH,   _______, _______,
        FN_CAPS, KC_LABK, KC_RABK, KC_LPRN, KC_RPRN, KC_EQL,  KC_F11,                    _______, KC_MINS,  KC_LEFT, KC_DOWN,  KC_RIGHT,  _______, KC_ENT,
        KC_LSFT, KC_ASTR, KC_AMPR, KC_LCBR, KC_RCBR, KC_SCLN, KC_F12,                    _______, KC_AT,    KC_PERC, KC_COMM,  KC_DOT,    KC_SLSH, _______,
        _______, RGB_RMOD,RGB_TOG, RGB_MOD, KC_DEL,  KC_MPLY, KC_MNXT, KC_MPRV, KC_VOLD, KC_VOLU, KC_BSPC,  FN,      QWERTY,  _______, _______, _______,

        _______, _______, _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                       _______, _______, _______, _______, _______
    ),

};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SS_HELLO:
            if (record->event.pressed) {
                SEND_STRING("Hello, world!\n");
            }
            return false;
        case SS_CUT:
            if(record->event.pressed) {
                IS_MAC_OS ? SEND_STRING(SS_LCMD("x")) : SEND_STRING(SS_LCTL("x"));
            }
            return false;
        case SS_COPY:
            if(record->event.pressed) {
                IS_MAC_OS ? SEND_STRING(SS_LCMD("c")) : SEND_STRING(SS_LCTL("c"));
            }
            return false;
       case SS_PASTE:
            if(record->event.pressed) {
                IS_MAC_OS ? SEND_STRING(SS_LCMD("v")) : SEND_STRING(SS_LCTL("v"));
            }
            return false;
        case UNDO:
            if(record->event.pressed) {
                IS_MAC_OS ? SEND_STRING(SS_LCMD("z")) : SEND_STRING(SS_LCTL("z"));
            }
            return false;
        case ZOOM_OUT:
            if(record->event.pressed) {
                IS_MAC_OS ? SEND_STRING(SS_LCMD("-")) : SEND_STRING(SS_LWIN("-"));
            }
            return false;
        case ZOOM_IN:
            if(record->event.pressed) {
                IS_MAC_OS ? SEND_STRING(SS_LCMD("+")) : SEND_STRING(SS_LWIN("+"));
            }
            return false;
    }

    return true;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    // Sol 3 uses OLED_ROTATION_270 for default rotation on both halves
    return oled_init_user(OLED_ROTATION_270);
}

bool oled_task_user(void) {
    // Host Keyboard Layer Status
    oled_write_P(PSTR("Layer-----\n"), false);

    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("QWRTY\n"), false);
            break;
        case _FN:
            oled_write_P(PSTR("FN\n"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("ADJ\n"), false);
            break;
        default:
            // Or use the write_ln shortcut over adding '\n' to the end of your string
            oled_write_ln_P(PSTR("Undefined"), false);
    }

    oled_write_P(PSTR("-----\n"), false);
   
    // Host Keyboard LED Status
    led_t led_state = host_keyboard_led_state();
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    
    // Host OS Status
    oled_write_P(PSTR("   -----\n"), false);
    oled_write_P(PSTR("OS: \n"), false);
    
    switch (OS) {
        case OS_UNSURE:
            oled_write_P(PSTR("???\n"), false);
            break;
        case OS_WINDOWS:
            oled_write_P(PSTR("Win\n"), false);
            break;
        case OS_MACOS:
            oled_write_P(PSTR("Mac\n"), false);
            break;
        case OS_LINUX:
            oled_write_P(PSTR("Linux\n"), false);
            break;
        case OS_IOS:
            oled_write_P(PSTR("IOS\n"), false);
            break;
        default:
            return true;
    }

    return false;
}