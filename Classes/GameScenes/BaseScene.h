//
//  BaseScene.h
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#ifndef __SuperLife__BaseScene__
#define __SuperLife__BaseScene__

#include "cocos2d.h"
#include "SceneConst.h"

class BaseScene : public cocos2d::Scene
{
public:
    //构造
    BaseScene();
    //析构
    virtual ~BaseScene();
    //初始化图层
    void initGameLayers(int layerMask);
    //获取图层对象
    cocos2d::Layer* getLayer(const std::string& layerName);
    //是否暂停中
    bool IsPaused() const;
    //设置是否暂停
    void setPause(bool pause);
public:
    virtual void onEnter();
    virtual void onExit();
    // 更新处理
    virtual void update(float delta);
    // 设置场景颜色
    virtual void setSceneColor(const cocos2d::Color3B& color);
protected:
    bool                    m_bPause;
    cocos2d::Color3B        m_SceneColor;
};

#endif /* defined(__SuperLife__BaseScene__) */
