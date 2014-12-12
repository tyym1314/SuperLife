//
//  MissionUI.h
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#ifndef __SuperLife__MissionUI__
#define __SuperLife__MissionUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "IUIReader.h"
class BaseScene;
class ControlPanel;
class MissionUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    MissionUI(BaseScene* owner);
    // 析构函数
    virtual ~MissionUI();
    // 加载文件
    void loadUI(const std::string& file);
public:
    // 更新处理
    void update(float delta);
    //设置UI颜色
    void setColor(const cocos2d::Color3B& color);
protected:
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*                  m_pOwnerScene;
    cocos2d::Label*             m_pLabelMode;
    cocos2d::Sprite*            m_pPanel1;
    ControlPanel*               m_pControlPanel;
    cocos2d::ui::Button*        m_pBackBtn;
};

#endif /* defined(__SuperLife__MissionUI__) */
