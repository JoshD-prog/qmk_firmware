// Copyright 2022 Shem Sedrick (@ssedrick)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum key_layers {
    _BASE,
    _WINDOWS,
    _RAISE,
    _LOWER,
    _FUNCS,
    _WFUNCS,
    _STR,
    _LEADER,
    _TRANS
};


#define SBASE DF(_BASE)
#define SWIND DF(_WINDOWS)
#define TFUNCS LT(_FUNCS, KC_TAB)
#define EFUNCS LT(_FUNCS, KC_ENT)
#define TWFUNCS LT(_WFUNCS, KC_TAB)
#define EWFUNCS LT(_WFUNCS, KC_ENT)
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

#define WCOPY C(KC_C)
#define WPSTE C(KC_V)
#define WCUT C(KC_C)
#define WSELA C(KC_A)
#define WUNDO C(KC_Z)
#define WREDO C(KC_Y)

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
#define WMUTE C(A(KC_GRV))

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
    TD_DOUBLE_SINGLE_TAP
} td_state_t;

// Create a global instance of the tapdance state typea
static td_state_t rl_state;
static td_state_t ll_state;

// Declare your tapdance functions:

// Function to determine the current tapdance state
td_state_t cur_dance(tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void altlp_finished(tap_dance_state_t *state, void *user_data);
void altlp_reset(tap_dance_state_t *state, void *user_data);
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
    [_WINDOWS] = LAYOUT(
        KC_QUOT, KC_COMM,  KC_DOT, KC_P,   KC_Y,                        KC_F,   KC_G,    KC_C,    KC_R,   KC_L,
        KC_A,    KC_O,    KC_E,    KC_U,   KC_I,                        KC_D,   KC_H,    KC_T,    KC_N,   KC_S,
        KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,                        KC_B,   KC_M,    KC_W,    KC_V,   KC_Z,
                 KC_RALT, KC_TAB,                                                       KC_SLSH, KC_GRV,
                                   SH_ESC, KC_LCTL, TWFUNCS,    KC_BSPC, KC_SPC, KC_LSFT,
                                   KC_LGUI,  RAISE,                      LOWER,  EWFUNCS
    ),
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
        COPY,   PASTE,     CUT,    SELA,     CAX,                 WMUTE,  C_LEFT,  C_DOWN,    C_UP,  C_RGHT,
        UNDO,    REDO,    ____,   KC_F11, KC_F12,               KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
                 ____,   SWIND,                                                    OS_STR,    ____,
                                   ____,    ____, KC_TAB,    ____, ____,    ____,
                                   ____,  QK_RBT,               QK_BOOT,    ____
    ),
    [_WFUNCS] = LAYOUT(
       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                 KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, 
       WCOPY,   WPSTE,    WCUT,   WSELA,     CAX,                 WMUTE,  C_LEFT,  C_DOWN,    C_UP,  C_RGHT,
       WUNDO,   WREDO,    ____,   KC_F11, KC_F12,               KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU,
                CALTD,   SBASE,                                                    OS_STR,    ____,
                                   ____,    ____, KC_TAB,    ____, ____,    ____,
                                   ____,  QK_RBT,               QK_BOOT,    ____
    ),
    [_STR] = LAYOUT(
         PW1,     PW2,     PW3,     PW4,     PW5,                   EM1,     EM2,     EM3,     EM4,     EM5,
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
        ____,    ____,    ____,    ____,    ____,                  ____,    ____,    ____,    ____,    ____,
                 ____,    ____,                                                      ____,    ____,
                                   ____,    ____,  ____,     ____, ____,    ____,
                                   ____,    ____,                  ____,    ____
    ),
    [_LEADER] = LAYOUT(
        HYPR(KC_QUOT), HYPR(KC_1),  HYPR(KC_2), HYPR(KC_P),   HYPR(KC_Y),                        HYPR(KC_F),   HYPR(KC_G),    HYPR(KC_4),    HYPR(KC_R),   HYPR(KC_L),
        HYPR(KC_A),    HYPR(KC_O),    HYPR(KC_E),    HYPR(KC_U),   HYPR(KC_I),                        HYPR(KC_D),   HYPR(KC_H),    HYPR(KC_T),    HYPR(KC_N),   HYPR(KC_S),
        HYPR(KC_SCLN), HYPR(KC_3),    HYPR(KC_J),    HYPR(KC_K),   HYPR(KC_X),                        HYPR(KC_B),   HYPR(KC_M),    HYPR(KC_W),    HYPR(KC_V),   HYPR(KC_Z),
               DM_RSTP,  KC_DEL,                                                    HYPR(KC_SLSH), HYPR(KC_GRV),
                               DM_RSTP,  DM_REC2, DM_REC1,   DM_REC2, DM_REC1,  DM_RSTP,
                                  DM_PLY2, DM_PLY1,                 DM_PLY2,  DM_PLY1
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


#define HSV_RED1          2, 245, 255
#define HSV_RED2          5, 235, 255
#define HSV_RED3          7, 230, 255

#define HSV_BLUE1        170, 200, 255
#define HSV_BLUE2        170, 120, 255
#define HSV_BLUE3        170, 90, 255
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_RED},{4, 8, HSV_BLUE});
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_GREEN});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_RED1},{4, 8, HSV_RED});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 4, HSV_BLUE},{4, 8, HSV_BLUE1});
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_RED3},{1, 2, HSV_RED2},{2, 3, HSV_RED1},{3, 4, HSV_RED},{4, 5, HSV_BLUE3},{5, 6, HSV_BLUE2},{6, 7, HSV_BLUE1},{7, 8, HSV_BLUE});
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_BLACK});
const rgblight_segment_t PROGMEM my_layer6_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_CORAL});
const rgblight_segment_t PROGMEM my_layer7_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 8, HSV_GOLD});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_layer0_layer, my_layer1_layer, my_layer2_layer, my_layer3_layer, my_layer4_layer, my_layer5_layer, my_layer6_layer, my_layer7_layer);

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
    rgblight_set_layer_state(1, layer_state_cmp(state, _WINDOWS));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(4, layer_state_cmp(state, _FUNCS));
    rgblight_set_layer_state(5, layer_state_cmp(state, _STR));   
    rgblight_set_layer_state(6, layer_state_cmp(state, _LEADER));   
    rgblight_set_layer_state(7, layer_state_cmp(state, _WFUNCS));
    return state;
}


// Determine the tapdance state to return
td_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    }

    if (state->count == 2) return TD_DOUBLE_SINGLE_TAP;
    else return TD_UNKNOWN; // Any number higher than the maximum state value you return above
}

// Handle the possible states for each tapdance keycode you define:

// Functions that control what our tap dance key does
void rl_finished(tap_dance_state_t *state, void *user_data) {
    rl_state = cur_dance(state);
    switch (rl_state) {
        case TD_SINGLE_TAP:
            layer_on(_RAISE);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_RAISE);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_RAISE)) {
                // If already set, then switch it off
                layer_off(_RAISE);
            } else {
                // If not already set, then switch the layer on
                layer_on(_RAISE);
            }
            set_oneshot_layer(_LEADER, ONESHOT_START);
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
            layer_on(_LOWER);
            break;
        case TD_SINGLE_HOLD:
            layer_on(_LOWER);
            break;
        case TD_DOUBLE_SINGLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(_LOWER)) {
                // If already set, then switch it off
                layer_off(_LOWER);
            } else {
                // If not already set, then switch the layer on
                layer_on(_LOWER);
            }
            set_oneshot_layer(_LEADER, ONESHOT_START);
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
 