//
//  ShopScene.h
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#ifndef __SuperLife__ShopScene__
#define __SuperLife__ShopScene__

#include "BaseScene.h"
#include "CocosGUI.h"
class ShopScene : public BaseScene
{
public:
    //构造
    ShopScene();
    //析构
    virtual ~ShopScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pShopUI;
};

#endif /* defined(__SuperLife__ShopScene__) */
