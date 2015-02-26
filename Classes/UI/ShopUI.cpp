//
//  ShopUI.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#include "ShopUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "GameConst.h"
#include "CommonUtility.h"
#include "SimpleAudioEngine.h"
#include "EncrytionUtility.h"
USING_NS_CC;
using namespace CocosDenshion;
// 构造函数
ShopUI::ShopUI(BaseScene* owner)
{
    m_pOwnerScene = nullptr;
    m_pLabelShop = nullptr;
    m_pLabelStandard = nullptr;
    m_pLabelProfessional = nullptr;
    m_pStandardBtn = nullptr;
    m_pProfessionalBtn = nullptr;
    m_pRestoreBtn = nullptr;
    m_pLabelShopTips = nullptr;
    m_pBackBtn = nullptr;
}
// 析构函数
ShopUI::~ShopUI()
{
}
// 加载文件
void ShopUI::loadUI(const std::string& file)
{
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(ShopUI::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelShop = Label::createWithTTF(CommonUtility::getLocalString("Shop"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelShop->setPosition(Vec2(480,590));
    m_pLabelShop->setColor(color);
    m_pLabelShop->setScale(0.5f);
    this->addChild(m_pLabelShop);
    
    m_pLabelStandard = Label::createWithTTF(CommonUtility::getLocalString("Standard"), CommonUtility::getLocalString("CommonFont"), 60);
    m_pLabelStandard->setPosition(Vec2(350,450));
    m_pLabelStandard->setDimensions(600, 140);
    m_pLabelStandard->setColor(color);
    m_pLabelStandard->setScale(0.5f);
    this->addChild(m_pLabelStandard);
    
    
    m_pLabelProfessional = Label::createWithTTF(CommonUtility::getLocalString("Professional"), CommonUtility::getLocalString("CommonFont"), 60);
    m_pLabelProfessional->setPosition(Vec2(350,300));
    m_pLabelProfessional->setDimensions(600, 200);
    m_pLabelProfessional->setColor(color);
    m_pLabelProfessional->setScale(0.5f);
    this->addChild(m_pLabelProfessional);
    
    m_pStandardBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pStandardBtn->setPosition(Vec2(800,450));
    m_pStandardBtn->addTouchEventListener(CC_CALLBACK_2(ShopUI::pressStandardBtn, this));
    m_pStandardBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pStandardBtn->setTitleColor(color);
    m_pStandardBtn->setTitleFontSize(20);
    m_pStandardBtn->setTitleText(CommonUtility::getLocalString("Purchase"));
    m_pStandardBtn->setColor(color);
    this->addChild(m_pStandardBtn);
    
    m_pProfessionalBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pProfessionalBtn->setPosition(Vec2(800,300));
    m_pProfessionalBtn->addTouchEventListener(CC_CALLBACK_2(ShopUI::pressProfessionalBtn, this));
    m_pProfessionalBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pProfessionalBtn->setTitleColor(color);
    m_pProfessionalBtn->setTitleFontSize(20);
    m_pProfessionalBtn->setTitleText(CommonUtility::getLocalString("Purchase"));
    m_pProfessionalBtn->setColor(color);
    this->addChild(m_pProfessionalBtn);
    
    
    m_pRestoreBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pRestoreBtn->setPosition(Vec2(800,150));
    m_pRestoreBtn->addTouchEventListener(CC_CALLBACK_2(ShopUI::pressRestorelBtn, this));
    m_pRestoreBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pRestoreBtn->setTitleColor(color);
    m_pRestoreBtn->setTitleFontSize(20);
    m_pRestoreBtn->setTitleText(CommonUtility::getLocalString("RestorePurchase"));
    m_pRestoreBtn->setColor(color);
    this->addChild(m_pRestoreBtn);
    
    if(PaymentMgr::getInstance()->getProductList().size()>0)
    {
        m_pLabelShopTips = Label::createWithTTF(CommonUtility::getLocalString("ShopTips"), CommonUtility::getLocalString("CommonFont"), 60);
        m_pStandardBtn->setEnabled(true);
        m_pProfessionalBtn->setEnabled(true);
    }
    else
    {
        m_pLabelShopTips = Label::createWithTTF(CommonUtility::getLocalString("ShopNotOK"), CommonUtility::getLocalString("CommonFont"), 60);
        m_pStandardBtn->setEnabled(false);
        m_pProfessionalBtn->setEnabled(false);
    }
    m_pLabelShopTips->setPosition(Vec2(350,150));
    m_pLabelShopTips->setDimensions(600, 200);
    m_pLabelShopTips->setColor(color);
    m_pLabelShopTips->setScale(0.5f);
    this->addChild(m_pLabelShopTips);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(770,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(ShopUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC
    PaymentMgr::getInstance()->setPayResultListener(this);
#endif
}
// 购买标准版本
void ShopUI::pressStandardBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC
        if(PaymentMgr::getInstance()->getProductList().size()>0)
        {
            SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
            PaymentMgr::getInstance()->payForProduct(PaymentMgr::getInstance()->getProductList()[0]);
        }
#endif
    }

}
// 购买专业完整版本
void ShopUI::pressProfessionalBtn(Ref* p,TouchEventType eventType)
{

    if(eventType == TouchEventType::ENDED)
    {
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC
        if(PaymentMgr::getInstance()->getProductList().size()>0)
        {
            SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
            PaymentMgr::getInstance()->payForProduct(PaymentMgr::getInstance()->getProductList()[1]);
        }
#endif
    }

}
// 恢复购买
void ShopUI::pressRestorelBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC
        if(PaymentMgr::getInstance()->getProductList().size()>0)
        {
            SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
            PaymentMgr::getInstance()->restorePurchase();
        }
#endif
    }
}
// 点击返回按钮
void ShopUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}

void ShopUI::onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
{
#if CC_TARGET_PLATFORM != CC_PLATFORM_MAC
    if(ret == kPaySuccess)
    {
        if(info == PaymentMgr::getInstance()->getProductList()[0])
        {
            SimpleAudioEngine::getInstance()->playEffect("god7.wav");
            EncrytionUtility::setBoolForKey("RemoveAds",true);
            EncrytionUtility::setBoolForKey("UnlockSimpleTemplates", true);
            BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
            Director::getInstance()->replaceScene(mainScene);
        }
        else if(info == PaymentMgr::getInstance()->getProductList()[1])
        {
            SimpleAudioEngine::getInstance()->playEffect("god7.wav");
            EncrytionUtility::setBoolForKey("RemoveAds",true);
            EncrytionUtility::setBoolForKey("UnlockAllTemplates", true);
            EncrytionUtility::setIntegerForKey("MaxUnlockLevel", MAX_LEVEL);
            EncrytionUtility::setBoolForKey("UnlockEditMode", true);
            BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
            Director::getInstance()->replaceScene(mainScene);
        }
        else
            SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
    }
    else if(ret == kPayCancel)
    {
        std::string productId = msg;
        if(productId == "org.wanax.superlife.newproduct1")
        {
            SimpleAudioEngine::getInstance()->playEffect("god7.wav");
            EncrytionUtility::setBoolForKey("RemoveAds",true);
            EncrytionUtility::setBoolForKey("UnlockSimpleTemplates", true);
            BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
            Director::getInstance()->replaceScene(mainScene);
        }
        else if(productId == "org.wanax.superlife.newproduct2")
        {
            SimpleAudioEngine::getInstance()->playEffect("god7.wav");
            EncrytionUtility::setBoolForKey("RemoveAds",true);
            EncrytionUtility::setBoolForKey("UnlockAllTemplates", true);
            EncrytionUtility::setIntegerForKey("MaxUnlockLevel", MAX_LEVEL);
            EncrytionUtility::setBoolForKey("UnlockEditMode", true);
            BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
            Director::getInstance()->replaceScene(mainScene);
        }
        else
            SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
    }
    else
        SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
#endif
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void ShopUI::onRequestProductsResult(ProductsRequestResult ret, TProductList info)
{
    if(ret == RequestSuccees && info.size()>0)
    {
        m_pLabelShopTips->setString(CommonUtility::getLocalString("ShopTips"));
        m_pStandardBtn->setEnabled(true);
        m_pProfessionalBtn->setEnabled(true);
    }
    else
    {
        m_pLabelShopTips->setString(CommonUtility::getLocalString("ShopNotOK"));
        m_pStandardBtn->setEnabled(false);
        m_pProfessionalBtn->setEnabled(false);
    }
}
#endif
void ShopUI::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}