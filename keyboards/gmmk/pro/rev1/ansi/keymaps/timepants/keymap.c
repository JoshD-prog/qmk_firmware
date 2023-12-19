/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>, Mikael Manukyan <arm.localhost@gmail.com>
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
#include "timepants.h"
#include "qmk-vim/src/vim.h"
void insert_mode_user(void) {
    layer_on(VIM_I);
    layer_off(VIM_N);
    layer_off(VIM_V);
}
void normal_mode_user(void) {
    layer_off(VIM_I);
    layer_on(VIM_N);
    layer_off(VIM_V);
}
void visual_mode_user(void) {
    layer_off(VIM_I);
    layer_off(VIM_N);
    layer_on(VIM_V);
}

const uint16_t PROGMEM jk_combo[] = {KC_J, KC_K, COMBO_END};

combo_t key_combos[] = {
    [JK_ESC] = COMBO(jk_combo, KC_ESC),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right
    // [LINUX] = LAYOUT(
    //     KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  WB_MUTE,          KC_MUTE,
    //     KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC,           KC_DEL,
    //     KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,           PMAC_1,
    //     LT_MSEC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,           KC_ENT,           PMAC_2,
    //     KC_LSFT,          KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             KC_RSFT, KC_UP,   TT_MOUS,
    //     LM_QCTL, LM_QGUI, LM_QALT,                            KC_SPC,                             LM_QALT,   TT_FN, LM_QCTL, KC_LEFT, KC_DOWN, KC_RGHT
    // ),
    [LINUX] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  WB_MUTE,          KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_LBRC, KC_RBRC, KC_BSPC,           KC_DEL,
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, KC_EQL,  KC_BSLS,           PMAC_1,
        LT_MSEC, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS,           KC_ENT,           PMAC_2,
        KC_LSFT,          KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,             KC_RSFT, KC_UP,   TT_MOUS,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT,   TT_FN, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [WINDOWS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [MACOS] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        LM_QGUM, LM_QALM, LM_QCLM,                            _______,                            LM_QGUM, _______, LM_QALM, _______, _______, _______
    ),

    [QWERTY] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______,          _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, _______,          _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          _______,          _______,
        _______,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          _______, _______, _______,
        KC_LCTL, KC_LGUI, KC_LALT,                            _______,                            KC_RALT, _______, KC_RCTL, _______, _______, _______
    ),
    [QWERTYMAC] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MINS, KC_EQL,  _______,          _______,
        _______, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, _______,          _______,
        _______, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          _______,          _______,
        _______,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          _______, _______, _______,
        KC_LGUI, KC_LALT, KC_LCTL,                            _______,                            KC_RGUI, _______, KC_RALT, _______, _______, _______
    ),

    [FUNCTIONS] = LAYOUT(
        _______, KC_SEC1, KC_SEC2, KC_SEC3, KC_SEC4, KC_SEC5, KC_SEC6, KC_SEC7, KC_SEC8, _______, KC_MPRV, KC_MPLY, KC_MNXT, KC_PSCR,          _______,
        _______, KC_LINX, KC_MAC,  KC_WIN,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           KC_INS,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT,          TOG_VIM,
        KC_CAPS, _______, _______, _______, _______, TOG_VIM, TOG_VIM, _______, _______, _______, _______, _______,          _______,          TG_QWEM,
        _______,          KC_RGBH, KC_RGBS, KC_RGBV, KC_RGBE, KC_RGBP, KC_WRGB, _______, _______, _______, _______,          _______, KC_PGUP, TG_QWER,
        _______, _______, _______,                            RGB_TOG,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),
    
    [MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           MAC_ST,
        _______,   MS_LB,    MS_U,   MS_RB, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           SMAC_1,
        _______,    MS_L,    MS_D,    MS_R, TOG_VIM, _______, _______, _______, _______, _______, _______, _______,          _______,           SMAC_2,
        _______,            MS_A0,   MS_A1,   MS_A2, _______, _______, _______, _______, _______, _______, _______,          _______, KC_PGUP, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN,  KC_END
    )
};

#ifdef RGB_MATRIX_LEDMAPS_ENABLED

#define ______ {0, 0, 0}

const ledmap PROGMEM ledmaps[] = {
         //  LU = Left Underglow, RU = Right Underglow
         //  LU_1    ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)  RU_1
         //  LU_2    ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del       RU_2
         //  LU_3    Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp         RU_3
         //  LU_4    Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn         RU_4
         //  LU_5    Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End          RU_5
         //  LU_6    Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right        RU_6
    [LINUX] = RGB_MATRIX_LAYOUT_LEDMAP(
          YELLOW,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    YELLOW,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    ______,
          ______,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    ______,
          YELLOW,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,    YELLOW
    ),
    [WINDOWS] = RGB_MATRIX_LAYOUT_LEDMAP(
            CYAN,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,      CYAN,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    ______,
          ______,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    ______,
            CYAN,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,      CYAN
    ),
    [MACOS] = RGB_MATRIX_LAYOUT_LEDMAP(
          PURPLE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    PURPLE,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    ______,
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    ______,
          ______,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    ______,
          PURPLE,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,    PURPLE
    ),

    [VIM_N] = RGB_MATRIX_LAYOUT_LEDMAP( 
          MAGENT,    MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT,         MAGENT,    MAGENT,
          MAGENT,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    MAGENT,
          MAGENT,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    MAGENT,
          MAGENT,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    MAGENT,
          MAGENT,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    MAGENT,
          MAGENT,    MAGENT, MAGENT, MAGENT,                         MAGENT,                         MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT,    MAGENT
    ),

    [VIM_I] = RGB_MATRIX_LAYOUT_LEDMAP( 
          YELLOW,    MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT,         MAGENT,    MAGENT,
          YELLOW,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    MAGENT,
          YELLOW,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    MAGENT,
          YELLOW,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    MAGENT,
          YELLOW,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    MAGENT,
          YELLOW,    MAGENT, MAGENT, MAGENT,                         MAGENT,                         MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT,    MAGENT
    ),


    [VIM_V] = RGB_MATRIX_LAYOUT_LEDMAP( 
            CYAN,    MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT,         MAGENT,    MAGENT,
            CYAN,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    MAGENT,
            CYAN,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,    MAGENT,
            CYAN,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,    MAGENT,
            CYAN,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,    MAGENT,
            CYAN,    MAGENT, MAGENT, MAGENT,                         MAGENT,                         MAGENT, MAGENT, MAGENT, MAGENT, MAGENT, MAGENT,    MAGENT
    ),

    [QWERTY] = RGB_MATRIX_LAYOUT_LEDMAP(
            BLUE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,      BLUE,
            BLUE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,      BLUE,
            BLUE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,      BLUE,
            BLUE,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,      BLUE,
            BLUE,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,      BLUE,
            BLUE,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,      BLUE
    ),


    [QWERTYMAC] = RGB_MATRIX_LAYOUT_LEDMAP(
             RED,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,       RED,
             RED,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,       RED,
             RED,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,       RED,
             RED,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______,         ______,       RED,
             RED,    ______,         ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         ______, ______, ______,       RED,
             RED,    ______, ______, ______,                         ______,                         ______, ______, ______, ______, ______, ______,       RED
    ),

    [MOUSE] = RGB_MATRIX_LAYOUT_LEDMAP(
          ______,    ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,   PINK,         ______,    ______,
          ______,    ______, ORANGE,  CHART,   TEAL, PURPLE,    RED, ORANGE,  CHART,   TEAL, PURPLE,    RED, ______, ______, ______,            RED,    ______,
          ______,    ______,  CORAL,   CYAN,  CORAL, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______,         MAGENT,    ______,
          ______,    ______,   CYAN,   CYAN,   CYAN, MAGENT, ______, ______, ______, ______, ______, ______, ______,         ______,         ORANGE,    ______,
          ______,    ______,            RED,    RED,    RED, ______, ______, ______, ______, ______, ______, ______,         ______,  CORAL, ______,    ______,
          ______,    ______, ______, ______,                         ______,                         ______, ______, ______,  CORAL,  CORAL,  CORAL,    ______
    ),

    [FUNCTIONS] = RGB_MATRIX_LAYOUT_LEDMAP(
            GOLD,    GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  GREEN,  BLACK,  GREEN,  GREEN,  GREEN,  GREEN,          BLACK,      GOLD,
            GOLD,    BLACK,   GOLD,   GOLD,   GOLD,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,           GOLD,      GOLD,
            GOLD,    BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,    RED,          BLACK,      GOLD,
            GOLD,     TURQ,  BLACK,  BLACK,  BLACK,  BLACK, MAGENT, MAGENT,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,          BLACK,          BLACK,      GOLD,
            GOLD,    BLACK,            RED,    RED,    RED,    RED,    RED,    RED,  BLACK,  BLACK,  BLACK,  BLACK,          BLACK,  BLACK,   GOLD,      GOLD,
            GOLD,    BLACK,  BLACK,   BLUE,                          BLACK,                          BLACK,  BLACK,  BLACK,  BLACK,  BLACK,  BLACK,      GOLD
    ),
};

#endif // RGB_MATRIX_LEDMAPS_ENABLED
// clang-format on
