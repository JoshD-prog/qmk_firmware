#include "kb.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    KEYMAP(KC_P7, KC_P8, KC_P9, QK_BOOT, KC_P4, KC_P5, KC_P6, QK_BOOT, KC_P1, KC_P2, KC_P3, QK_BOOT, KC_P0, QK_BOOT, QK_BOOT, QK_BOOT),

    KEYMAP(KC_P7, KC_P8, KC_P9, LT(0, KC_NO), KC_P4, KC_P5, KC_P6, KC_PPLS, KC_P1, KC_P2, KC_P3, KC_PMNS, KC_P0, KC_PAST, KC_PSLS, KC_PENT),

    KEYMAP(QK_BOOT, KC_TRNS, KC_TRNS, KC_NLCK, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
    keyevent_t event = record->event;

    switch (id) {}
    return MACRO_NONE;
}

void matrix_init_user(void) {}

void matrix_scan_user(void) {}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_NUM_LOCK)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_SCROLL_LOCK)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_COMPOSE)) {
    } else {
    }

    if (usb_led & (1 << USB_LED_KANA)) {
    } else {
    }
}