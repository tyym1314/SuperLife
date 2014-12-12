//
//  UIMgr.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-11.
//
//

#include "UIMgr.h"
#include "SceneFactory.h"
#include "UIConst.h"
#include "MenuUI.h"
#include "MainUI.h"
#include "MissionListUI.h"
#include "MissionUI.h"
USING_NS_CC;

UIMgr* g_pUIMgrInstance = nullptr;
// 单体
UIMgr* UIMgr::getInstance()
{
    if( g_pUIMgrInstance == nullptr )
        g_pUIMgrInstance = new UIMgr();
    
    return g_pUIMgrInstance;
}
// 构造函数
UIMgr::UIMgr()
{
}
// 析构函数
UIMgr::~UIMgr()
{
}
//创建UI
ui::Layout* UIMgr::createUI(int uiid)
{
    ui::Layout* layout = nullptr;
    BaseScene* runningScene = SceneFactory::getInstance()->getCurrentScene();
    Layer* layer = runningScene->getLayer("UILayer");
    if(runningScene && layer)
    {
        switch (uiid) {
            case MENU_UI:
                {
                    layout = new MenuUI(runningScene);
                    if(layout)
                    {
                        static_cast<MenuUI*>(layout)->loadUI(MENU_UI_FILE);
                        layer->addChild(layout);
                        layout->autorelease();
                    }
                }
                break;
            case MAIN_UI:
                {
                    layout = new MainUI(runningScene);
                    if(layout)
                    {
                        static_cast<MainUI*>(layout)->loadUI(MAIN_UI_FILE);
                        layer->addChild(layout);
                        layout->autorelease();
                    }
                }
                break;
            case MISSION_LIST_UI:
                {
                    layout = new MissionListUI(runningScene);
                    if(layout)
                    {
                        static_cast<MissionListUI*>(layout)->loadUI(MISSION_LIST_UI_FILE);
                        layer->addChild(layout);
                        layout->autorelease();
                    }
                }
                break;
            case MISSION_UI:
                {
                    layout = new MissionUI(runningScene);
                    if(layout)
                    {
                        static_cast<MissionUI*>(layout)->loadUI(MISSION_UI_FILE);
                        layer->addChild(layout);
                        layout->autorelease();
                    }
                }
                break;
                
            default:
                break;
        }
    }
    return layout;
}
