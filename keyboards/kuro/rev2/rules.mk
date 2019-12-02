KEYBOARD_LOCAL_FEATURES_MK := $(dir $(lastword $(MAKEFILE_LIST)))local_features.mk

SRC += local_drivers/i2c.c
SRC += local_drivers/serial.c
SRC += local_drivers/ssd1306.c
KEYBOARD_PATHS += $(KURO_TOP_DIR)/local_drivers

CUSTOM_MATRIX = yes

SRC += rev2/matrix.c
SRC += rev2/split_util.c
SRC += rev2/split_scomm.c

# Helix Spacific Build Options default values
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_ANIMATIONS = yes        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
