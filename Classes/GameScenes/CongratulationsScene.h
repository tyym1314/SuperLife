//
//  CongratulationsScene.h
//  SuperLife
//
//  Created by wang haibo on 15/1/20.
//
//

#ifndef __SuperLife__CongratulationsScene__
#define __SuperLife__CongratulationsScene__

#include "BaseScene.h"
#include "ui/CocosGUI.h"
class CongratulationsScene : public BaseScene
{
public:
    //构造
    CongratulationsScene();
    //析构
    virtual ~CongratulationsScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pCongratulationsUI;
};

#endif /* defined(__SuperLife__CongratulationsScene__) */
