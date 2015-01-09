//
//  HelpInfoUI.h
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#ifndef __SuperLife__HelpInfoUI__
#define __SuperLife__HelpInfoUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "IUIReader.h"
class BaseScene;
class HelpInfoUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    HelpInfoUI(BaseScene* owner);
    // 析构函数
    virtual ~HelpInfoUI();
    // 加载文件
    void loadUI(const std::string& file);
protected:
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*                              m_pOwnerScene;
    cocos2d::Label*                         m_pLabelHelpInfo;
    cocos2d::ui::Button*                    m_pBackBtn;
    
};

#endif /* defined(__SuperLife__HelpInfoUI__) */
