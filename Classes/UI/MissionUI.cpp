//
//  MissionUI.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#include "MissionUI.h"
#include "MissionScene.h"
#include "UIMgr.h"
#include "SceneFactory.h"
#include "TerrainMgr.h"
#include "SpeedSlider.h"
#include "ControlPanel.h"
#include "CommonUtility.h"
#include "EncrytionUtility.h"
USING_NS_CC;
// 构造函数
MissionUI::MissionUI(BaseScene* owner)
:ui::Layout()
{
    m_pOwnerScene           = owner;
    m_pLabelMode            = nullptr;
    m_pLabelMissionName     = nullptr;
    m_pLabelMissionGoal     = nullptr;
    m_pLabelStarerLifeNum   = nullptr;
    m_pPanel1               = nullptr;
    m_pControlPanel         = nullptr;
    m_pStartBtn             = nullptr;
    m_pNextLevelBtn         = nullptr;
    m_pBackBtn              = nullptr;
}
// 析构函数
MissionUI::~MissionUI()
{
}
// 加载文件
void MissionUI::loadUI(const std::string& file)
{
    int currentLevel = EncrytionUtility::getIntegerForKey("CurrentLevel", 1);
    std::string filename = "level";
    filename = filename + Value(currentLevel).asString() + ".plist";
    std::string levelName;
    int goalCellNum;
    int goalCellGeneration;
    if(!TerrainMgr::getInstance()->loadLevel(filename, levelName, goalCellGeneration, goalCellNum, m_nStartLifeNum))
        CCLOG("Load level %s failed!", filename.c_str());
    
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelMode = Label::createWithTTF(CommonUtility::getLocalString("MissionMode"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelMode->setPosition(Vec2(770,590));
    m_pLabelMode->setColor(color);
    m_pLabelMode->setScale(0.4f);
    this->addChild(m_pLabelMode);
    
    m_pPanel1 = Sprite::create("panel1.png");
    m_pPanel1->setPosition(Vec2(770,400));
    m_pPanel1->setColor(color);
    this->addChild(m_pPanel1);
    
    std::string strMission = String::createWithFormat(CommonUtility::getLocalString("Mission").c_str(), currentLevel, levelName.c_str())->getCString();
    m_pLabelMissionName = Label::createWithTTF(strMission, CommonUtility::getLocalString("MainFont"), 40);
    m_pLabelMissionName->setPosition(Vec2(770,500));
    m_pLabelMissionName->setMaxLineWidth(300);
    m_pLabelMissionName->setColor(color);
    m_pLabelMissionName->setScale(0.4f);
    this->addChild(m_pLabelMissionName);
    
    std::string strMissionGoal = String::createWithFormat(CommonUtility::getLocalString("MissionGoal").c_str(), goalCellNum, goalCellGeneration)->getCString();
    m_pLabelMissionGoal = Label::createWithTTF(strMissionGoal, CommonUtility::getLocalString("MainFont"), 40);
    m_pLabelMissionGoal->setPosition(Vec2(770,450));
    m_pLabelMissionGoal->setMaxLineWidth(300);
    m_pLabelMissionGoal->setColor(color);
    m_pLabelMissionGoal->setScale(0.4f);
    this->addChild(m_pLabelMissionGoal);
    
    std::string strStarterCellNum = String::createWithFormat(CommonUtility::getLocalString("MisstionStarterCellNum").c_str(), m_nStartLifeNum)->getCString();
    m_pLabelStarerLifeNum = Label::createWithTTF(strStarterCellNum, CommonUtility::getLocalString("MainFont"), 40);
    m_pLabelStarerLifeNum->setPosition(Vec2(770,400));
    m_pLabelStarerLifeNum->setMaxLineWidth(300);
    m_pLabelStarerLifeNum->setColor(color);
    m_pLabelStarerLifeNum->setScale(0.4f);
    this->addChild(m_pLabelStarerLifeNum);
    
    m_pControlPanel = ControlPanel::create();
    m_pControlPanel->loadUI("");
    m_pControlPanel->setColor(color);
    m_pControlPanel->setPosition(Vec2(770,175));
    this->addChild(m_pControlPanel);
    
    m_pStartBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pStartBtn->setPosition(Vec2(770,300));
    m_pStartBtn->addTouchEventListener(CC_CALLBACK_2(MissionUI::pressStartBtn, this));
    m_pStartBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pStartBtn->setTitleColor(color);
    m_pStartBtn->setTitleFontSize(24);
    m_pStartBtn->setTitleText(CommonUtility::getLocalString("Start"));
    m_pStartBtn->setScale(0.5f);
    m_pStartBtn->setColor(color);
    this->addChild(m_pStartBtn);
    
    m_pNextLevelBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pNextLevelBtn->setPosition(Vec2(770,300));
    m_pNextLevelBtn->addTouchEventListener(CC_CALLBACK_2(MissionUI::pressNextLevelBtn, this));
    m_pNextLevelBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pNextLevelBtn->setTitleColor(color);
    m_pNextLevelBtn->setTitleFontSize(24);
    m_pNextLevelBtn->setTitleText(CommonUtility::getLocalString("NextMission"));
    m_pNextLevelBtn->setScale(0.5f);
    m_pNextLevelBtn->setColor(color);
    m_pNextLevelBtn->setVisible(false);
    this->addChild(m_pNextLevelBtn);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(770,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(MissionUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
}
// 更新处理
void MissionUI::update(float delta)
{
    ui::Layout::update(delta);
}
//设置UI颜色
void MissionUI::setColor(const cocos2d::Color3B& color)
{
    m_pLabelMode->setColor(color);
    m_pPanel1->setColor(color);
    m_pLabelMissionName->setColor(color);
    m_pLabelMissionGoal->setColor(color);
    m_pLabelStarerLifeNum->setColor(color);
    m_pControlPanel->setColor(color);
    m_pStartBtn->setTitleColor(color);
    m_pStartBtn->setColor(color);
    m_pNextLevelBtn->setTitleColor(color);
    m_pNextLevelBtn->setColor(color);
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setColor(color);
}
// 点击开始按钮
void MissionUI::pressStartBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        
    }
}
// 点击开始按钮
void MissionUI::pressNextLevelBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        
    }
}
// 点击返回按钮
void MissionUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}