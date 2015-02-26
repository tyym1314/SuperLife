//
//  EditLevelScene.h
//  SuperLife
//
//  Created by wang haibo on 15/1/14.
//
//

#ifndef __SuperLife__EditLevelScene__
#define __SuperLife__EditLevelScene__

#include "BaseScene.h"
#include "ui/CocosGUI.h"
class LevelEditorScene : public BaseScene
{
public:
    //构造
    LevelEditorScene();
    //析构
    virtual ~LevelEditorScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pLevelEditorUI;
};

#endif /* defined(__SuperLife__EditLevelScene__) */
