#
#  local_features.mk contains post-processing rules for the Helix keyboard.
#
#   Post-processing rules convert keyboard-specific shortcuts (that represent
#   combinations of standard options) into QMK standard options.
#

define HELIX_CUSTOMISE_MSG
  $(info Helix Spacific Build Options)
  $(info -  LED_BACK_ENABLE      = $(LED_BACK_ENABLE))
  $(info -  LED_ANIMATION        = $(LED_ANIMATIONS))
  $(info -  IOS_DEVICE_ENABLE    = $(IOS_DEVICE_ENABLE))
  $(info )
endef

  ifneq ($(strip $(HELIX)),)
    ### Helix keyboard keymap: convenient command line option
    ##    make HELIX=<options> helix:<keymap>
    ##    option= oled | back | under | na | ios
    ##    ex.
    ##      make HELIX=oled          helix:<keymap>
    ##      make HELIX=oled,back     helix:<keymap>
    ##      make HELIX=oled,back,na  helix:<keymap>
    ##      make HELIX=oled,back,ios helix:<keymap>
    ##
    ifeq ($(findstring back,$(HELIX)), back)
      LED_BACK_ENABLE = yes
    endif
    ifeq ($(findstring na,$(HELIX)), na)
      LED_ANIMATIONS = no
    endif
    ifeq ($(findstring no_ani,$(HELIX)), no_ani)
      LED_ANIMATIONS = no
    endif
    ifeq ($(findstring ios,$(HELIX)), ios)
      IOS_DEVICE_ENABLE = yes
    endif
    ifeq ($(findstring verbose,$(HELIX)), verbose)
       SHOW_VERBOSE_INFO = yes
    endif
    SHOW_HELIX_OPTIONS = yes
  endif

########
# convert Helix-specific options (that represent combinations of standard options)
#   into QMK standard options.

ifeq ($(strip $(LED_BACK_ENABLE)), yes)
  RGBLIGHT_ENABLE = yes
  OPT_DEFS += -DRGBLED_BACK
endif

ifeq ($(strip $(IOS_DEVICE_ENABLE)), yes)
    OPT_DEFS += -DIOS_DEVICE_ENABLE
endif

ifeq ($(strip $(LED_ANIMATIONS)), yes)
    OPT_DEFS += -DLED_ANIMATIONS
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

ifneq ($(strip $(SHOW_HELIX_OPTIONS)),)
  $(eval $(call HELIX_CUSTOMISE_MSG))
  ifneq ($(strip $(SHOW_VERBOSE_INFO)),)
     $(info -- RGBLIGHT_ENABLE = $(RGBLIGHT_ENABLE))
     $(info -- OPT_DEFS        = $(OPT_DEFS))
     $(info -- LINK_TIME_OPTIMIZATION_ENABLE = $(LINK_TIME_OPTIMIZATION_ENABLE))
     $(info )
  endif
endif
