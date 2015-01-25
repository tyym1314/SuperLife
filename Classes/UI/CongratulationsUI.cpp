//
//  CongratulationsUI.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/20.
//
//

#include "CongratulationsUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "GameConst.h"
#include "CommonUtility.h"
#include "EncrytionUtility.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
// 构造函数
CongratulationsUI::CongratulationsUI(BaseScene* owner)
{
    m_pOwnerScene = nullptr;
    m_pLabelCongratulations = nullptr;
    m_pBackBtn = nullptr;
}
// 析构函数
CongratulationsUI::~CongratulationsUI()
{
}
// 加载文件
void CongratulationsUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelCongratulations = Label::createWithTTF(CommonUtility::getLocalString("Congratulations"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelCongratulations->setPosition(Vec2(480,500));
    m_pLabelCongratulations->setColor(color);
    m_pLabelCongratulations->setScale(0.5f);
    this->addChild(m_pLabelCongratulations);
    
    m_pLabelDetail = Label::createWithTTF(CommonUtility::getLocalString("CongratulationsDetail"), CommonUtility::getLocalString("MainFont"), 40);
    m_pLabelDetail->setPosition(Vec2(480,350));
    m_pLabelDetail->setColor(color);
    m_pLabelDetail->setDimensions(600, 200);
    m_pLabelDetail->setScale(0.5f);
    this->addChild(m_pLabelDetail);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(CongratulationsUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
}
// 点击返回按钮
void CongratulationsUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}