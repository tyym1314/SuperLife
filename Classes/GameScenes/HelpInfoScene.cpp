//
//  HelpInfoScene.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#include "HelpInfoScene.h"
#include "UIMgr.h"
#include "UIConst.h"
USING_NS_CC;
//构造
HelpInfoScene::HelpInfoScene()
{
    m_pHelpInfoUI = nullptr;
}
//析构
HelpInfoScene::~HelpInfoScene()
{
}
void HelpInfoScene::onEnter()
{
    BaseScene::onEnter();
    m_pHelpInfoUI = UIMgr::getInstance()->createUI(HELPINFO_UI);
}
void HelpInfoScene::onExit()
{
    BaseScene::onExit();
}
// 更新处理
void HelpInfoScene::update(float delta)
{
    BaseScene::update(delta);
    if(m_pHelpInfoUI)
        m_pHelpInfoUI->update(delta);
}
// 设置场景颜色
void HelpInfoScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pHelpInfoUI->setColor(color);
}