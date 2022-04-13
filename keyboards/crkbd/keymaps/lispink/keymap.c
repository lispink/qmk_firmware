/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation,    either version 2 of the License,    or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not,    see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include <stdio.h>

enum crkbd_layers { _QWERTY, _NUMS, _SPEC, _ADJUST };

enum crkbd_keycodes {
    DT_GAME = SAFE_RANGE, // switch on game mode
    ESC_SFT               // Esc in normal mode left shift in game mode
};

#define C_A_DEL LALT(LCTL(KC_DEL))
#define NUMS MO(_NUMS)
#define SPEC MO(_SPEC)

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        ESC_SFT,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH,  KC_ENT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            KC_LALT,    NUMS,  KC_SPC,    KC_RSFT,    SPEC, KC_RGUI
                                        //`--------------------------'  `--------------------------'
    ),
    [_NUMS] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_ESC,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_DEL, XXXXXXX, KC_HOME, KC_PGDN, KC_PGUP,  KC_END,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, XXXXXXX, _______,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    ),
    [_SPEC] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
         KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_UNDS,  KC_EQL, _______,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
         KC_DEL, KC_LPRN, KC_LCBR, KC_LBRC, KC_LABK, KC_MINS,                      KC_PLUS, KC_RABK, KC_RBRC, KC_RCBR, KC_RPRN,  KC_GRV,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        _______, KC_PIPE, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, KC_LABK, KC_RABK, KC_BSLS, _______,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    ),
    [_ADJUST] = LAYOUT_split_3x6_3(
    //,-----------------------------------------------------.                    ,-----------------------------------------------------.
        C_A_DEL,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, DT_GAME,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LSFT, RGB_HUI, RGB_SAI, RGB_VAI, RGB_TOG,  KC_F11,                       KC_F12, XXXXXXX, XXXXXXX, XXXXXXX, KC_VOLU, KC_PSCR,
    //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
        KC_LCTL, RGB_HUD, RGB_SAD, RGB_VAD, RGB_MOD, NK_TOGG,                      KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, KC_VOLD, KC_RALT,
    //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            _______, _______, _______,    _______, _______, _______
                                        //`--------------------------'  `--------------------------'
    )
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _SPEC, _NUMS, _ADJUST);
}

bool gamemode = false; // used to swap a couple keys for games

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DT_GAME:
            if (record->event.pressed) {
                if (gamemode) {
                    gamemode = false;
                } else {
                    gamemode = true;
                }
            }
            return false;
        case ESC_SFT:
            if (record->event.pressed) {
                if (gamemode) {
                    register_code(KC_LSFT);
                } else {
                    register_code(KC_ESC);
                }
            } else {
                if (gamemode) {
                    unregister_code(KC_LSFT);
                } else {
                    unregister_code(KC_ESC);
                }
            }
            return false;
    }
    // disable homerow keys on number layer in gamemode to prevent unintended keypresses while using WASD and hitting a number
    if (gamemode && IS_LAYER_ON(_NUMS) && record->event.key.row == 1 && record->event.key.col > 0 && record->event.key.col < 6) {
        return false;
    }
    return true;
}
