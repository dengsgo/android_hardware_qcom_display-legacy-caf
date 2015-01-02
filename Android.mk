#Enables the listed display HAL modules
#libs to be built for QCOM targets only

ifeq ($(TARGET_QCOM_DISPLAY_VARIANT),legacy-caf)

ifeq ($(call is-vendor-board-platform,QCOM),true)
display-hals := libgralloc libgenlock libcopybit liblight
display-hals += libhwcomposer liboverlay libqdutils
endif

display-hals += libtilerenderer

include $(call all-named-subdir-makefiles,$(display-hals))

endif
