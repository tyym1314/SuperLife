LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

LOCAL_DEFAULT_CPP_EXTENSION := cpp

SOURCE_FILES := hellocpp/main.cpp \
                   ../../Classes/*.cpp \
                   ../../Classes/Const/*.cpp \
                   ../../Classes/Data/*.cpp \
                   ../../Classes/GameLayers/*.cpp \
                   ../../Classes/GameScenes/*.cpp \
                   ../../Classes/Payment/*.cpp \
                   ../../Classes/Terrain/*.cpp \
                   ../../Classes/UI/*.cpp \
                   ../../Classes/Utilities/*.cpp

LOCAL_SRC_FILES := 	$(foreach F, $(SOURCE_FILES), $(addprefix $(dir $(F)),$(notdir $(wildcard $(LOCAL_PATH)/$(F)))))

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes \
					$(LOCAL_PATH)/../../Classes/Const \
					$(LOCAL_PATH)/../../Classes/Data \
					$(LOCAL_PATH)/../../Classes/GameLayers \
					$(LOCAL_PATH)/../../Classes/GameScenes \
					$(LOCAL_PATH)/../../Classes/Payment \
					$(LOCAL_PATH)/../../Classes/Terrain \
					$(LOCAL_PATH)/../../Classes/UI \
					$(LOCAL_PATH)/../../Classes/Utilities		

LOCAL_WHOLE_STATIC_LIBRARIES := cocos2dx_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocosdenshion_static

# LOCAL_WHOLE_STATIC_LIBRARIES += box2d_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocosbuilder_static
# LOCAL_WHOLE_STATIC_LIBRARIES += spine_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocostudio_static
# LOCAL_WHOLE_STATIC_LIBRARIES += cocos_network_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_ui_static
LOCAL_WHOLE_STATIC_LIBRARIES += cocos_extension_static


include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)
$(call import-module,audio/android)

# $(call import-module,Box2D)
# $(call import-module,editor-support/cocosbuilder)
# $(call import-module,editor-support/spine)
# $(call import-module,editor-support/cocostudio)
# $(call import-module,network)
$(call import-module,ui)
$(call import-module,extensions)
