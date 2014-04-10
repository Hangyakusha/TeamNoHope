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
LOCAL_MODULE := openal
LOCAL_SRC_FILES := ../libs/libopenal.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := libsndfile
LOCAL_SRC_FILES := ../libs/libsndfile.so
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)
#APP_STL		:= stlport_shared
LOCAL_MODULE    := libgame
LOCAL_CFLAGS    := -Werror
LOCAL_SRC_FILES := Android.cpp\
					Graphics.cpp \
					Game.cpp\
					SpriteEntity.cpp\
					Shader.cpp\
					Texture.cpp \
					UtilAndroid.cpp \
					VertexData.cpp \
					IndexData.cpp \
					Entity.cpp \
					Color.cpp \
					Input.cpp \
					RenderTexture.cpp \
					math/Vec2.cpp \
					math/Vec3.cpp \
					math/Mat3.cpp \
					math/Mat4.cpp \
					math/Vec4.cpp \
					SoundManager.cpp \
					Sound.cpp \
					Mesh.cpp \
					ObjLoader.cpp \
					FileReader.cpp \
					Camera.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)
LOCAL_LDLIBS    := -llog -lGLESv2 -landroid -lOpenSLES -lEGL
LOCAL_STATIC_LIBRARIES := android_native_app_glue
LOCAL_SHARED_LIBRARIES := libopenal libsndfile

include $(BUILD_SHARED_LIBRARY)

$(call import-module,android/native_app_glue)
