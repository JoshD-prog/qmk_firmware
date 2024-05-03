#include QMK_KEYBOARD_H

#define _LAYER0 0
#define _LAYER1 1
#define _LAYER2 2
#define _LAYER3 3
#define _LAYER4 4
#define _LAYER5 5

enum custom_keycodes { LAYER0 = SAFE_RANGE, LAYER1, LAYER2, LAYER3, LAYER4, LAYER5 };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_LAYER0] = LAYOUT(
                        C(KC_F), LCA(KC_X), C(KC_GRV), TO(1), 
                        C(KC_S), KC_LPRN, KC_RPRN, TO(2), 
                        C(KC_Z), C(KC_Y), KC_DEL, TO(3), 
                        C(KC_C), C(KC_V), C(KC_A), TO(4)
                        ),

    [_LAYER1] = LAYOUT(QK_BOOT, QK_BOOT, QK_BOOT, TG(1), 
    QK_BOOT, QK_BOOT, QK_BOOT, KC_TRNS,
     QK_BOOT, QK_BOOT, QK_BOOT, KC_TRNS, 
     QK_BOOT, QK_BOOT, QK_BOOT, KC_TRNS),

    [_LAYER2] = LAYOUT(KC_MPRV, KC_MPLY, KC_MNXT, KC_TRNS, 
    KC_VOLD, KC_MUTE, KC_VOLU, TG(2), 
    KC_WBAK, KC_WFWD, KC_WREF, KC_TRNS, 
    KC_WFAV, KC_WSCH, KC_WSTP, KC_TRNS),

    [_LAYER3] = LAYOUT(KC_PGUP, KC_UP, KC_PGDN, KC_TRNS, 
    KC_LEFT, KC_DOWN, KC_RIGHT, KC_TRNS, 
    KC_HOME, C(KC_UP), KC_END, TG(3), 
    C(KC_LEFT), C(KC_DOWN), C(KC_RIGHT), KC_TRNS),

    [_LAYER4] = LAYOUT(KC_P7, KC_P8, KC_P9, KC_TRNS, 
    KC_P4, KC_P5, KC_P6, KC_TRNS, 
    KC_P1, KC_P2, KC_P3, KC_TRNS, 
    KC_P0, MO(5), KC_PENT, TG(4)),

    [_LAYER5] = LAYOUT(KC_LNUM, KC_PSLS, KC_PAST, KC_TRNS, 
    KC_TRNS, KC_PMNS, KC_PPLS, KC_TRNS, 
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, 
    KC_TRNS, KC_NO, KC_PEQL, KC_TRNS)

};
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM my_layer0_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_WHITE});
const rgblight_segment_t PROGMEM my_layer1_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_RED});
const rgblight_segment_t PROGMEM my_layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_YELLOW});
const rgblight_segment_t PROGMEM my_layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_GREEN});
const rgblight_segment_t PROGMEM my_layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_PURPLE});
const rgblight_segment_t PROGMEM my_layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 2, HSV_CYAN});

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(my_layer0_layer, my_layer1_layer, my_layer2_layer, my_layer3_layer, my_layer4_layer, my_layer5_layer);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
}

// bool led_update_user(led_t led_state) {
//     rgblight_set_layer_state(0, led_state.caps_lock);
//     return true;
// }

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LAYER0));
    return state;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, _LAYER1));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LAYER2));
    rgblight_set_layer_state(3, layer_state_cmp(state, _LAYER3));
    rgblight_set_layer_state(4, layer_state_cmp(state, _LAYER4));
    rgblight_set_layer_state(5, layer_state_cmp(state, _LAYER5));
    return state;
}
