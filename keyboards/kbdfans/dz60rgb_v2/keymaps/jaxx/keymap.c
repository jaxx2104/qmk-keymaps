#include QMK_KEYBOARD_H

// Custom keycodes
enum custom_keycodes {
    CK_EISU = SAFE_RANGE,  // Tap: Eisu (KC_LNG2), Hold: GUI
    CK_KANA,               // Tap: Kana (KC_LNG1), Hold: Alt
};

// Layer definitions
enum layers {
    _BASE,
    _FN,
};

// Tap/hold state tracking
static uint16_t eisu_timer = 0;
static uint16_t kana_timer = 0;
static bool eisu_held = false;
static bool kana_held = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_60_ansi_arrow(
        QK_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   MO(_FN),
        KC_LCTL, KC_LALT, CK_EISU,                   KC_SPC,                    CK_KANA, KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [_FN] = LAYOUT_60_ansi_arrow(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        _______, RM_TOGG, RM_NEXT, RM_HUEU, RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, _______, KC_PSCR, KC_SCRL, KC_PAUS, QK_BOOT,
        _______, RM_SPDU, RM_SPDD, _______, _______, _______, _______, _______, _______, _______, _______, _______,          EE_CLR,
        _______, _______, _______, _______, _______, _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______, KC_PGUP, _______,
        _______, _______, _______,                   _______,                   _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CK_EISU:
            if (record->event.pressed) {
                eisu_timer = timer_read();
                eisu_held = false;
            } else {
                if (eisu_held) {
                    unregister_mods(MOD_BIT(KC_LGUI));
                } else if (timer_elapsed(eisu_timer) < TAPPING_TERM) {
                    tap_code(KC_LNG2);  // Eisu
                }
                eisu_held = false;
                eisu_timer = 0;
            }
            return false;

        case CK_KANA:
            if (record->event.pressed) {
                kana_timer = timer_read();
                kana_held = false;
            } else {
                if (kana_held) {
                    unregister_mods(MOD_BIT(KC_RALT));
                } else if (timer_elapsed(kana_timer) < TAPPING_TERM) {
                    tap_code(KC_LNG1);  // Kana
                }
                kana_held = false;
                kana_timer = 0;
            }
            return false;

        default:
            if (record->event.pressed) {
                if (eisu_timer > 0 && !eisu_held) {
                    register_mods(MOD_BIT(KC_LGUI));
                    eisu_held = true;
                }
                if (kana_timer > 0 && !kana_held) {
                    register_mods(MOD_BIT(KC_RALT));
                    kana_held = true;
                }
            }
            break;
    }
    return true;
}
