// Copyright 2022 Shem Sedrick (@ssedrick)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum key_layers {
    _BASE,
    _RAISE,
    _LOWER,
    _FUNCS,
    _FUNCS_LOWER,
    _STR,
    _LEADER1,
    _LEADER2,
    _LEADER3,
    _TRANS
};

#define TFUNCS LT(_FUNCS_LOWER, KC_TAB)
#define EFUNCS LT(_FUNCS, KC_ENT)
#define OS_STR OSL(_STR)
#define LEADER OSL(_LEADER)

#define CALTD LCA(KC_DEL)

#define COPY G(KC_C)
#define PASTE G(KC_V)
#define HPSTE G(C(KC_V))
#define CUT G(KC_C)
#define SELA G(KC_A)
#define UNDO G(KC_Z)
#define REDO G(S(KC_Z))
#define C_RY TD(CTRL_SPTLGHT)
#define RAISE TD(TD_RAISE)
#define LOWER TD(TD_LOWER)

#define A_UP A(KC_UP)
#define A_DOWN A(KC_DOWN)
#define A_LEFT A(KC_LEFT)
#define A_RGHT A(KC_RGHT)
#define SCRSHT S(C(G(KC_4)))


#define SH_ESC SFT_T(KC_ESC)
#define BK_TAB SFT_T(KC_BSPC)
#define C_UP C(KC_UP)
#define C_DOWN C(KC_DOWN)
#define C_LEFT C(KC_LEFT)
#define C_RGHT C(KC_RGHT)
#define CAX LCA(KC_X)

#define ____ KC_TRNS

enum custom_keycodes {
    PW1 = SAFE_RANGE,
    PW2,
    PW3,
    PW4,
    PW5,
    EM1,
    EM2,
    EM3,
    EM4,
    EM5,
    C_SPT
};

// Tap Dance keycodes
enum td_keycodes {
    CTRL_SPTLGHT, // Our example key: `LALT` when held, `(` when tapped. Add additional keycodes for each tapdance.
    TD_RAISE,
    TD_LOWER
};

// Define a type containing as many tapdance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_SINGLE_TAP,
    TD_TRIPLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state typea
static td_state_t rl_state;
static td_state_t ll_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void rl_finished(tap_dance_state_t *state, void *user_data);
void rl_reset(tap_dance_state_t *state, void *user_data);
void ll_finished(tap_dance_state_t *state, void *user_data);
void ll_reset(tap_dance_state_t *state, void *user_data);



#define TIME_LIMIT 500

uint16_t key_timer; // declare key_timer for use in macro

bool other_key_pressed;


#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#    include "secrets.h"
#else
// `PROGMEM const char secret[][x]` may work better, but it takes up more space in the firmware
// And I'm not familiar enough to know which is better or why...
// static const char *const secrets[] = {"", "\n", "\n", "\n", "", "", "", ""};
#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
            case PW1 ... EM5: // Secrets!  Externally defined strings, not stored in repo
            if (!record->event.pressed) {
                // clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_string_with_delay(secrets[keycode - PW1], MACRO_TIMER);
            }
            return false;
            break;
              // tap for (, hold for (_) (both on release)
            case C_SPT: {
                if (record->event.pressed) {
                key_timer = timer_read();
                other_key_pressed = false;
                register_mods(MOD_BIT(KC_LCTL));
                } else { // Release the key
                unregister_mods(MOD_BIT(KC_LCTL));
                if (timer_elapsed(key_timer) < TAPPING_TERM && !other_key_pressed) {
                    register_code16(G(KC_SPC));
                }
                }
                return false;
                break;
            }
    }
    if (!record->event.pressed) {
        if (keycode != C_SPT) {
            other_key_pressed = true;
        }
        // clear_oneshot_layer_state(ONESHOT_PRESSED);
    }
    return true;
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     [_BASE] = LAYOUT(
        KC_QUOT, KC_COMM,  KC_DOT, KC_P,   KC_Y,                        KC_F,   KC_G,    KC_C,    KC_R,   KC_L,
        KC_A,    KC_O,    KC_E,    KC_U,   KC_I,                        KC_D,   KC_H,    KC_T,    KC_N,   KC_S,
        KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,                        KC_B,   KC_M,    KC_W,    KC_V,   KC_Z,
                 KC_RALT, KC_TAB,                                                       KC_SLSH, KC_GRV,
                                   SH_ESC, KC_LGUI, TFUNCS,    KC_BSPC, KC_SPC, KC_LSFT,
                                   C_SPT,  RAISE,                      LOWER,  EFUNCS
    ), 
    /*
    [_BASE] = LAYOUT(
        KC_Q, KC_W,  KC_E, KC_R,   KC_T,                        KC_Y,   KC_U,    KC_I,    KC_O,   KC_P,
        KC_A,    KC_S,    KC_D,    KC_F,   KC_G,                        KC_H,   KC_J,    KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X,    KC_C,    KC_V,   KC_B,                        KC_N,   KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,
                 KC_RALT, KC_TAB,                                                       KC_QUOT, KC_GRV,
                                   SH_ESC, KC_LGUI, TFUNCS,    KC_BSPC, KC_SPC, KC_LSFT,
                                   C_SPT,  RAISE,                      LOWER,  EFUNCS
     ), */
    [_RAISE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
     S(KC_9), S(KC_0), KC_LBRC, KC_RBRC,  KC_EQL,               KC_MINS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
        ____,  KC_APP, KC_LCBR, KC_RCBR, KC_PLUS,               KC_UNDS, KC_BSLS, KC_PIPE,  KC_APP,    ____,
                 ____,    ____,                                                      ____,    ____,
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),

    [_LOWER] = LAYOUT(
     KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,               KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
     S(KC_9), S(KC_0), KC_LBRC, KC_RBRC,  KC_EQL,               KC_MINS, KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT,
        ____,  KC_APP, KC_LCBR, KC_RCBR, KC_PLUS,               KC_UNDS, KC_BSLS, KC_PIPE,  KC_APP,    ____,
                 ____,    ____,                                                      ____,    ____,
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),
    [_FUNCS] = LAYOUT(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, 
        COPY,   PASTE,     CUT,    SELA,     CAX,               KC_LCTL,  C_LEFT,  C_DOWN,    C_UP,  C_RGHT,
        UNDO,    REDO,    ____,   KC_F11, KC_F12,               KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
                 ____,    KC_DEL,                                                  OS_STR,    ____,
                                   ____,    ____, KC_TAB,    ____, ____,    ____,
                                   ____,  ____,               QK_BOOT,    ____
    ),
    [_FUNCS_LOWER] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,
        COPY,   PASTE,     CUT,    SELA,     CAX,                  ____, MS_LEFT, MS_DOWN,   MS_UP, MS_RGHT,
        UNDO,    REDO,    ____,    KC_F11, KC_F12,                 ____,    ____,    ____,    ____,    ____,
                MS_WHLU,  MS_WHLD,                                               MS_WHLD, MS_WHLU,
                                QK_BOOT,   ____, ____,      MS_ACL0, MS_ACL1, MS_ACL2,
                                   ____,  ____,                 MS_BTN1, MS_BTN2
    ),
    [_STR] = LAYOUT(
         PW1,     PW2,     PW3,     PW4,     PW5,                   EM1,     EM2,     EM3,     EM4,     EM5,
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
                 ____,    ____,                                                      ____,    ____,
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),
    [_LEADER1] = LAYOUT(
        MEH(KC_QUOT), MEH(KC_1),  MEH(KC_2), MEH(KC_P),   MEH(KC_Y),                        MEH(KC_F),   MEH(KC_G),    MEH(KC_4),    MEH(KC_R),   MEH(KC_L),
        MEH(KC_A),    MEH(KC_O),    MEH(KC_E),    MEH(KC_U),   MEH(KC_I),                        MEH(KC_D),   MEH(KC_H),    MEH(KC_T),    MEH(KC_N),   MEH(KC_S),
        MEH(KC_SCLN), MEH(KC_3),    MEH(KC_J),    MEH(KC_K),   MEH(KC_X),                        MEH(KC_B),   MEH(KC_M),    MEH(KC_W),    MEH(KC_V),   MEH(KC_Z),
            MEH(KC_5),  MEH(KC_4),                                                      MEH(KC_SLSH), MEH(KC_GRV),
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),
    [_LEADER2] = LAYOUT(
        HYPR(KC_QUOT), HYPR(KC_1),  HYPR(KC_2), HYPR(KC_P),   HYPR(KC_Y),                        HYPR(KC_F),   HYPR(KC_G),    HYPR(KC_4),    HYPR(KC_R),   HYPR(KC_L),
        HYPR(KC_A),    HYPR(KC_O),    HYPR(KC_E),    HYPR(KC_U),   HYPR(KC_I),                        HYPR(KC_D),   HYPR(KC_H),    HYPR(KC_T),    HYPR(KC_N),   HYPR(KC_S),
        HYPR(KC_SCLN), HYPR(KC_3),    HYPR(KC_J),    HYPR(KC_K),   HYPR(KC_X),                        HYPR(KC_B),   HYPR(KC_M),    HYPR(KC_W),    HYPR(KC_V),   HYPR(KC_Z),
            HYPR(KC_5),  HYPR(KC_4),                                                    HYPR(KC_SLSH), HYPR(KC_GRV),
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),
    [_LEADER3] = LAYOUT(
        HYPR(KC_6),    HYPR(KC_7),    HYPR(KC_8),    HYPR(KC_9),   HYPR(KC_0),                        LCAG(KC_F),   LCAG(KC_G),    LCAG(KC_4),    LCAG(KC_R),   LCAG(KC_L),
        HYPR(KC_MINS), HYPR(KC_EQL),  HYPR(KC_LBRC), HYPR(KC_RBRC),HYPR(KC_BSLS),                     LCAG(KC_D),   LCAG(KC_H),    LCAG(KC_T),    LCAG(KC_N),   LCAG(KC_S),
        LCAG(KC_SCLN), LCAG(KC_3),  LCAG(KC_J),    LCAG(KC_K),   LCAG(KC_X),                        LCAG(KC_B),   LCAG(KC_M),    LCAG(KC_W),    LCAG(KC_V),   LCAG(KC_Z),
            LCAG(KC_5),  LCAG(KC_4),                                                    LCAG(KC_SLSH), LCAG(KC_GRV),
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),
    [_TRANS] = LAYOUT(
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
                 ____,    ____,                                                      ____,    ____,
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    )
};


#define HSV_L0         85, 255, 255
#define HSV_L1         80, 245, 255
#define HSV_L2         80, 235, 255
#define HSV_L3         80, 230, 255

#define HSV_R0         43, 255, 255
#define HSV_R1         40, 245, 255
#define HSV_R2         40, 235, 255
#define HSV_R3         40, 230, 255

const rgblight_segment_t PROGMEM led0[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_L0},{4, 8, HSV_R0});
const rgblight_segment_t PROGMEM led1[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_L0},{4, 8, HSV_L1});
const rgblight_segment_t PROGMEM led2[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_R1},{4, 8, HSV_R0});
const rgblight_segment_t PROGMEM led3[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_L3},{1, 2, HSV_L2},{2, 3, HSV_L1},{3, 4, HSV_L0},{4, 5, HSV_R3},{5, 6, HSV_R2},{6, 7, HSV_R1},{7, 8, HSV_R0});
const rgblight_segment_t PROGMEM led4[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_R3},{1, 2, HSV_R2},{2, 3, HSV_R1},{3, 4, HSV_R0},{4, 5, HSV_L3},{5, 6, HSV_L2},{6, 7, HSV_L1},{7, 8, HSV_L0});
const rgblight_segment_t PROGMEM led5[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLACK});
const rgblight_segment_t PROGMEM led6[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_L0},{1, 4, HSV_BLACK},{4, 5, HSV_R0},{5, 8, HSV_BLACK});
const rgblight_segment_t PROGMEM led7[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_L0},{2, 4, HSV_BLACK},{4, 6, HSV_R0},{6, 8, HSV_BLACK});
const rgblight_segment_t PROGMEM led8[] = RGBLIGHT_LAYER_SEGMENTS({0, 3, HSV_L0},{3, 4, HSV_BLACK},{4, 7, HSV_R0},{7, 8, HSV_BLACK});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(led0, led1, led2, led3, led4, led5, led6, led7, led8);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(3, layer_state_cmp(state, _FUNCS));
    rgblight_set_layer_state(4, layer_state_cmp(state, _FUNCS_LOWER));
    rgblight_set_layer_state(5, layer_state_cmp(state, _STR));   
    rgblight_set_layer_state(6, layer_state_cmp(state, _LEADER1));
    rgblight_set_layer_state(7, layer_state_cmp(state, _LEADER2));    
    rgblight_set_layer_state(8, layer_state_cmp(state, _LEADER3));    
    return state;
}


// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    if (state->count == 3) return TD_TRIPLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

// Functions that control what our tap dance key does
void rl_finished(tap_dance_state_t *state, void *user_data) {
    rl_state = cur_dance(state);
    switch (rl_state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(_LEADER1, ONESHOT_START);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RAISE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            set_oneshot_layer(_LEADER2, ONESHOT_START);
            break;
        case TD_TRIPLE_SINGLE_TAP:
            set_oneshot_layer(_LEADER3, ONESHOT_START);
            break;
        default:
            break;
    }
}

void rl_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    // if (td_state == TD_SINGLE_HOLD || td_state == TD_SINGLE_TAP ) {
        layer_off(_RAISE);
    // }
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    rl_state = TD_NONE;
}

// Functions that control what our tap dance key does
void ll_finished(tap_dance_state_t *state, void *user_data) {
    ll_state = cur_dance(state);
    switch (ll_state) {
        case TD_SINGLE_TAP:
            set_oneshot_layer(_LEADER1, ONESHOT_START);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LOWER);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            set_oneshot_layer(_LEADER2, ONESHOT_START);
            break;
        case TD_TRIPLE_SINGLE_TAP:
            set_oneshot_layer(_LEADER3, ONESHOT_START);
            break;
        default:
            break;
    }
}

void ll_reset(tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    // if (td_state == TD_SINGLE_HOLD || td_state == TD_SINGLE_TAP) {
        layer_off(_LOWER);
    // }
    clear_oneshot_layer_state(ONESHOT_PRESSED);
    ll_state = TD_NONE;
}

// Define `ACTION_TAP_DANCE_FN_ADVANCED()` for each tapdance keycode, passing in `finished` and `reset` functions
tap_dance_action_t tap_dance_actions[] = {
    [TD_RAISE] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, rl_finished, rl_reset),
    [TD_LOWER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ll_finished, ll_reset),
};
 