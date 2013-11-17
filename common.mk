#Common headers
common_includes := hardware/qcom/display-legacy-caf/libgralloc
common_includes += hardware/qcom/display-legacy-caf/libgenlock
common_includes += hardware/qcom/display-legacy-caf/liboverlay
common_includes += hardware/qcom/display-legacy-caf/libcopybit
common_includes += hardware/qcom/display-legacy-caf/libqdutils

common_header_export_path := qcom/display

ifeq ($(TARGET_USES_POST_PROCESSING),true)
    common_flags     += -DUSES_POST_PROCESSING
    common_includes += $(TARGET_OUT_HEADERS)/pp/inc
endif


#Common libraries external to display HAL
common_libs := liblog libutils libcutils libhardware

#Common C flags
common_flags := -DDEBUG_CALC_FPS -Wno-missing-field-initializers

ifeq ($(ARCH_ARM_HAVE_NEON),true)
    common_flags += -D__ARM_HAVE_NEON
endif

common_deps  :=
kernel_includes :=
#Kernel includes
ifeq ($(call is-vendor-board-platform,QCOM),true)
    # common_deps += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr
    # kernel_includes += $(TARGET_OUT_INTERMEDIATES)/KERNEL_OBJ/usr/include
endif


