//
//  MenuScene.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#include "MenuScene.h"
#include "UIMgr.h"
#include "UIConst.h"
USING_NS_CC;
//构造
MenuScene::MenuScene()
{
    m_pMenuUI = nullptr;
}
//析构
MenuScene::~MenuScene()
{
}
void MenuScene::onEnter()
{
    BaseScene::onEnter();
    m_pMenuUI = UIMgr::getInstance()->createUI(MENU_UI);
}
void MenuScene::onExit()
{
    BaseScene::onExit();
}
// 更新处理
void MenuScene::update(float delta)
{
    BaseScene::update(delta);
}