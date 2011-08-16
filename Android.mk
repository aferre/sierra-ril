## Infineon X-Gold RIL
##
## Copyright (C) 2009, Texas Instruments
## Copyright 2006, The Android Open Source Project
##
## Licensed under the Apache License, Version 2.0 (the "License");
## you may not use this file except in compliance with the License.
## You may obtain a copy of the License at
##
##     http://www.apache.org/licenses/LICENSE-2.0
##
## Unless required by applicable law or agreed to in writing, software
## distributed under the License is distributed on an "AS IS" BASIS,
## WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
## See the License for the specific language governing permissions and
## limitations under the License.
## 
## Based on reference-ril by - Copyright 2006, The Android Open Source Project
## Modified September 2009 by Texas Instruments
##

# XXX using libutils for simulator build only...
#

LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    xgold-ril.c \
    atchannel.c \
    misc.c \
    at_tok.c

LOCAL_SHARED_LIBRARIES := \
    libcutils libutils libril

# for asprinf
LOCAL_CFLAGS := -D_GNU_SOURCE

LOCAL_C_INCLUDES := $(KERNEL_HEADERS)

ifeq (foo,foo)
  #build shared library
  LOCAL_SHARED_LIBRARIES += \
      libcutils libutils
  LOCAL_LDLIBS += -lpthread
  LOCAL_CFLAGS += -DRIL_SHLIB
  LOCAL_PRELINK_MODULE := false
  LOCAL_MODULE:= libreference-ril
  include $(BUILD_SHARED_LIBRARY)
else
  #build executable
  LOCAL_SHARED_LIBRARIES += \
      libril
  LOCAL_MODULE:= reference-ril
  include $(BUILD_EXECUTABLE)
endif
