//
//  EditorUI.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/7.
//
//

#include "EditorUI.h"
#include "EditorScene.h"
#include "UIMgr.h"
#include "SceneFactory.h"
#include "TerrainMgr.h"
#include "SpeedSlider.h"
#include "CommonUtility.h"
#include "MathUtility.h"
#include <regex>
#include "SimpleAudioEngine.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace CocosDenshion;
// 构造函数
EditorUI::EditorUI(BaseScene* owner)
:ui::Layout()
{
    m_pOwnerScene   = owner;
    m_pLabelMode    = nullptr;
    m_pPanel1       = nullptr;
    m_pEditBox      = nullptr;
    m_pSaveBtn      = nullptr;
    m_pResetBtn     = nullptr;
    m_pDeleteBtn    = nullptr;
    m_pBackBtn      = nullptr;
    m_pTableView    = nullptr;
    m_nSelectIndex  = -1;
}
// 析构函数
EditorUI::~EditorUI()
{
}
// 加载文件
void EditorUI::loadUI(const std::string& file)
{
    auto keyboardListener=EventListenerKeyboard::create();
    keyboardListener->onKeyReleased=CC_CALLBACK_2(EditorUI::onKeyReleased,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener,this);
    
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelMode = Label::createWithTTF(CommonUtility::getLocalString("EditorMode"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelMode->setPosition(Vec2(750,590));
    m_pLabelMode->setColor(color);
    m_pLabelMode->setScale(0.4f);
    this->addChild(m_pLabelMode);
    
    m_pPanel1 = Sprite::create("panel1.png");
    m_pPanel1->setPosition(Vec2(750,400));
    m_pPanel1->setColor(color);
    this->addChild(m_pPanel1);
    
    Scale9Sprite* scale9 = Scale9Sprite::create("slider_bar_button.png");
    m_pEditBox = EditBox::create(cocos2d::Size(200,48), scale9);
    m_pEditBox->setPosition(Vec2(750,480));
    m_pEditBox->setPlaceHolder(CommonUtility::getLocalString("TemplateName").c_str());
    m_pEditBox->setPlaceholderFontColor(Color3B::RED);
    m_pEditBox->setFontColor(Color3B::BLACK);
    m_pEditBox->setColor(color);
    this->addChild(m_pEditBox);
    
    m_pSaveBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pSaveBtn->setPosition(Vec2(750,400));
    m_pSaveBtn->addTouchEventListener(CC_CALLBACK_2(EditorUI::pressSaveBtn, this));
    m_pSaveBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pSaveBtn->setTitleColor(color);
    m_pSaveBtn->setTitleFontSize(24);
    m_pSaveBtn->setTitleText(CommonUtility::getLocalString("Save"));
    m_pSaveBtn->setColor(color);
    m_pSaveBtn->setScale(0.6f);
    this->addChild(m_pSaveBtn);
    
    m_pResetBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pResetBtn->setPosition(Vec2(750,350));
    m_pResetBtn->addTouchEventListener(CC_CALLBACK_2(EditorUI::pressResetBtn, this));
    m_pResetBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pResetBtn->setTitleColor(color);
    m_pResetBtn->setTitleFontSize(24);
    m_pResetBtn->setTitleText(CommonUtility::getLocalString("Reset"));
    m_pResetBtn->setColor(color);
    m_pResetBtn->setScale(0.6f);
    this->addChild(m_pResetBtn);
    
    m_pDeleteBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pDeleteBtn->setPosition(Vec2(750,300));
    m_pDeleteBtn->addTouchEventListener(CC_CALLBACK_2(EditorUI::pressDeleteBtn, this));
    m_pDeleteBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pDeleteBtn->setTitleColor(color);
    m_pDeleteBtn->setTitleFontSize(24);
    m_pDeleteBtn->setTitleText(CommonUtility::getLocalString("Delete"));
    m_pDeleteBtn->setColor(color);
    m_pDeleteBtn->setScale(0.6f);
    this->addChild(m_pDeleteBtn);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(EditorUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    this->addChild(m_pBackBtn);
    
    m_pLabelErrorInfo = Label::createWithTTF("", CommonUtility::getLocalString("CommonFont"), 30);
    m_pLabelErrorInfo->setPosition(Vec2(750,180));
    m_pLabelErrorInfo->setMaxLineWidth(350);
    m_pLabelErrorInfo->setColor(color);
    this->addChild(m_pLabelErrorInfo);
    
    m_pTableView = TableView::create(this, cocos2d::Size(540, 64));
    m_pTableView->setDirection(ScrollView::Direction::HORIZONTAL);
    m_pTableView->setPosition(Vec2(40,25));
    m_pTableView->setColor(color);
    m_pTableView->setDelegate(this);
    this->addChild(m_pTableView);
    
    m_pTableView->reloadData();
}
// 更新处理
void EditorUI::update(float delta)
{
    ui::Layout::update(delta);
}
//设置UI颜色
void EditorUI::setColor(const cocos2d::Color3B& color)
{
    m_pLabelMode->setColor(color);
    m_pPanel1->setColor(color);
    m_pEditBox->setColor(color);
    m_pSaveBtn->setTitleColor(color);
    m_pSaveBtn->setColor(color);
    m_pResetBtn->setTitleColor(color);
    m_pResetBtn->setColor(color);
    m_pDeleteBtn->setTitleColor(color);
    m_pDeleteBtn->setColor(color);
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setColor(color);
    m_pTableView->setColor(color);
    m_pTableView->reloadData();
}
cocos2d::Size EditorUI::cellSizeForTable(TableView *table)
{
    return cocos2d::Size(64, 64);
}
TableViewCell* EditorUI::tableCellAtIndex(TableView *table, ssize_t idx)
{
    CCLOG("%zd",idx);
    std::string nameString = TerrainMgr::getInstance()->getTemplateName(idx) + ".png";
    TableViewCell *cell = table->cellAtIndex(idx);
    if (!cell) {
        cell = TableViewCell::create();
        cell->setCascadeColorEnabled(true);
        cell->setColor(table->getColor());
        Sprite *bgSprite = Sprite::create(nameString);
        bgSprite->setScale(0.1f);
        bgSprite->setAnchorPoint(Vec2::ZERO);
        cell->addChild(bgSprite);
    }
    else
    {
        cell->setCascadeColorEnabled(true);
        cell->setColor(table->getColor());
    }
    
    
    return cell;
}
ssize_t EditorUI::numberOfCellsInTableView(TableView *table)
{
    return TerrainMgr::getInstance()->getTemplateCount();
}

void EditorUI::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
    CCLOG("cell touched at index: %zi", cell->getIdx());
    SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
    if(cell->getColor() == Color3B::MAGENTA)
    {
        setColor(Color3B::WHITE);
        m_nSelectIndex = -1;
    }
    else
    {
        if(m_nSelectIndex != -1)
        {
            TableViewCell* lastCell = table->cellAtIndex(m_nSelectIndex);
            if(lastCell)
                lastCell->setColor(Color3B::WHITE);
        }
        cell->setColor(Color3B::MAGENTA);
        m_nSelectIndex = cell->getIdx();
    }
    if(m_nSelectIndex != -1)
    {
        std::string strText = TerrainMgr::getInstance()->getTemplateName(m_nSelectIndex);
        m_pEditBox->setText(strText.c_str());
        TerrainMgr::getInstance()->loadTemplate(strText);
    }
    else
    {
        TerrainMgr::getInstance()->resetTerrain();
        m_pEditBox->setText("");
    }
}

// 点击保存按钮
void EditorUI::pressSaveBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        std::string strText = m_pEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo"));
            return;
        }
        std::regex pattern("[0-9A-Za-z]+");
        if ( !regex_match( strText, pattern ) )
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo2"));
            return;
        }
        
        //截屏后的回调函数
        auto callback = [&](const std::string& fullPath){
            CCLOG("Image saved %s", fullPath.c_str());
            TerrainMgr::getInstance()->getTerrainNode()->setVisible(true);
            TerrainMgr::getInstance()->saveTemplate(m_pEditBox->getText());
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("SaveOK"));
            m_pTableView->reloadData();
        };
        
        //调用Director的截屏功能
#if CC_TARGET_PLATFORM == CC_PLATFORM_MAC
        std::string strDir = "templates/";
        strDir = strDir + strText + ".png";
#else
        std::string strDir = strText + ".png";
#endif
        CommonUtility::renderNodeToFile(strDir, TerrainMgr::getInstance()->getTerrainNode(), Vec2(28,28), callback);
    }
}
// 点击重置按钮
void EditorUI::pressResetBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        TerrainMgr::getInstance()->resetTerrain();
        m_pLabelErrorInfo->setString("");
    }
}
// 点击删除按钮
void EditorUI::pressDeleteBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        std::string strText = m_pEditBox->getText();
        if(strText.empty())
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo3"));
            return;
        }
        if(!TerrainMgr::getInstance()->hasTemplate(strText))
        {
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("ErrorInfo4"));
            return;
        }
        if(m_nSelectIndex != -1)
        {
            strText = TerrainMgr::getInstance()->getTemplateName(m_nSelectIndex);
            TerrainMgr::getInstance()->removeTemplate(strText);
            m_pTableView->reloadData();
            m_pLabelErrorInfo->setString(CommonUtility::getLocalString("DeleteOK"));
            TerrainMgr::getInstance()->resetTerrain();
            m_pEditBox->setText("");
            m_nSelectIndex = -1;
        }
    }
}
// 点击返回按钮
void EditorUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        SceneFactory::getInstance()->setSceneColor(MathUtility::randomColor());
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}
void EditorUI::onKeyReleased(EventKeyboard::KeyCode keyCode, Event *unused_event)
{
    if(keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        SimpleAudioEngine::getInstance()->playEffect("btnclick.wav");
        SceneFactory::getInstance()->setSceneColor(MathUtility::randomColor());
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}