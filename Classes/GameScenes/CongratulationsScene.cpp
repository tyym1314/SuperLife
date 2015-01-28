//
//  CongratulationsScene.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/20.
//
//

#include "CongratulationsScene.h"
#include "UIMgr.h"
#include "UIConst.h"
#include "NativeBridge.h"
USING_NS_CC;
//构造
CongratulationsScene::CongratulationsScene()
{
    m_pCongratulationsUI = nullptr;
}
//析构
CongratulationsScene::~CongratulationsScene()
{
}
void CongratulationsScene::onEnter()
{
    BaseScene::onEnter();
    m_pCongratulationsUI = UIMgr::getInstance()->createUI(CONGRATULATIONS_UI);
    NativeBridge::getInstance()->showAdsView();
}
void CongratulationsScene::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    BaseScene::onExit();
}
// 更新处理
void CongratulationsScene::update(float delta)
{
    BaseScene::update(delta);
}
// 设置场景颜色
void CongratulationsScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pCongratulationsUI->setColor(color);
}