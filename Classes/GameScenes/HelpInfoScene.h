//
//  HelpInfoScene.h
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#ifndef __SuperLife__HelpInfoScene__
#define __SuperLife__HelpInfoScene__

#include "BaseScene.h"
#include "CocosGUI.h"
class HelpInfoScene : public BaseScene
{
public:
    //构造
    HelpInfoScene();
    //析构
    virtual ~HelpInfoScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pHelpInfoUI;
};

#endif /* defined(__SuperLife__HelpInfoScene__) */
