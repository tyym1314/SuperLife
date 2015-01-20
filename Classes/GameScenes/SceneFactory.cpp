//
//  SceneFactory.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#include "SceneFactory.h"
#include "MenuScene.h"
#include "MainScene.h"
#include "MissionListScene.h"
#include "MissionScene.h"
#include "EditorScene.h"
#include "ShopScene.h"
#include "HelpInfoScene.h"
#include "EditLevelScene.h"
#include "CongratulationsScene.h"
#include "MathUtility.h"
USING_NS_CC;

SceneFactory* g_pSceneFactoryInstance = nullptr;
// 单体
SceneFactory* SceneFactory::getInstance()
{
    if( g_pSceneFactoryInstance == nullptr )
        g_pSceneFactoryInstance = new SceneFactory();
    
    return g_pSceneFactoryInstance;
}
// 构造函数
SceneFactory::SceneFactory()
{
    m_SceneColor = MathUtility::randomColor();
}
// 获取指定ID场景
BaseScene* SceneFactory::createSceneByID(int sceneID)
{
    BaseScene* scene = nullptr;
    switch ( sceneID ) {
        case SCENE_MENU:
            scene = new MenuScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        case SCENE_MAIN:
            scene = new MainScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        case SCENE_MISSION_LIST:
            scene = new MissionListScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        case SCENE_MISSION:
            scene = new MissionScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        case SCENE_EDITOR:
            m_SceneColor = Color3B::WHITE;
            scene = new EditorScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }

            break;
        case SCENE_SHOP:
            scene = new ShopScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;

        case SCENE_HELPINFO:
            scene = new HelpInfoScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        case SCENE_LEVELEDITOR:
            m_SceneColor = Color3B::WHITE;
            scene = new LevelEditorScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        case SCENE_CONGRATULATIONS:
            scene = new CongratulationsScene();
            if(scene)
            {
                scene->initGameLayers(LAYER_ALL);
                scene->autorelease();
            }
            break;
        default:
            break;
    }
    return scene;
}
// 获取当前场景
BaseScene* SceneFactory::getCurrentScene()
{
    return static_cast<BaseScene*>(Director::getInstance()->getRunningScene());
}
//获取颜色
Color3B SceneFactory::getSceneColor() const
{
    return m_SceneColor;
}
//设置颜色
void SceneFactory::setSceneColor(const cocos2d::Color3B& color)
{
    m_SceneColor = color;
    BaseScene* pBaseScene = getCurrentScene();
    if(pBaseScene)
        pBaseScene->setSceneColor(m_SceneColor);
}