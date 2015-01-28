//
//  MissionListScene.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#include "MissionListScene.h"
#include "UIMgr.h"
#include "UIConst.h"
#include "NativeBridge.h"
USING_NS_CC;

//构造
MissionListScene::MissionListScene()
{
    m_pMissionListUI = nullptr;
}
//析构
MissionListScene::~MissionListScene()
{
}
void MissionListScene::onEnter()
{
    BaseScene::onEnter();
    m_pMissionListUI = UIMgr::getInstance()->createUI(MISSION_LIST_UI);
    NativeBridge::getInstance()->showAdsView();
}
void MissionListScene::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    BaseScene::onExit();
}
// 设置场景颜色
void MissionListScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pMissionListUI->setColor(color);
}