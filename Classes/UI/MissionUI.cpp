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
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;
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
    m_pRetryBtn             = nullptr;
    m_pBackBtn              = nullptr;
}
// 析构函数
MissionUI::~MissionUI()
{
}
// 加载文件
void MissionUI::loadUI(const std::string& file)
{
    m_nCurrentLevel = EncrytionUtility::getIntegerForKey("CurrentLevel");
    int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
    if(m_nCurrentLevel > maxUnlockLevel)
        m_nCurrentLevel = maxUnlockLevel;
    std::string filename = "level";
    filename = filename + Value(m_nCurrentLevel).asString() + ".plist";
    std::string levelName;
    if(!TerrainMgr::getInstance()->loadLevel(filename, levelName, m_nGoalCellNum, m_nGoalCellGeneration, m_nStartLifeNum, m_nLevelType))
        CCLOG("Load level %s failed!", filename.c_str());
    
    m_nLastTotalLifeNum = TerrainMgr::getInstance()->getLifeNum();
    
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
    
    std::string strMission = String::createWithFormat(CommonUtility::getLocalString("Mission").c_str(), m_nCurrentLevel, levelName.c_str())->getCString();
    m_pLabelMissionName = Label::createWithTTF(strMission, CommonUtility::getLocalString("CommonFont"), 40);
    m_pLabelMissionName->setPosition(Vec2(770,500));
    m_pLabelMissionName->setMaxLineWidth(300);
    m_pLabelMissionName->setColor(color);
    m_pLabelMissionName->setScale(0.4f);
    this->addChild(m_pLabelMissionName);
    
    std::string strMissionGoal;
    if (m_nLevelType == 0)
        strMissionGoal= String::createWithFormat(CommonUtility::getLocalString("MissionGoal0").c_str(), m_nGoalCellGeneration, m_nGoalCellNum)->getCString();
    else if(m_nLevelType == 1)
        strMissionGoal= String::createWithFormat(CommonUtility::getLocalString("MissionGoal1").c_str(), m_nGoalCellGeneration, m_nGoalCellNum)->getCString();
    else if (m_nLevelType == 2)
        strMissionGoal= String::createWithFormat(CommonUtility::getLocalString("MissionGoal2").c_str(), m_nGoalCellGeneration, m_nGoalCellNum)->getCString();
    else if(m_nLevelType == 3)
        strMissionGoal= String::createWithFormat(CommonUtility::getLocalString("MissionGoal3").c_str(), m_nGoalCellGeneration, m_nGoalCellNum)->getCString();
    
    m_pLabelMissionGoal = Label::createWithTTF(strMissionGoal, CommonUtility::getLocalString("CommonFont"), 40);
    m_pLabelMissionGoal->setPosition(Vec2(770,450));
    m_pLabelMissionGoal->setMaxLineWidth(300);
    m_pLabelMissionGoal->setColor(color);
    m_pLabelMissionGoal->setScale(0.4f);
    this->addChild(m_pLabelMissionGoal);
    
    std::string strStarterCellNum = String::createWithFormat(CommonUtility::getLocalString("MissionStarterCellNum").c_str(), m_nStartLifeNum)->getCString();
    m_pLabelStarerLifeNum = Label::createWithTTF(strStarterCellNum, CommonUtility::getLocalString("CommonFont"), 40);
    m_pLabelStarerLifeNum->setPosition(Vec2(770,400));
    m_pLabelStarerLifeNum->setMaxLineWidth(300);
    m_pLabelStarerLifeNum->setColor(color);
    m_pLabelStarerLifeNum->setScale(0.4f);
    this->addChild(m_pLabelStarerLifeNum);
    
    int lifeNum = TerrainMgr::getInstance()->getLifeNum();
    int generationNum = TerrainMgr::getInstance()->getGeneration();
    std::string strLifeNum = String::createWithFormat(CommonUtility::getLocalString("LifeNum").c_str(), lifeNum)->getCString();
    std::string strGenerationNum = String::createWithFormat(CommonUtility::getLocalString("GenerationNum").c_str(), generationNum)->getCString();
    
    m_pLabelLifeNum = Label::createWithTTF(strLifeNum, CommonUtility::getLocalString("CommonFont"), 40);
    m_pLabelLifeNum->setPosition(Vec2(700,350));
    m_pLabelLifeNum->setColor(color);
    m_pLabelLifeNum->setScale(0.4f);
    this->addChild(m_pLabelLifeNum);
    
    m_pLabeGenerationNum = Label::createWithTTF(strGenerationNum, CommonUtility::getLocalString("CommonFont"), 40);
    m_pLabeGenerationNum->setPosition(Vec2(840,350));
    m_pLabeGenerationNum->setColor(color);
    m_pLabeGenerationNum->setScale(0.4f);
    this->addChild(m_pLabeGenerationNum);
    
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
    m_pStartBtn->setScale(0.8f);
    m_pStartBtn->setColor(color);
    this->addChild(m_pStartBtn);
    
    m_pNextLevelBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pNextLevelBtn->setPosition(Vec2(770,300));
    m_pNextLevelBtn->addTouchEventListener(CC_CALLBACK_2(MissionUI::pressNextLevelBtn, this));
    m_pNextLevelBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pNextLevelBtn->setTitleColor(color);
    m_pNextLevelBtn->setTitleFontSize(24);
    m_pNextLevelBtn->setTitleText(CommonUtility::getLocalString("NextMission"));
    m_pNextLevelBtn->setScale(0.8f);
    m_pNextLevelBtn->setColor(color);
    m_pNextLevelBtn->setVisible(false);
    this->addChild(m_pNextLevelBtn);
    
    m_pRetryBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pRetryBtn->setPosition(Vec2(770,300));
    m_pRetryBtn->addTouchEventListener(CC_CALLBACK_2(MissionUI::pressRetryBtn, this));
    m_pRetryBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pRetryBtn->setTitleColor(color);
    m_pRetryBtn->setTitleFontSize(24);
    m_pRetryBtn->setTitleText(CommonUtility::getLocalString("Retry"));
    m_pRetryBtn->setScale(0.8f);
    m_pRetryBtn->setColor(color);
    m_pRetryBtn->setVisible(false);
    this->addChild(m_pRetryBtn);
    
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
    int lifeNum = TerrainMgr::getInstance()->getLifeNum();
    if(m_pOwnerScene->IsPaused())
    {
        int diffLifes = lifeNum - m_nLastTotalLifeNum;
        if(diffLifes > 0)
        {
            if(m_nStartLifeNum >= diffLifes)
            {
                m_nStartLifeNum -= diffLifes;
                if(m_nStartLifeNum > 0)
                    TerrainMgr::getInstance()->setEnableAddTerrainCell(true);
                else
                {
                    m_nStartLifeNum = 0;
                    TerrainMgr::getInstance()->setEnableAddTerrainCell(false);
                }
            }
        }
        else if(diffLifes < 0)
        {
            m_nStartLifeNum -= diffLifes;
            TerrainMgr::getInstance()->setEnableAddTerrainCell(true);
        }
    }
    m_nLastTotalLifeNum = lifeNum;
    
    int generationNum = TerrainMgr::getInstance()->getGeneration();
    
    std::string strLifeNum = String::createWithFormat(CommonUtility::getLocalString("LifeNum").c_str(), lifeNum)->getCString();
    std::string strGenerationNum = String::createWithFormat(CommonUtility::getLocalString("GenerationNum").c_str(), generationNum)->getCString();
    
    m_pLabelLifeNum->setString(strLifeNum);
    m_pLabeGenerationNum->setString(strGenerationNum);
    
    std::string strStarterCellNum = String::createWithFormat(CommonUtility::getLocalString("MissionStarterCellNum").c_str(), m_nStartLifeNum)->getCString();
    m_pLabelStarerLifeNum->setString(strStarterCellNum);
    
    checkWin();
}
//设置UI颜色
void MissionUI::setColor(const cocos2d::Color3B& color)
{
    m_pLabelMode->setColor(color);
    m_pPanel1->setColor(color);
    m_pLabelMissionName->setColor(color);
    m_pLabelMissionGoal->setColor(color);
    m_pLabelStarerLifeNum->setColor(color);
    m_pLabelLifeNum->setColor(color);
    m_pLabeGenerationNum->setColor(color);
    m_pControlPanel->setColor(color);
    m_pStartBtn->setTitleColor(color);
    m_pStartBtn->setColor(color);
    m_pNextLevelBtn->setTitleColor(color);
    m_pNextLevelBtn->setColor(color);
    m_pRetryBtn->setTitleColor(color);
    m_pRetryBtn->setColor(color);
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setColor(color);
}
void MissionUI::checkWin()
{
    auto scene = static_cast<MissionScene*>(m_pOwnerScene);
    if(scene)
    {
        if(scene->IsPaused())
            return;
        int lifeNum = TerrainMgr::getInstance()->getLifeNum();
        int generationNum = TerrainMgr::getInstance()->getGeneration();
        if(m_nGoalCellGeneration == generationNum)
        {
            scene->setPause(true);
            if(m_nLevelType == 0)
            {
                if(lifeNum == m_nGoalCellNum)
                {
                    if(m_pStartBtn->isVisible())
                    {
                        m_nCurrentLevel +=1;
                        m_pStartBtn->setVisible(false);
                        m_pRetryBtn->setVisible(false);
                        m_pNextLevelBtn->setVisible(true);
                        SimpleAudioEngine::getInstance()->playEffect("god7.wav");
                    }
                    int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
                    if(m_nCurrentLevel > maxUnlockLevel)
                    {
                        maxUnlockLevel = m_nCurrentLevel;
                        EncrytionUtility::setIntegerForKey("MaxUnlockLevel", maxUnlockLevel);
                    }
                }
                else
                {
                    m_pStartBtn->setVisible(false);
                    m_pRetryBtn->setVisible(true);
                    m_pNextLevelBtn->setVisible(false);
                    SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
                }

            }
            else if(m_nLevelType == 1)
            {
                if(lifeNum >= m_nGoalCellNum)
                {
                    if(m_pStartBtn->isVisible())
                    {
                        m_nCurrentLevel +=1;
                        m_pStartBtn->setVisible(false);
                        m_pRetryBtn->setVisible(false);
                        m_pNextLevelBtn->setVisible(true);
                        SimpleAudioEngine::getInstance()->playEffect("god7.wav");
                    }
                    int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
                    if(m_nCurrentLevel > maxUnlockLevel)
                    {
                        maxUnlockLevel = m_nCurrentLevel;
                        EncrytionUtility::setIntegerForKey("MaxUnlockLevel", maxUnlockLevel);
                    }
                }
                else
                {
                    m_pStartBtn->setVisible(false);
                    m_pRetryBtn->setVisible(true);
                    m_pNextLevelBtn->setVisible(false);
                    SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
                }

            }
            else if(m_nLevelType == 2)
            {
                if(lifeNum <= m_nGoalCellNum)
                {
                    if(m_pStartBtn->isVisible())
                    {
                        m_nCurrentLevel +=1;
                        m_pStartBtn->setVisible(false);
                        m_pRetryBtn->setVisible(false);
                        m_pNextLevelBtn->setVisible(true);
                        SimpleAudioEngine::getInstance()->playEffect("God7.wav");
                    }
                    int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
                    if(m_nCurrentLevel > maxUnlockLevel)
                    {
                        maxUnlockLevel = m_nCurrentLevel;
                        EncrytionUtility::setIntegerForKey("MaxUnlockLevel", maxUnlockLevel);
                    }
                }
                else
                {
                    m_pStartBtn->setVisible(false);
                    m_pRetryBtn->setVisible(true);
                    m_pNextLevelBtn->setVisible(false);
                    SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
                }

            }
            else if(m_nLevelType == 3)
            {
                if(lifeNum == 0)
                {
                    if(m_pStartBtn->isVisible())
                    {
                        m_nCurrentLevel +=1;
                        m_pStartBtn->setVisible(false);
                        m_pRetryBtn->setVisible(false);
                        m_pNextLevelBtn->setVisible(true);
                        SimpleAudioEngine::getInstance()->playEffect("God7.wav");
                    }
                    int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
                    if(m_nCurrentLevel > maxUnlockLevel)
                    {
                        maxUnlockLevel = m_nCurrentLevel;
                        EncrytionUtility::setIntegerForKey("MaxUnlockLevel", maxUnlockLevel);
                    }
                    return;
                }
                else
                {
                    m_pStartBtn->setVisible(false);
                    m_pRetryBtn->setVisible(true);
                    m_pNextLevelBtn->setVisible(false);
                    SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
                    return;
                }
            }
        }
        if(lifeNum == 0)
        {
            scene->setPause(true);
            if(m_nLevelType == 3)
            {
                if(m_pStartBtn->isVisible())
                {
                    m_nCurrentLevel +=1;
                    m_pStartBtn->setVisible(false);
                    m_pRetryBtn->setVisible(false);
                    m_pNextLevelBtn->setVisible(true);
                    SimpleAudioEngine::getInstance()->playEffect("god7.wav");
                }
                int maxUnlockLevel = EncrytionUtility::getIntegerForKey("MaxUnlockLevel", 1);
                if(m_nCurrentLevel > maxUnlockLevel)
                {
                    maxUnlockLevel = m_nCurrentLevel;
                    EncrytionUtility::setIntegerForKey("MaxUnlockLevel", maxUnlockLevel);
                }
            }
            else
            {
                m_pStartBtn->setVisible(false);
                m_pRetryBtn->setVisible(true);
                m_pNextLevelBtn->setVisible(false);
                SimpleAudioEngine::getInstance()->playEffect("Beep_Error01.wav");
            }
        }
    }
}
// 点击开始按钮
void MissionUI::pressStartBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        TerrainMgr::getInstance()->resetScrollView(true);
        auto scene = static_cast<MissionScene*>(m_pOwnerScene);
        if(scene)
        {
            if(scene->IsPaused())
                scene->setPause(false);
            TerrainMgr::getInstance()->setEnableAddTerrainCell(false);
        }
    }
}
// 点击开始按钮
void MissionUI::pressNextLevelBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        if(m_nCurrentLevel <= MAX_LEVEL)
        {
            BaseScene* missionScene = SceneFactory::getInstance()->createSceneByID(SCENE_MISSION);
            Director::getInstance()->replaceScene(missionScene);
            TerrainMgr::getInstance()->setEnableAddTerrainCell(true);
            EncrytionUtility::setIntegerForKey("CurrentLevel", m_nCurrentLevel);
        }
        else
        {
            BaseScene* congratulationsScene = SceneFactory::getInstance()->createSceneByID(SCENE_CONGRATULATIONS);
            Director::getInstance()->replaceScene(congratulationsScene);
        }
    }
}
// 点击重试按钮
void MissionUI::pressRetryBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        BaseScene* missionScene = SceneFactory::getInstance()->createSceneByID(SCENE_MISSION);
        Director::getInstance()->replaceScene(missionScene);
        TerrainMgr::getInstance()->setEnableAddTerrainCell(true);
    }
}
// 点击返回按钮
void MissionUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        BaseScene* menuScene = SceneFactory::getInstance()->createSceneByID(SCENE_MISSION_LIST);
        Director::getInstance()->replaceScene(menuScene);
        TerrainMgr::getInstance()->setEnableAddTerrainCell(true);
    }
}