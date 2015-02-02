//
//  NativeBridge.h
//  SuperLife
//
//  Created by wang haibo on 15/1/27.
//
//

#ifndef __SuperLife__NativeBridge__
#define __SuperLife__NativeBridge__

#include "cocos2d.h"
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
#import "RootViewController.h"
#endif
class NativeBridge : public cocos2d::Ref
{
    NativeBridge();
public:
    static NativeBridge* getInstance();
    virtual ~NativeBridge();
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    void setRootViewController(RootViewController* viewController);
#endif
    void showAdsView();
    void hideAdsView();
    void showRateAppView();
    
    void resetDefaultUserSetting();
private:
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    RootViewController* mViewController;
#endif
    
};


#endif /* defined(__SuperLife__NativeBridge__) */
