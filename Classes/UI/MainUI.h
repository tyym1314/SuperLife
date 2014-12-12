//
//  MainUI.h
//  SuperLife
//
//  Created by wang haibo on 14-8-11.
//
//

#ifndef __SuperLife__MainUI__
#define __SuperLife__MainUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "IUIReader.h"
class BaseScene;
class ControlPanel;
class MainUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    MainUI(BaseScene* owner);
    // 析构函数
    virtual ~MainUI();
    // 加载文件
    void loadUI(const std::string& file);
public:
    // 更新处理
    void update(float delta);
    //设置UI颜色
    void setColor(const cocos2d::Color3B& color);
private:
    // 点击开始按钮
    void pressStartBtn(Ref* p,TouchEventType eventType);
    // 点击重置按钮
    void pressResetBtn(Ref* p,TouchEventType eventType);
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*               m_pOwnerScene;
    cocos2d::Label*          m_pLabelMode;
    cocos2d::Label*          m_pLabelLifeNum;
    cocos2d::Label*          m_pLabeGenerationNum;
    cocos2d::Sprite*         m_pPanel1;
    cocos2d::ui::Button*     m_pStartBtn;
    cocos2d::ui::Button*     m_pResetBtn;
    ControlPanel*     m_pControlPanel;
    cocos2d::ui::Button*     m_pBackBtn;
};

#endif /* defined(__SuperLife__MainUI__) */
