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
USING_NS_CC;
using namespace CocosDenshion;
// 构造函数
ShopUI::ShopUI(BaseScene* owner)
{
    m_pOwnerScene = nullptr;
    m_pLabelShop = nullptr;
    m_pBackBtn = nullptr;
}
// 析构函数
ShopUI::~ShopUI()
{
}
// 加载文件
void ShopUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelShop = Label::createWithTTF(CommonUtility::getLocalString("Shop"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelShop->setPosition(Vec2(480,590));
    m_pLabelShop->setColor(color);
    m_pLabelShop->setScale(0.5f);
    this->addChild(m_pLabelShop);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(ShopUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
}
// 点击删除广告按钮
void ShopUI::pressRemoveAdsViewBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    }
}
// 点击解锁全部模版按钮
void ShopUI::pressUnlockAllTemplatesBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    }
}
// 点击解锁编辑模式按钮
void ShopUI::pressUnlockEditorModeBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
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