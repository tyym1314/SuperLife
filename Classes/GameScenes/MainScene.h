//
//  MainScene.h
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#ifndef __SuperLife__MainScene__
#define __SuperLife__MainScene__

#include "BaseScene.h"
#include "CocosGUI.h"
class MainScene : public BaseScene
{
public:
    //构造
    MainScene();
    //析构
    virtual ~MainScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pMainUI;
};

#endif /* defined(__SuperLife__MainScene__) */
