include $(KEYBOARD_PATH_1)/keymaps/$(KEYMAP)/qmk-vim/rules.mk

VIA_ENABLE = no

COMBO_ENABLE = yes
COMMAND_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RAW_ENABLE = no
CONSOLE_ENABLE = yes
MOUSEKEY_ENABLE = yes
DYNAMIC_MACRO_ENABLE = yes

WPM_ENABLE = no

RGB_MATRIX_LEDMAPS = yes

SRC += utils.c
SRC += timepants.c
SRC += process_record.c
SRC += encoder.c

ifeq ($(strip $(WPM_ENABLE)), yes)
	SRC += fun.c
endif

ifeq ($(strip $(RGB_MATRIX_LEDMAPS)), yes)
	SRC += rgb_matrix_ledmaps.c
	OPT_DEFS += -DRGB_MATRIX_LEDMAPS_ENABLED
endif
