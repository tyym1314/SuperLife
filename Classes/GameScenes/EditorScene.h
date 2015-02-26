//
//  EditorScene.h
//  SuperLife
//
//  Created by wang haibo on 15/1/7.
//
//

#ifndef __SuperLife__EditorScene__
#define __SuperLife__EditorScene__

#include "BaseScene.h"
#include "ui/CocosGUI.h"
class EditorScene : public BaseScene
{
public:
    //构造
    EditorScene();
    //析构
    virtual ~EditorScene();
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::ui::Layout*    m_pEditorUI;
};

#endif /* defined(__SuperLife__EditorScene__) */
