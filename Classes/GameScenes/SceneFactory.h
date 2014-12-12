//
//  SceneFactory.h
//  SuperLife
//
//  Created by wang haibo on 14-8-4.
//
//

#ifndef __SuperLife__SceneFactory__
#define __SuperLife__SceneFactory__

#include "cocos2d.h"
#include "BaseScene.h"
class SceneFactory : public cocos2d::Ref
{
    // 构造函数
    SceneFactory();
public:
    // 单体
    static SceneFactory* getInstance();
    // 创建指定ID场景
    BaseScene* createSceneByID(int sceneID);
    // 获取当前场景
    BaseScene* getCurrentScene();
    //获取颜色
    cocos2d::Color3B getSceneColor() const;
    //设置颜色
    void setSceneColor(const cocos2d::Color3B& color);
private:
    cocos2d::Color3B    m_SceneColor;
};

#endif /* defined(__SuperLife__SceneFactory__) */
