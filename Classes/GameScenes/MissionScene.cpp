//
//  MissionScene.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#include "MissionScene.h"
#include "TerrainMgr.h"
#include "UIMgr.h"
#include "UIConst.h"
#include "NativeBridge.h"
#include "EncrytionUtility.h"
USING_NS_CC;

//构造
MissionScene::MissionScene()
{
    m_pMissionUI = nullptr;
    m_nCurrentLevel = 0;
}
//析构
MissionScene::~MissionScene()
{
}
// 设置当前关卡
void MissionScene::setCurrentLevel(int level)
{
    m_nCurrentLevel = level;
    TerrainMgr::getInstance()->resetTerrain();
}
void MissionScene::onEnter()
{
    BaseScene::onEnter();
    if (!EncrytionUtility::getBoolForKey("RemoveAds",false))
        TerrainMgr::getInstance()->addTerrain(TerrainCell::RECTANGLE, 60, 60, 6, Vec2(40, 105));
    else
        TerrainMgr::getInstance()->addTerrain(TerrainCell::RECTANGLE, 60, 60, 6, Vec2(40, 95));
    m_pMissionUI = UIMgr::getInstance()->createUI(MISSION_UI);
    NativeBridge::getInstance()->showAdsView();
}
void MissionScene::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    TerrainMgr::getInstance()->removeTerrain();
    BaseScene::onExit();
}
// 更新处理
void MissionScene::update(float delta)
{
    BaseScene::update(delta);
    if(!m_bPause)
        TerrainMgr::getInstance()->update(delta);
    if(m_pMissionUI)
        m_pMissionUI->update(delta);
}
// 设置场景颜色
void MissionScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pMissionUI->setColor(color);
    TerrainMgr::getInstance()->updateTerrain();
}