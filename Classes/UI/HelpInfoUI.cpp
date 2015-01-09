//
//  HelpInfoUI.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#include "HelpInfoUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "GameConst.h"
#include "CommonUtility.h"
USING_NS_CC;

// 构造函数
HelpInfoUI::HelpInfoUI(BaseScene* owner)
{
    m_pOwnerScene = nullptr;
    m_pLabelHelpInfo = nullptr;
    m_pBackBtn = nullptr;
}
// 析构函数
HelpInfoUI::~HelpInfoUI()
{
}
// 加载文件
void HelpInfoUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelHelpInfo = Label::createWithTTF(CommonUtility::getLocalString("HelpInfo"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelHelpInfo->setPosition(Vec2(480,590));
    m_pLabelHelpInfo->setColor(color);
    m_pLabelHelpInfo->setScale(0.5f);
    this->addChild(m_pLabelHelpInfo);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(HelpInfoUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
}
// 点击返回按钮
void HelpInfoUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}