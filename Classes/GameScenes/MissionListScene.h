//
//  MissionListScene.h
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#ifndef __SuperLife__MissionListScene__
#define __SuperLife__MissionListScene__

#include "BaseScene.h"
#include "CocosGUI.h"
class MissionListScene : public BaseScene
{
public:
    //构造
    MissionListScene();
    //析构
    virtual ~MissionListScene();
public:
    virtual void onEnter();
    virtual void onExit();

    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pMissionListUI;
};

#endif /* defined(__SuperLife__MissionListScene__) */
