//
//  MissionScene.h
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#ifndef __SuperLife__MissionScene__
#define __SuperLife__MissionScene__

#include "BaseScene.h"
#include "ui/CocosGUI.h"
class MissionScene : public BaseScene
{
public:
    //构造
    MissionScene();
    //析构
    virtual ~MissionScene();
    // 设置当前关卡
    void setCurrentLevel(int level);
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pMissionUI;
    int                         m_nCurrentLevel;
};

#endif /* defined(__SuperLife__MissionScene__) */
