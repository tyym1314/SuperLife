//
//  MenuUI.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#include "MenuUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "CommonUtility.h"
USING_NS_CC;

// 构造函数
MenuUI::MenuUI(BaseScene* owner)
{
    m_pOwnerScene = owner;
    m_pFreeModeBtn = nullptr;
    m_pQuestModeBtn = nullptr;
    m_pHelpBtn  = nullptr;
}
// 析构函数
MenuUI::~MenuUI()
{
}
// 加载文件
void MenuUI::loadUI(const std::string& file)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    auto labelTitle = Label::createWithTTF(CommonUtility::getLocalString("MainTitle"), CommonUtility::getLocalString("MainFont"), 120);
    labelTitle->setColor(color);
    labelTitle->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - labelTitle->getContentSize().height));
    this->addChild(labelTitle);
    
    m_pQuestModeBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pQuestModeBtn->setPosition(Vec2(origin.x + visibleSize.width/2,260));
    m_pQuestModeBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressQuestModeBtn, this));
    m_pQuestModeBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pQuestModeBtn->setTitleColor(color);
    m_pQuestModeBtn->setTitleFontSize(24);
    m_pQuestModeBtn->setTitleText(CommonUtility::getLocalString("MissionMode"));
    m_pQuestModeBtn->setColor(color);
    this->addChild(m_pQuestModeBtn);
    
    m_pFreeModeBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pFreeModeBtn->setPosition(Vec2(origin.x + visibleSize.width/2,180));
    m_pFreeModeBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressFreeModeBtn, this));
    m_pFreeModeBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pFreeModeBtn->setTitleColor(color);
    m_pFreeModeBtn->setTitleFontSize(24);
    m_pFreeModeBtn->setTitleText(CommonUtility::getLocalString("FreeMode"));
    m_pFreeModeBtn->setColor(color);
    this->addChild(m_pFreeModeBtn);
    
    m_pHelpBtn = ui::Button::create("btnLBN.png", "btnLBD.png");
    m_pHelpBtn->setPosition(Vec2(origin.x + visibleSize.width/2,100));
    m_pHelpBtn->addTouchEventListener(CC_CALLBACK_2(MenuUI::pressHelpBtn, this));
    m_pHelpBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pHelpBtn->setTitleColor(color);
    m_pHelpBtn->setTitleFontSize(24);
    m_pHelpBtn->setTitleText(CommonUtility::getLocalString("HelpInfo"));
    m_pHelpBtn->setColor(color);
    this->addChild(m_pHelpBtn);

    //auto labelMadeBy = Label::createWithTTF("Made by Irenicus", CommonUtility::getLocalString("SecondFont"), 10);
    //labelMadeBy->setColor(color);
    //labelMadeBy->setPosition(Vec2(860,10));
    //this->addChild(labelMadeBy);
}
// 点击开始按钮
void MenuUI::pressFreeModeBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MAIN);
        Director::getInstance()->replaceScene(mainScene);
    }
}
// 点击暂停按钮
void MenuUI::pressQuestModeBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* missionListScene = SceneFactory::getInstance()->createSceneByID(SCENE_MISSION_LIST);
        Director::getInstance()->replaceScene(missionListScene);
    }
}
// 点击帮助按钮
void MenuUI::pressHelpBtn(Ref* p,TouchEventType eventType)
{
}