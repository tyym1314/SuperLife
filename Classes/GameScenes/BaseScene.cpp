//
//  BaseScene.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#include "BaseScene.h"
USING_NS_CC;

//构造
BaseScene::BaseScene()
{
    m_bPause = true;
}

//析构
BaseScene::~BaseScene()
{
    Director::getInstance()->getTextureCache()->removeUnusedTextures();
}

//初始化图层
void BaseScene::initGameLayers(int layerMask)
{
    Scene::init();
    if(layerMask & LAYER_HIDEN)
    {
        Layer* layer = Layer::create();
        layer->setName("HidenLayer");
        addChild(layer,LAYER_HIDEN, LAYER_HIDEN);
    }
    if(layerMask & LAYER_BACKGROUND);
    {
        Layer* layer = Layer::create();
        layer->setName("BackgroundLayer");
        addChild(layer,LAYER_BACKGROUND, LAYER_BACKGROUND);
    }
    if(layerMask & LAYER_BACKGROUND_EFFECT);
    {
        Layer* layer = Layer::create();
        layer->setName("BackgroundEffectLayer");
        addChild(layer,LAYER_BACKGROUND_EFFECT, LAYER_BACKGROUND_EFFECT);
    }
    if(layerMask & LAYER_TERRAIN);
    {
        Layer* layer = Layer::create();
        layer->setName("TerrainLayer");
        addChild(layer,LAYER_TERRAIN, LAYER_TERRAIN);
    }
    if(layerMask & LAYER_BASE);
    {
        Layer* layer = Layer::create();
        layer->setName("BaseLayer");
        addChild(layer,LAYER_BASE, LAYER_BASE);
    }
    if(layerMask & LAYER_EFFECT);
    {
        Layer* layer = Layer::create();
        layer->setName("EffectLayer");
        addChild(layer,LAYER_EFFECT, LAYER_EFFECT);
    }
    if(layerMask & LAYER_SCREEN_EFFECT);
    {
        Layer* layer = Layer::create();
        layer->setName("ScreenEffectLayer");
        addChild(layer,LAYER_SCREEN_EFFECT, LAYER_SCREEN_EFFECT);
    }
    if(layerMask & LAYER_UI);
    {
        Layer* layer = Layer::create();
        layer->setName("UILayer");
        addChild(layer,LAYER_UI, LAYER_UI);
    }
    if(layerMask & LAYER_CONSOLE);
    {
        Layer* layer = Layer::create();
        layer->setName("ConsoleLayer");
        addChild(layer,LAYER_CONSOLE, LAYER_CONSOLE);
    }
    if(layerMask & LAYER_DEBUG_INFO);
    {
        Layer* layer = Layer::create();
        layer->setName("UILayer");
        addChild(layer,LAYER_DEBUG_INFO, LAYER_DEBUG_INFO);
    }
}
//获取图层对象
Layer* BaseScene::getLayer(const std::string& layerName)
{
    return static_cast<Layer*>(getChildByName(layerName));
}

//是否暂停中
bool BaseScene::IsPaused() const
{
    return m_bPause;
}
//设置是否暂停
void BaseScene::setPause(bool pause)
{
    m_bPause = pause;
}

void BaseScene::onEnter()
{
    Scene::onEnter();
    scheduleUpdate();
}
void BaseScene::onExit()
{
    unscheduleUpdate();
    Scene::onExit();
}
// 更新处理
void BaseScene::update(float delta)
{
    Scene::update(delta);
}
// 设置场景颜色
void BaseScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_SceneColor = color;
}