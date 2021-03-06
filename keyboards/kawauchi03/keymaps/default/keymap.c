/* Copyright 2020 T.Shinohara
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

// // Defines names for use in layer keycodes and the keymap
// enum layer_names {
//     _BASE,
//     _FN
// };

// // Defines the keycodes used by our macros in process_record_user
// enum custom_keycodes {
//     QMKBEST = SAFE_RANGE,
//     QMKURL
// };


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(
    KC_MINS, KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,         KC_BSLS,
    KC_LALT, KC_LBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,      KC_BSPC,
    KC_LGUI, KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,      KC_ENT,
    KC_ESC,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             KC_SPC,
             KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LSFT,
             KC_SPC,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             KC_LCTL
  )
};

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     switch (keycode) {
//         case QMKBEST:
//             if (record->event.pressed) {
//                 // when keycode QMKBEST is pressed
//                 SEND_STRING("QMK is the best thing ever!");
//             } else {
//                 // when keycode QMKBEST is released
//             }
//             break;
//         case QMKURL:
//             if (record->event.pressed) {
//                 // when keycode QMKURL is pressed
//                 SEND_STRING("https://qmk.fm/\n");
//             } else {
//                 // when keycode QMKURL is released
//             }
//             break;
//     }
//     return true;
// }

// /*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/
