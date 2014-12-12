//
//  ControlPanel.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-18.
//
//

#include "ControlPanel.h"
#include "SpeedSlider.h"
#include "ColorCheckBox.h"
#include "SceneFactory.h"
#include "TerrainMgr.h"
USING_NS_CC;

ControlPanel* ControlPanel::create()
{
    ControlPanel* widget = new ControlPanel();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
ControlPanel::ControlPanel()
:m_pPanel(nullptr),m_pSpeedSlider(nullptr),m_pLabelSlow(nullptr),m_pLabelQuick(nullptr),
m_pSelectColorCB0(nullptr),m_pSelectColorCB1(nullptr),m_pSelectColorCB2(nullptr),
m_pSelectColorCB3(nullptr),m_pSelectColorCB4(nullptr),m_pSelectColorCB5(nullptr),m_pSelectColorCB6(nullptr)
{
}
// 加载文件
void ControlPanel::loadUI(const std::string& file)
{
    m_pPanel = Sprite::create("panel2.png");
    m_pPanel->setPosition(Vec2(0,0));
    this->addChild(m_pPanel);
    
    m_pSpeedSlider = SpeedSlider::create();
    m_pSpeedSlider->loadBarTexture("slider_bar.png");
    m_pSpeedSlider->loadSlidBallTextureNormal("slider_bar_button.png");
    m_pSpeedSlider->loadSlidBallTexturePressed("slider_bar_button.png");
    m_pSpeedSlider->setPosition(Vec2(0, 40));
    m_pSpeedSlider->addEventListener(ControlPanel::sliderPercentChanged);
    float percent =TerrainMgr::getInstance()->getCurUpdateDelta()/(TerrainMgr::getInstance()->getMaxUpdateDelta() - TerrainMgr::getInstance()->getMinUpdateDelta());
    m_pSpeedSlider->setPercent(percent*100);
    this->addChild(m_pSpeedSlider);
    
    m_pLabelSlow = Label::createWithTTF("慢", "FZXS12.TTF", 18);
    m_pLabelSlow->setPosition(Vec2(150,40));
    this->addChild(m_pLabelSlow);
    
    m_pLabelQuick = Label::createWithTTF("快", "FZXS12.TTF", 18);
    m_pLabelQuick->setPosition(Vec2(-150,40));
    this->addChild(m_pLabelQuick);
    
    m_pSelectColorCB0 = ColorCheckBox::create();
    m_pSelectColorCB0->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB0->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB0->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB0->setPosition(Vec2(-120, -30));
    m_pSelectColorCB0->setSelectedState(false);
    m_pSelectColorCB0->setColor(Color3B(70,255,149));
    m_pSelectColorCB0->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB0->setScale(1.5f);
    this->addChild(m_pSelectColorCB0);
    
    m_pSelectColorCB1 = ColorCheckBox::create();
    m_pSelectColorCB1->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB1->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB1->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB1->setPosition(Vec2(-80, -30));
    m_pSelectColorCB1->setSelectedState(false);
    m_pSelectColorCB1->setColor(Color3B(243,47,187));
    m_pSelectColorCB1->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB1->setScale(1.5f);
    this->addChild(m_pSelectColorCB1);
    
    m_pSelectColorCB2 = ColorCheckBox::create();
    m_pSelectColorCB2->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB2->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB2->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB2->setPosition(Vec2(-40, -30));
    m_pSelectColorCB2->setSelectedState(false);
    m_pSelectColorCB2->setColor(Color3B(246,248,21));
    m_pSelectColorCB2->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB2->setScale(1.5f);
    this->addChild(m_pSelectColorCB2);
    
    m_pSelectColorCB3 = ColorCheckBox::create();
    m_pSelectColorCB3->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB3->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB3->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB3->setPosition(Vec2(0, -30));
    m_pSelectColorCB3->setSelectedState(false);
    m_pSelectColorCB3->setColor(Color3B(67,230,203));
    m_pSelectColorCB3->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB3->setScale(1.5f);
    this->addChild(m_pSelectColorCB3);
    
    m_pSelectColorCB4 = ColorCheckBox::create();
    m_pSelectColorCB4->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB4->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB4->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB4->setPosition(Vec2(40, -30));
    m_pSelectColorCB4->setSelectedState(false);
    m_pSelectColorCB4->setColor(Color3B(188,49,249));
    m_pSelectColorCB4->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB4->setScale(1.5f);
    this->addChild(m_pSelectColorCB4);
    
    m_pSelectColorCB5 = ColorCheckBox::create();
    m_pSelectColorCB5->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB5->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB5->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB5->setPosition(Vec2(80, -30));
    m_pSelectColorCB5->setSelectedState(false);
    m_pSelectColorCB5->setColor(Color3B(71,220,255));
    m_pSelectColorCB5->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB5->setScale(1.5f);
    this->addChild(m_pSelectColorCB5);
    
    m_pSelectColorCB6 = ColorCheckBox::create();
    m_pSelectColorCB6->loadTextureBackGround("slider_bar_button.png");
    m_pSelectColorCB6->loadTextureBackGroundSelected("slider_bar_button.png");
    m_pSelectColorCB6->loadTextureFrontCross("slider_bar_button.png");
    m_pSelectColorCB6->setPosition(Vec2(120, -30));
    m_pSelectColorCB6->setSelectedState(false);
    m_pSelectColorCB6->setColor(Color3B(252,183,54));
    m_pSelectColorCB6->addTouchEventListener(CC_CALLBACK_2(ControlPanel::checkBoxPressed, this));
    m_pSelectColorCB6->setScale(1.5f);
    this->addChild(m_pSelectColorCB6);
}
// 设置颜色
void ControlPanel::setColor(const cocos2d::Color3B& color)
{
    m_pPanel->setColor(color);
    m_pSpeedSlider->setColor(color);
    m_pLabelSlow->setColor(color);
    m_pLabelQuick->setColor(color);
}
// 点击CkeckBox返回
void ControlPanel::checkBoxPressed(Ref* p,TouchEventType eventType)
{
    if (eventType != TouchEventType::ENDED)
        return;
    ui::CheckBox* cb = static_cast<ui::CheckBox*>(p);
    if(cb)
    {
        if(!cb->getSelectedState())
        {
            if(cb == m_pSelectColorCB0)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB1->setSelectedState(false);
                m_pSelectColorCB2->setSelectedState(false);
                m_pSelectColorCB3->setSelectedState(false);
                m_pSelectColorCB4->setSelectedState(false);
                m_pSelectColorCB5->setSelectedState(false);
                m_pSelectColorCB6->setSelectedState(false);
            }
            else if(cb == m_pSelectColorCB1)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB0->setSelectedState(false);
                m_pSelectColorCB2->setSelectedState(false);
                m_pSelectColorCB3->setSelectedState(false);
                m_pSelectColorCB4->setSelectedState(false);
                m_pSelectColorCB5->setSelectedState(false);
                m_pSelectColorCB6->setSelectedState(false);
            }
            else if(cb == m_pSelectColorCB2)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB0->setSelectedState(false);
                m_pSelectColorCB1->setSelectedState(false);
                m_pSelectColorCB3->setSelectedState(false);
                m_pSelectColorCB4->setSelectedState(false);
                m_pSelectColorCB5->setSelectedState(false);
                m_pSelectColorCB6->setSelectedState(false);
            }
            else if(cb == m_pSelectColorCB3)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB0->setSelectedState(false);
                m_pSelectColorCB1->setSelectedState(false);
                m_pSelectColorCB2->setSelectedState(false);
                m_pSelectColorCB4->setSelectedState(false);
                m_pSelectColorCB5->setSelectedState(false);
                m_pSelectColorCB6->setSelectedState(false);
            }
            else if(cb == m_pSelectColorCB4)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB0->setSelectedState(false);
                m_pSelectColorCB1->setSelectedState(false);
                m_pSelectColorCB2->setSelectedState(false);
                m_pSelectColorCB3->setSelectedState(false);
                m_pSelectColorCB5->setSelectedState(false);
                m_pSelectColorCB6->setSelectedState(false);
            }
            else if(cb == m_pSelectColorCB5)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB0->setSelectedState(false);
                m_pSelectColorCB1->setSelectedState(false);
                m_pSelectColorCB2->setSelectedState(false);
                m_pSelectColorCB3->setSelectedState(false);
                m_pSelectColorCB4->setSelectedState(false);
                m_pSelectColorCB6->setSelectedState(false);
            }
            else if(cb == m_pSelectColorCB6)
            {
                SceneFactory::getInstance()->setSceneColor(cb->getColor());
                m_pSelectColorCB0->setSelectedState(false);
                m_pSelectColorCB1->setSelectedState(false);
                m_pSelectColorCB2->setSelectedState(false);
                m_pSelectColorCB3->setSelectedState(false);
                m_pSelectColorCB4->setSelectedState(false);
                m_pSelectColorCB5->setSelectedState(false);
            }
        }
        else
        {
            cb->setSelectedState(false);
        }
    }
}
// 拖动滑动条回调
void ControlPanel::sliderPercentChanged(Ref* p,ui::Slider::EventType eventType)
{
    if(eventType == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        ui::Slider* slider = static_cast<ui::Slider*>(p);
        if(slider)
        {
            float percent = slider->getPercent()/100.0f;
            percent = (TerrainMgr::getInstance()->getMaxUpdateDelta() - TerrainMgr::getInstance()->getMinUpdateDelta())*percent;
            TerrainMgr::getInstance()->setCurUpdateDelta(percent);
        }
    }
}