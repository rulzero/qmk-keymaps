/* Copyright 2020 Andrew Kannan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layer_names {
    _BASE,
    _FN1,
    _FN2,
    _FN3
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_all(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSPC,  KC_PGUP,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,             KC_PGDN,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,            KC_UP,    MO(_FN2),
    KC_LCTL,  KC_LGUI,  KC_LALT,            LT(_FN1, KC_SPC),   KC_SPC,             KC_RALT,  KC_RGUI,  KC_RCTL,            KC_LEFT,  KC_DOWN,  KC_RGHT
  ),

  [_FN1] = LAYOUT_all(
    _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  _______,  _______,  _______,
    _______,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,            _______,            _______,            _______,  _______,  _______,            _______,  _______,  _______
  ),

  [_FN2] = LAYOUT_all(
    _______,  _______,  _______,  _______,  MO(_FN3), _______,  _______,  _______,  _______,  KC_INS,   KC_PSCR,  KC_SCRL,  KC_PAUS,  KC_DEL,   KC_HOME,
    KC_CAPS,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            KC_END,
    _______,  _______,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,            _______,            _______,            _______,  KC_APP,   _______,            _______,  _______,  _______
  ),

  [_FN3] = LAYOUT_all(
    _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,            _______,            _______,            _______,  _______,  _______,            _______,  _______,  _______
  )
};

uint8_t mod_state;

bool replace(keyrecord_t *record, uint16_t replacement_keycode) {
    static bool replacement_key_registered;
    if (record->event.pressed) {
        if (mod_state & MOD_BIT(KC_RALT)) {
            del_mods(MOD_BIT(KC_RALT));
            register_code(replacement_keycode);
            replacement_key_registered = true;
            set_mods(mod_state);
            return false;
        }
    } else {
        if (replacement_key_registered) {
            unregister_code(replacement_keycode);
            replacement_key_registered = false;
            return false;
        }
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    mod_state = get_mods();
    switch (keycode) {

        case KC_ESC: {
            return replace(record, KC_GRV);
        }
        case KC_O: {
            return replace(record, KC_MINS);
        }
        case KC_P: {
            return replace(record, KC_EQL);
        }
        case KC_SLSH: {
            return replace(record, KC_BSLS);
        }

    }
    return true;
};

const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_OFF}
);
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GOLD}
);
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_GREEN}
);
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_RED}
);

const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_GOLD}
);
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_GOLD}
);
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 2, HSV_GOLD}
);


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_layer0_layer,
    my_layer1_layer,
    my_layer2_layer,
    my_layer3_layer,
    my_layer4_layer,
    my_layer5_layer,
    my_layer6_layer
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(4, led_state.caps_lock);
    rgblight_set_layer_state(5, led_state.scroll_lock);
    rgblight_set_layer_state(6, led_state.caps_lock & led_state.scroll_lock);
    return true;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _FN1));
    rgblight_set_layer_state(2, layer_state_cmp(state, _FN2));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FN3));
    return state;
}
