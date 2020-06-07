/* Copyright 2019 T.Shinohara
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

enum layer {
  QWERTY = 0,
  FUNC,
  NUM,
  CURSOL
};

enum {
  X_TAP_DANCE_1 = 0,
  X_TAP_DANCE_2,
};

#define L_ALT LT(CURSOL, KC_LALT)
#define L_TAB LT(FUNC, KC_TAB)
#define TAP_SFT TD(X_TAP_DANCE_1)
#define TAP_SPC TD(X_TAP_DANCE_2)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [QWERTY] = LAYOUT(
    KC_ESC,  KC_MINS, KC_EQL,  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
             KC_LANG1,KC_LBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSPC,
             KC_LANG2,KC_RBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
             L_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             L_ALT,
             KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,             KC_LGUI,
             TAP_SPC, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             TAP_SFT
  ),
  [FUNC] = LAYOUT(
    _______, KC_MINS, KC_EQL,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             _______, KC_LPRN, KC_EXLM, KC_AT,   KC_HASH, XXXXXXX, XXXXXXX, _______,
             _______, KC_RPRN, KC_DLR,  KC_PERC, KC_GRV,  XXXXXXX, XXXXXXX, _______,
             _______, KC_CIRC, KC_AMPR, KC_ASTR, XXXXXXX, XXXXXXX,          XXXXXXX,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______
  ),
  [NUM] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______,
             _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
             _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,             XXXXXXX,
             _______, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,             _______,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______
  ),
  [CURSOL] = LAYOUT(
    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
             _______, KC_PGDN, KC_UP,   KC_PGUP, XXXXXXX, XXXXXXX,          XXXXXXX,
             _______, KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, XXXXXXX,          _______,
             _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          _______
  )
};

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (!state->pressed) return SINGLE_TAP;
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    return DOUBLE_TAP;
  }
  else return 6; //magic number. At some point this method will expand to work for more presses
}

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap xtap_state_1 = {
  .is_press_action = true,
  .state = 0
};

void x_finished_1 (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state_1.state = cur_dance(state);
  switch (xtap_state_1.state) {
    case SINGLE_TAP:
      if (IS_LAYER_ON(NUM)){
        layer_off(NUM);
      } else {
        register_code(KC_LSFT);
      }
      break;
    case SINGLE_HOLD:
      register_code(KC_LSFT);
      break;
    case DOUBLE_TAP:
      layer_invert(NUM);
      break;
  }
}

void x_reset_1 (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state_1.state) {
    case SINGLE_TAP:
      unregister_code(KC_LSFT);
      break;
    case SINGLE_HOLD:
      layer_off(NUM);
      break;
    case DOUBLE_TAP:
      break;
  }
  xtap_state_1.state = 0;
}

static tap xtap_state_2 = {
  .is_press_action = true,
  .state = 0
};

void x_finished_2 (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state_2.state = cur_dance(state);
  switch (xtap_state_2.state) {
    case SINGLE_TAP:
      if (IS_LAYER_ON(CURSOL)){
        // register_code(KC_SPC);
        layer_off(CURSOL);
      } else {
        register_code(KC_SPC);
      }
      break;
    case SINGLE_HOLD:
      layer_on(CURSOL);
      break;
    case DOUBLE_TAP:
      layer_invert(CURSOL);
      break;
  }
}

void x_reset_2 (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state_2.state) {
    case SINGLE_TAP:
      unregister_code(KC_SPC);
      break;
    case SINGLE_HOLD:
      layer_off(CURSOL);
      break;
    case DOUBLE_TAP:
      break;
  }
  xtap_state_2.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
 [X_TAP_DANCE_1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_1, x_reset_1),
 [X_TAP_DANCE_2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished_2, x_reset_2),
};