# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_MODULE    := libsamplegame
LOCAL_SRC_FILES := 	Game.cpp \
					android.cpp
LOCAL_C_INCLUDES := $(LOCAL_PATH)

LOCAL_LDLIBS    := -llog -lGLESv2 -landroid -lEGL
LOCAL_SHARED_LIBRARIES := libgame

include $(BUILD_SHARED_LIBRARY)

include $(LOCAL_PATH)/../../../jni/Android.mk

$(call import-module,android/native_app_glue)
