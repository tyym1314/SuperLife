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
USING_NS_CC;
// 构造函数
MissionUI::MissionUI(BaseScene* owner)
:ui::Layout()
{
    m_pOwnerScene   = owner;
    m_pLabelMode    = nullptr;
    m_pPanel1       = nullptr;
    m_pControlPanel = nullptr;
    m_pBackBtn      = nullptr;
}
// 析构函数
MissionUI::~MissionUI()
{
}
// 加载文件
void MissionUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    m_pLabelMode = Label::createWithTTF("任务模式", "FZXS12.TTF", 120);
    m_pLabelMode->setPosition(Vec2(750,590));
    m_pLabelMode->setColor(color);
    m_pLabelMode->setScale(0.5f);
    this->addChild(m_pLabelMode);
    
    m_pPanel1 = Sprite::create("panel1.png");
    m_pPanel1->setPosition(Vec2(750,400));
    m_pPanel1->setColor(color);
    this->addChild(m_pPanel1);
    
    m_pControlPanel = ControlPanel::create();
    m_pControlPanel->loadUI("");
    m_pControlPanel->setColor(color);
    m_pControlPanel->setPosition(Vec2(750,175));
    this->addChild(m_pControlPanel);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,50));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(MissionUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName("FZXS12.TTF");
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText("返回");
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
    m_pControlPanel->setColor(color);
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setColor(color);
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