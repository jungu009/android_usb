LOCAL_PATH := $(call my-dir)

PATH_TO_LIBUSB_SRC := E:/workspace/eclipse_workspace/Usbdemo/jni/libusb-1.0.22


#myusb
include $(CLEAR_VARS)

LOCAL_LDLIBS    := -lm -llog

# libusb dependence
LOCAL_C_INCLUDES += $(LIBUSB_ROOT_ABS)
LOCAL_SHARED_LIBRARIES += libusb1.0

LOCAL_MODULE    := optics
LOCAL_SRC_FILES := main.cpp \
				myusb.c

include $(BUILD_SHARED_LIBRARY)


# libusb 
include $(PATH_TO_LIBUSB_SRC)/android/jni/libusb.mk
