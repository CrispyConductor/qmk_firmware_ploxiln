#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FUNCBANK,
    _HIST,
    _HISTCODE,
    _FN,
    _FNADV
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    QMKBEST = SAFE_RANGE,
    QMKURL
};

enum unicode_names {
    DW_PLUSMINUS,
    DW_DEGREE,
    DW_HALF,
    DW_QUARTER,
    DW_LBRACKET,
    DW_RBRACKET,
    DW_SUP2,
    DW_SUP3,
    DW_SECTION,
    DW_PARAGRAPH
};

const uint32_t PROGMEM unicode_map[] = {
    [DW_PLUSMINUS] = 0x00B1,  // ±
    [DW_DEGREE]    = 0x00B0,  // °
    [DW_HALF]      = 0x00BD,  // ½
    [DW_QUARTER]   = 0x00BC,  // ¼
    [DW_LBRACKET]  = 0x005B,  // [
    [DW_RBRACKET]  = 0x005D,  // ]
    [DW_SUP2]      = 0x00B2,  // ²
    [DW_SUP3]      = 0x00B3,  // ³
    [DW_SECTION]   = 0x00A7,  // §
    [DW_PARAGRAPH] = 0x00B6   // ¶
};

/*
 * CrispyConductor's DisplayWriter Key Map
 *
 * Base layer:
 * - Most keys behave as expected.
 * - Lock, Shift, Paragraph, Code, and Enter keys are used for the modifiers
 *   Ctrl, Shift, Super, Alt, Fn; respectively.
 * - Nonstandard punctuation is mapped roughly positionally to modern
 *   equivalents.  'Degree' key becomes backtick/tilde; 2 keys right of 'P'
 *   become brackets; '3 2' key becomes backslash/pipe.
 * - Two positions for escape; 'Index' and upper-right key in the left-hand key
 *   block (positionally similar to a normal Esc position).
 * - Upper-right key block is mostly standard nav cluster (Ins/Home/PgUp/Del/
 *   End/PgDn).  Remaining 2 keys on right are PrintScrn and AppContext.
 * - Lower-right key block is remapped to a T arrow nav.  Remaining 4 keys
 *   are media controls; Play/Pause, Mute, VolUp, VolDown.
 * - Lower 8 keys in left-hand key block are mapped to F13-F20.
 * - Upper-left key in left-hand key block momentarily activates historical layer.
 *
 * Fn layer (hold ENTER): Function keys and uncommon keys.
 * - Function keys are either Fn+Number (incl. dash and equals for F11, F12) or
 *   the left-hand key block (F1-F10).
 * - Upper-left key in upper-right key block toggles speaker "haptic" feedback.
 * - Lower-right key block has uncommon key functions.  First 3 keys are
 *   caps lock, scroll lock, pause.
 * - Fn+Space for Advanced Fn layer.
 * - Fn+H toggles historical key map layer.
 * - Fn+F toggles function bank layer - left-hand keys are all F1-F10.
 *
 * Advanced Fn layer (hold ENTER+Space): Internal keyboard operations.
 * - 'E' resets EEPROM.
 * - 'R' resets to bootloader.
 * - 'D' enables debug mode.
 *
 * Historical layer (toggle with ENTER+H): Approximate original-DisplayWriter-inspired key functions.
 * - Special symbol legends in alpha block are sent as unicode macros.
 * - 'End' key sends 'End'.
 * - 'Print' key sends Print Screen.
 * - Arrow keys behave as specified on the legends.
 * - 'CODE'+Left/Right becomes Home/End.
 * - 'CODE'+Up/Down becomes Ctrl+Home/Ctrl+End.
 * - 'LOCK' becomes caps lock.  LCTL is assigned to upper-right key in left-hand block for convenience.
 */

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_all(
        MO(_HIST),KC_ESC,                                                                                                                                               KC_INS , KC_HOME, KC_PGUP, KC_PSCR,
        KC_F13 , KC_F14 ,   KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_MINS, KC_EQL ,  KC_BSPC   , KC_ESC,   KC_DEL , KC_END , KC_PGDN, KC_APP,
        KC_F15 , KC_F16 ,   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC, KC_RBRC,    KC_ENT ,
        KC_F17 , KC_F18 ,   KC_LCTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_BSLS,                        KC_MPLY, KC_UP  , KC_MUTE, KC_VOLU,
        KC_F19 , KC_F20 ,   KC_LSFT, KC_LGUI, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH,            KC_RSFT  ,           KC_LEFT, KC_DOWN, KC_RGHT, KC_VOLD,
                                          KC_LALT,                     KC_SPC ,                  MO(_FN)
    ),
    [_FUNCBANK] = LAYOUT_all(
        KC_F1, KC_F2,                                                                                                                                               _______, _______, _______, _______,
        KC_F3, KC_F4,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______   , _______,  _______, _______, _______, _______,
        KC_F5, KC_F6,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,
        KC_F7, KC_F8,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______,
        KC_F9, KC_F10,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______  ,           _______, _______, _______, _______,
                                          _______,                     _______,                 _______
    ),
    [_FN] = LAYOUT_all(
        KC_F1  , KC_F2  ,                                                                                                                                               HPT_TOG, KC_NO ,  KC_NO  , KC_NO,
        KC_F3  , KC_F4  ,   KC_NO  , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,  KC_NO     , KC_NO ,   KC_NO  , KC_NO  , KC_NO  , KC_NO,
        KC_F5  , KC_F6  ,   KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,    KC_NO  ,
        KC_F7  , KC_F8  ,   _______, KC_NO  , KC_NO  , KC_NO,TG(_FUNCBANK), KC_NO,TG(_HIST),KC_NO , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,                        KC_CAPS, KC_SLCK, KC_PAUS, KC_NO,
        KC_F9  , KC_F10 ,   _______, _______, KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  , KC_NO  ,            _______  ,           KC_NO  , KC_NO  , KC_NO  , KC_NO,
                                          _______,                     MO(_FNADV),                  _______
    ),
    [_FNADV] = LAYOUT_all(
        _______, _______,                                                                                                                                               HPT_TOG, HPT_DWLD, HPT_DWLI, HPT_BUZ,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______   , _______,  _______, _______, _______, _______,
        _______, _______,    _______, _______, _______, EEPROM_RESET, RESET, _______, _______, _______, _______, _______, _______, _______, _______,    _______,
        _______, _______,     _______, _______, _______, DEBUG, _______, _______, _______, _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______  ,           _______, _______, _______, _______,
                                          _______,                     _______,                  _______
    ),
    [_HIST] = LAYOUT_all(
        _______, KC_LCTL,                                                                                                                                                           KC_DEL, _______, _______, _______,
        _______, _______,   XP(DW_PLUSMINUS, DW_DEGREE), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______   , _______,  _______, _______, _______, _______,
        _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XP(DW_HALF, DW_QUARTER), XP(DW_RBRACKET, DW_LBRACKET),    _______,
        _______, KC_PSCR,    KC_CAPS, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, XP(DW_SUP2, DW_SUP3),                                KC_UP  , KC_DOWN, _______, _______,
        KC_END,  _______,    _______, XP(DW_SECTION, DW_PARAGRAPH), _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______  ,           KC_LEFT, KC_RIGHT, _______, _______,
                                          MO(_HISTCODE),                     _______,                 _______
    ),
    [_HISTCODE] = LAYOUT_all(
        KC_NO,   _______,                                                                                                                                               _______, _______, _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______   , _______,  _______, _______, _______, _______,
        _______, _______,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,
        _______, _______,     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                      LCTL(KC_HOME), LCTL(KC_END), _______, _______,
        _______, _______,   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,            _______  ,           KC_HOME, KC_END,  _______, _______,
                                          _______,                     _______,                 _______
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool six_hist_mode = false;

    switch (keycode) {
        case KC_6:
            if (record->event.pressed) {
                six_hist_mode = layer_state_is(_HIST) && (get_mods() & MOD_MASK_SHIFT);
                if (six_hist_mode) {
                    send_unicode_string("¢");
                    return false;
                }
            } else if (six_hist_mode) {
                six_hist_mode = false;
                return false;
            }
            break;
        case QMKBEST:
            if (record->event.pressed) {
                // when keycode QMKBEST is pressed
                SEND_STRING("QMK is the best thing ever!");
            } else {
                // when keycode QMKBEST is released
            }
            break;
        case QMKURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://qmk.fm/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
    }
    return true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
