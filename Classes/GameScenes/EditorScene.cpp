//
//  EditorScene.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/7.
//
//

#include "EditorScene.h"
#include "TerrainMgr.h"
#include "UIMgr.h"
#include "UIConst.h"
#include "NativeBridge.h"
USING_NS_CC;
//构造
EditorScene::EditorScene()
{
    m_pEditorUI = nullptr;
}
//析构
EditorScene::~EditorScene()
{
}
void EditorScene::onEnter()
{
    BaseScene::onEnter();
    TerrainMgr::getInstance()->addTerrain(TerrainCell::RECTANGLE, 9, 9, 40, Vec2(40, 100));
    m_pEditorUI = UIMgr::getInstance()->createUI(EDITOR_UI);
    NativeBridge::getInstance()->hideAdsView();
}
void EditorScene::onExit()
{
    NativeBridge::getInstance()->hideAdsView();
    TerrainMgr::getInstance()->removeTerrain();
    BaseScene::onExit();
}
// 更新处理
void EditorScene::update(float delta)
{
    BaseScene::update(delta);
    if(!m_bPause)
        TerrainMgr::getInstance()->update(delta);
    if(m_pEditorUI)
        m_pEditorUI->update(delta);
}
// 设置场景颜色
void EditorScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pEditorUI->setColor(color);
    TerrainMgr::getInstance()->updateTerrain();
}