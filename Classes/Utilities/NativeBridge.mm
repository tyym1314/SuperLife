//
//  NativeBridge.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/27.
//
//

#include "NativeBridge.h"
#include "EncrytionUtility.h"
USING_NS_CC;
static NativeBridge *s_NativeBridge = nullptr;
NativeBridge::NativeBridge()
{
}
NativeBridge* NativeBridge::getInstance()
{
    if (! s_NativeBridge)
    {
        s_NativeBridge = new NativeBridge();
    }
    
    return s_NativeBridge;
}
NativeBridge::~NativeBridge()
{
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void NativeBridge::setRootViewController(RootViewController* viewController)
{
    mViewController = viewController;
}
#endif
void NativeBridge::showAdsView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    if (!EncrytionUtility::getBoolForKey("RemoveAds",false)) {
        CCLOG("showAdsView");
        //return;
        if(mViewController != nil)
            [mViewController showAdsView];
    }
#endif
}
void NativeBridge::hideAdsView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("hideAdsView");
    if(mViewController != nil)
        [mViewController hideAdsView];
#endif
}
void NativeBridge::showRateAppView()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    CCLOG("showRateAppView");
    if(mViewController != nil)
    {
        LanguageType lt= CCApplication::getInstance()->getCurrentLanguage();
        switch (lt) {
            case LanguageType::CHINESE:
                [mViewController showRateAppViewCH];
                break;
                
            default:
                [mViewController showRateAppViewEN];
                break;
        }
    }
#endif
}
void NativeBridge::resetDefaultUserSetting()
{
    EncrytionUtility::setBoolForKey("RemoveAds",false);
    EncrytionUtility::setBoolForKey("UnlockSimpleTemplates", false);
    EncrytionUtility::setBoolForKey("UnlockAllTemplates", false);
    EncrytionUtility::setIntegerForKey("MaxUnlockLevel", 1);
    EncrytionUtility::setBoolForKey("UnlockEditMode", false);
}