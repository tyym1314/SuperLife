//
//  MenuUI.h
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#ifndef __SuperLife__MenuUI__
#define __SuperLife__MenuUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "IUIReader.h"

class BaseScene;
class MenuUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    MenuUI(BaseScene* owner);
    // 析构函数
    virtual ~MenuUI();
    // 加载文件
    void loadUI(const std::string& file);
private:
    // 点击任务模式按钮
    void pressMissionModeBtn(Ref* p,TouchEventType eventType);
    // 点击自由模式按钮
    void pressFreeModeBtn(Ref* p,TouchEventType eventType);
    // 点击闪电按钮
    void pressShopBtn(Ref* p,TouchEventType eventType);
    // 点击编辑模式按钮
    void pressEditorBtn(Ref* p,TouchEventType eventType);
    // 点击帮助按钮
    void pressHelpBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*               m_pOwnerScene;
    cocos2d::ui::Button*     m_pFreeModeBtn;
    cocos2d::ui::Button*     m_pMissionModeBtn;
    cocos2d::ui::Button*     m_pShopBtn;
    cocos2d::ui::Button*     m_pEditorBtn;
    cocos2d::ui::Button*     m_pHelpBtn;
};

#endif /* defined(__SuperLife__MenuUI__) */
