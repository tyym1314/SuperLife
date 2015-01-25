//
//  EditLevelUI.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/14.
//
//

#include "EditLevelUI.h"
#include "MainScene.h"
#include "UIMgr.h"
#include "SceneFactory.h"
#include "TerrainMgr.h"
#include "SpeedSlider.h"
#include "ControlPanel.h"
#include "CommonUtility.h"
#include "MathUtility.h"
#include <regex>
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
// 构造函数
EditLevelUI::EditLevelUI(BaseScene* owner)
:ui::Layout()
{
    m_pOwnerScene = owner;
    m_pFileNameEditBox = nullptr;
    m_pLevelNameEditBox = nullptr;
    m_pGoalCellNumEditBox = nullptr;
    m_pGoalCellGenerationEditBox = nullptr;
    m_pStarterCellNumEditBox = nullptr;
    m_pLabelMode = nullptr;
    m_pLabelLifeNum = nullptr;
    m_pLabeGenerationNum = nullptr;
    m_pStartBtn = nullptr;
    m_pResetBtn = nullptr;
    m_pRestoreBtn = nullptr;
    m_pSaveBtn = nullptr;
    m_pBackBtn = nullptr;
    m_pLabelErrorInfo = nullptr;
}
// 析构函数
EditLevelUI::~EditLevelUI()
{
}
// 加载文件
void EditLevelUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelMode = Label::createWithTTF(CommonUtility::getLocalString("EditLevelMode"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelMode->setPosition(Vec2(770,590));
    m_pLabelMode->setColor(color);
    m_pLabelMode->setScale(0.5f);
    this->addChild(m_pLabelMode);
    
    Scale9Sprite* scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pFileNameEditBox = EditBox::create(Size(200,25), scale9);
    m_pFileNameEditBox->setPosition(Vec2(750,530));
    m_pFileNameEditBox->setPlaceHolder(CommonUtility::getLocalString("FileName").c_str());
    m_pFileNameEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pFileNameEditBox->setFontColor(Color3B::BLACK);
    m_pFileNameEditBox->setColor(color);
    this->addChild(m_pFileNameEditBox);
    
    scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pLevelNameEditBox = EditBox::create(Size(200,25), scale9);
    m_pLevelNameEditBox->setPosition(Vec2(750,490));
    m_pLevelNameEditBox->setPlaceHolder(CommonUtility::getLocalString("LevelName").c_str());
    m_pLevelNameEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pLevelNameEditBox->setFontColor(Color3B::BLACK);
    m_pLevelNameEditBox->setColor(color);
    this->addChild(m_pLevelNameEditBox);
    
    scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pGoalCellNumEditBox = EditBox::create(Size(200,25), scale9);
    m_pGoalCellNumEditBox->setPosition(Vec2(750,450));
    m_pGoalCellNumEditBox->setPlaceHolder(CommonUtility::getLocalString("GoalCellNum").c_str());
    m_pGoalCellNumEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pGoalCellNumEditBox->setFontColor(Color3B::BLACK);
    m_pGoalCellNumEditBox->setColor(color);
    this->addChild(m_pGoalCellNumEditBox);
    
    scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pGoalCellGenerationEditBox = EditBox::create(Size(200,25), scale9);
    m_pGoalCellGenerationEditBox->setPosition(Vec2(750,410));
    m_pGoalCellGenerationEditBox->setPlaceHolder(CommonUtility::getLocalString("GoalCellGeneration").c_str());
    m_pGoalCellGenerationEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pGoalCellGenerationEditBox->setFontColor(Color3B::BLACK);
    m_pGoalCellGenerationEditBox->setColor(color);
    this->addChild(m_pGoalCellGenerationEditBox);
    
    scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pStarterCellNumEditBox = EditBox::create(Size(200,25), scale9);
    m_pStarterCellNumEditBox->setPosition(Vec2(750,370));
    m_pStarterCellNumEditBox->setPlaceHolder(CommonUtility::getLocalString("StarterCellNum").c_str());
    m_pStarterCellNumEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pStarterCellNumEditBox->setFontColor(Color3B::BLACK);
    m_pStarterCellNumEditBox->setColor(color);
    this->addChild(m_pStarterCellNumEditBox);
    
    scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pLevelTypeEditBox = EditBox::create(Size(200,25), scale9);
    m_pLevelTypeEditBox->setPosition(Vec2(750,330));
    m_pLevelTypeEditBox->setPlaceHolder(CommonUtility::getLocalString("LevelType").c_str());
    m_pLevelTypeEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pLevelTypeEditBox->setFontColor(Color3B::BLACK);
    m_pLevelTypeEditBox->setColor(color);
    this->addChild(m_pLevelTypeEditBox);
    
    int lifeNum = TerrainMgr::getInstance()->getLifeNum();
    int generationNum = TerrainMgr::getInstance()->getGeneration();
    std::string strLifeNum = String::createWithFormat(CommonUtility::getLocalString("LifeNum").c_str(), lifeNum)->getCString();
    std::string strGenerationNum = String::createWithFormat(CommonUtility::getLocalString("GenerationNum").c_str(), generationNum)->getCString();
    
    m_pLabelLifeNum = Label::createWithTTF(strLifeNum, CommonUtility::getLocalString("CommonFont"), 20);
    m_pLabelLifeNum->setPosition(Vec2(700,280));
    m_pLabelLifeNum->setColor(color);
    this->addChild(m_pLabelLifeNum);
    
    m_pLabeGenerationNum = Label::createWithTTF(strGenerationNum, CommonUtility::getLocalString("CommonFont"), 20);
    m_pLabeGenerationNum->setPosition(Vec2(840,280));
    m_pLabeGenerationNum->setColor(color);
    this->addChild(m_pLabeGenerationNum);
    
    m_pStartBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pStartBtn->setPosition(Vec2(700,230));
    m_pStartBtn->addTouchEventListener(CC_CALLBACK_2(EditLevelUI::pressStartBtn, this));
    m_pStartBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pStartBtn->setTitleColor(color);
    m_pStartBtn->setTitleFontSize(24);
    m_pStartBtn->setTitleText(CommonUtility::getLocalString("Start"));
    m_pStartBtn->setColor(color);
    m_pStartBtn->setScale(0.6f);
    this->addChild(m_pStartBtn);
    
    m_pResetBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pResetBtn->setPosition(Vec2(840,230));
    m_pResetBtn->addTouchEventListener(CC_CALLBACK_2(EditLevelUI::pressResetBtn, this));
    m_pResetBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pResetBtn->setTitleColor(color);
    m_pResetBtn->setTitleFontSize(24);
    m_pResetBtn->setTitleText(CommonUtility::getLocalString("Reset"));
    m_pResetBtn->setColor(color);
    m_pResetBtn->setScale(0.6f);
    this->addChild(m_pResetBtn);
    
    m_pRestoreBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pRestoreBtn->setPosition(Vec2(700,180));
    m_pRestoreBtn->addTouchEventListener(CC_CALLBACK_2(EditLevelUI::pressRestoreBtn, this));
    m_pRestoreBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pRestoreBtn->setTitleColor(color);
    m_pRestoreBtn->setTitleFontSize(24);
    m_pRestoreBtn->setTitleText(CommonUtility::getLocalString("Restore"));
    m_pRestoreBtn->setColor(color);
    m_pRestoreBtn->setScale(0.6f);
    this->addChild(m_pRestoreBtn);
    
    m_pSaveBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pSaveBtn->setPosition(Vec2(840,180));
    m_pSaveBtn->addTouchEventListener(CC_CALLBACK_2(EditLevelUI::pressSaveBtn, this));
    m_pSaveBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pSaveBtn->setTitleColor(color);
    m_pSaveBtn->setTitleFontSize(24);
    m_pSaveBtn->setTitleText(CommonUtility::getLocalString("Save"));
    m_pSaveBtn->setColor(color);
    m_pSaveBtn->setScale(0.6f);
    this->addChild(m_pSaveBtn);
    
    m_pLabelErrorInfo = Label::createWithTTF("", CommonUtility::getLocalString("CommonFont"), 20);
    m_pLabelErrorInfo->setPosition(Vec2(750,130));
    m_pLabelErrorInfo->setMaxLineWidth(250);
    m_pLabelErrorInfo->setColor(color);
    this->addChild(m_pLabelErrorInfo);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(770,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(EditLevelUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
}
// 更新处理
void EditLevelUI::update(float delta)
{
    ui::Layout::update(delta);
    
    int lifeNum = TerrainMgr::getInstance()->getLifeNum();
    int generationNum = TerrainMgr::getInstance()->getGeneration();
    
    std::string strLifeNum = String::createWithFormat(CommonUtility::getLocalString("LifeNum").c_str(), lifeNum)->getCString();
    std::string strGenerationNum = String::createWithFormat(CommonUtility::getLocalString("GenerationNum").c_str(), generationNum)->getCString();
    
    m_pLabelLifeNum->setString(strLifeNum);
    m_pLabeGenerationNum->setString(strGenerationNum);
    
    if(lifeNum == 0)
    {
        m_pOwnerScene->setPause(true);
        m_pStartBtn->setTitleText(CommonUtility::getLocalString("Start"));
    }
}

// 点击开始按钮
void EditLevelUI::pressStartBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        auto scene = static_cast<MainScene*>(m_pOwnerScene);
        if(scene)
        {
            bool pause = scene->IsPaused();
            scene->setPause(!pause);
            if(pause)
            {
                TerrainMgr::getInstance()->cacheTerrainCellList();
                m_pStartBtn->setTitleText(CommonUtility::getLocalString("Pause"));
            }
            else
                m_pStartBtn->setTitleText(CommonUtility::getLocalString("Start"));
        }
    }
}
// 点击重置按钮
void EditLevelUI::pressResetBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        auto scene = static_cast<MainScene*>(m_pOwnerScene);
        if(scene)
        {
            bool pause = scene->IsPaused();
            if(!pause)
            {
                scene->setPause(true);
                m_pStartBtn->setTitleText(CommonUtility::getLocalString("Start"));
            }
            TerrainMgr::getInstance()->resetTerrain();
        }
    }
}
// 点击恢复按钮
void EditLevelUI::pressRestoreBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        auto scene = static_cast<MainScene*>(m_pOwnerScene);
        if(scene)
        {
            TerrainMgr::getInstance()->restoreTerrainCellList();
        }
    }
}
// 点击保存按钮
void EditLevelUI::pressSaveBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        std::string strText = m_pFileNameEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo5"));
            return;
        }
        std::regex pattern("[0-9A-Za-z]+");
        if ( !regex_match( strText, pattern ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo6"));
            return;
        }
        
        strText = m_pLevelNameEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo7"));
            return;
        }
        if ( !regex_match( strText, pattern ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo8"));
            return;
        }
        
        strText = m_pGoalCellNumEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo9"));
            return;
        }
        std::regex pattern1("[0-9]+");
        if ( !regex_match( strText, pattern1 ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo11"));
            return;
        }
        
        strText = m_pGoalCellGenerationEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo10"));
            return;
        }
        if ( !regex_match( strText, pattern1 ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo12"));
            return;
        }
        
        strText = m_pStarterCellNumEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo13"));
            return;
        }
        if ( !regex_match( strText, pattern1 ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo14"));
            return;
        }
        
        strText = m_pLevelTypeEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo15"));
            return;
        }
        if ( !regex_match( strText, pattern1 ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo16"));
            return;
        }
        
        std::string strDir = "levels/";
        int goalCellNum = Value(m_pGoalCellNumEditBox->getText()).asInt();
        int goalCellGeneration = Value(m_pGoalCellGenerationEditBox->getText()).asInt();
        int starterCellNum = Value(m_pStarterCellNumEditBox->getText()).asInt();
        int levelType = Value(m_pLevelTypeEditBox->getText()).asInt();
        
        if(TerrainMgr::getInstance()->saveLevel(strDir + m_pFileNameEditBox->getText() + ".plist", m_pLevelNameEditBox->getText(), goalCellNum, goalCellGeneration, starterCellNum, levelType))
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("SaveOK"));
        else
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("SaveFailed"));
    }
}

// 点击返回按钮
void EditLevelUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        SceneFactory::getInstance()->setSceneColor(MathUtility::randomColor());
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}