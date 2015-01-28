//
//  MainScene.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#include "MainScene.h"
#include "TerrainMgr.h"
#include "UIMgr.h"
#include "UIConst.h"
#include "NativeBridge.h"
USING_NS_CC;
//构造
MainScene::MainScene()
{
    m_pMainUI = nullptr;
}
//析构
MainScene::~MainScene()
{
}
void MainScene::onEnter()
{
    BaseScene::onEnter();
    TerrainMgr::getInstance()->addTerrain(TerrainCell::RECTANGLE, 60, 60, 6, Vec2(40, 95));
    m_pMainUI = UIMgr::getInstance()->createUI(MAIN_UI);
    NativeBridge::getInstance()->showAdsView();
}
void MainScene::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    TerrainMgr::getInstance()->removeTerrain();
    BaseScene::onExit();
}
// 更新处理
void MainScene::update(float delta)
{
    BaseScene::update(delta);
    if(!m_bPause)
        TerrainMgr::getInstance()->update(delta);
    if(m_pMainUI)
        m_pMainUI->update(delta);
}
// 设置场景颜色
void MainScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pMainUI->setColor(color);
    TerrainMgr::getInstance()->updateTerrain();
}