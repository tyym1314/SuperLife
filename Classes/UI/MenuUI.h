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
    // 点击开始按钮
    void pressFreeModeBtn(Ref* p,TouchEventType eventType);
    // 点击暂停按钮
    void pressQuestModeBtn(Ref* p,TouchEventType eventType);
    // 点击帮助按钮
    void pressHelpBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*               m_pOwnerScene;
    cocos2d::ui::Button*     m_pFreeModeBtn;
    cocos2d::ui::Button*     m_pQuestModeBtn;
    cocos2d::ui::Button*     m_pHelpBtn;
};

#endif /* defined(__SuperLife__MenuUI__) */
