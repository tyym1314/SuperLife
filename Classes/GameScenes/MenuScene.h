//
//  MenuScene.h
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#ifndef __SuperLife__MenuScene__
#define __SuperLife__MenuScene__

#include "BaseScene.h"
#include "ui/CocosGUI.h"
class MenuScene : public BaseScene
{
public:
    //构造
    MenuScene();
    //析构
    virtual ~MenuScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
private:
    cocos2d::ui::Layout*    m_pMenuUI;
};

#endif /* defined(__SuperLife__MenuScene__) */
