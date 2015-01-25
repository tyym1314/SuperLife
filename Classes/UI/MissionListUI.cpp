//
//  MissionListUI.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#include "MissionListUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "GameConst.h"
#include "CommonUtility.h"
#include "EncrytionUtility.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
// 构造函数
MissionListUI::MissionListUI(BaseScene* owner)
{
    m_pOwnerScene = nullptr;
    m_pLabelLevelSelect = nullptr;
    m_pScrollView = nullptr;
    m_pBackBtn = nullptr;
}
// 析构函数
MissionListUI::~MissionListUI()
{
}
// 加载文件
void MissionListUI::loadUI(const std::string& file)
{
#if COCOS2D_DEBUG
    EncrytionUtility::setIntegerForKey("MaxUnlockLevel", MAX_LEVEL);
#endif
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelLevelSelect = Label::createWithTTF(CommonUtility::getLocalString("SelectMission"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelLevelSelect->setPosition(Vec2(480,590));
    m_pLabelLevelSelect->setColor(color);
    m_pLabelLevelSelect->setScale(0.5f);
    this->addChild(m_pLabelLevelSelect);
    
    int ContainerHeight = (MAX_LEVEL/7)*110;
    m_pScrollView = ui::ScrollView::create();
    m_pScrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    m_pScrollView->setContentSize(Size(960,440));
    m_pScrollView->setInnerContainerSize(Size(960,ContainerHeight));
    m_pScrollView->setPosition(Vec2(0,100));
    m_pScrollView->setTouchEnabled(true);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(MissionListUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
    
    for(int i = 1; i <=MAX_LEVEL; i++)
    {
        int k = i%7;
        int j = i/7;
        if(k==0)
        {
            k=7;
            j-=1;
        }
        
        Vec2 pos = Vec2(k*120,ContainerHeight-((j+1)*100-40));
        ui::Button* btn = ui::Button::create("levelBtnLBN.png","levelBtnLBD.png","levelBtnLBN.png");
        btn->setPosition(pos);
        btn->setTitleFontName(CommonUtility::getLocalString("MainFont"));
        btn->setTitleColor(color);
        btn->setTitleFontSize(60);
        btn->setColor(color);
        btn->addTouchEventListener(CC_CALLBACK_2(MissionListUI::pressLevelSelectBtn, this));
        int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
        if( i > maxUnlockLevel)
        {
            btn->setTitleText("?");
            btn->setTouchEnabled(false);
            btn->setOpacity(100);
        }
        else
        {
            Value value = Value(i);
            btn->setTitleText(value.asString());
            btn->setTouchEnabled(true);
            btn->setOpacity(255);
        }
        btn->setTag(i);
        m_pScrollView->addChild(btn);
    }
    this->addChild(m_pScrollView);
}
// 点击任务序号按钮
void MissionListUI::pressLevelSelectBtn(Ref* p,TouchEventType eventType)
{
    if(eventType != TouchEventType::ENDED)
        return;
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    ui::Button* btn = static_cast<ui::Button*>(p);
    if(btn)
    {
        int currentSelectLevel = Value(btn->getTitleText()).asInt();
        EncrytionUtility::setIntegerForKey("CurrentLevel", currentSelectLevel);
        BaseScene* missionScene = SceneFactory::getInstance()->createSceneByID(SCENE_MISSION);
        Director::getInstance()->replaceScene(missionScene);
    }
}
// 点击返回按钮
void MissionListUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}