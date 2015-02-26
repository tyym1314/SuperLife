//
//  CongratulationsUI.h
//  SuperLife
//
//  Created by wang haibo on 15/1/20.
//
//

#ifndef __SuperLife__CongratulationsUI__
#define __SuperLife__CongratulationsUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "IUIReader.h"
class BaseScene;
class ControlPanel;
class CongratulationsUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    CongratulationsUI(BaseScene* owner);
    // 析构函数
    virtual ~CongratulationsUI();
    // 加载文件
    void loadUI(const std::string& file);
protected:
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
private:
    BaseScene*                              m_pOwnerScene;
    cocos2d::Label*                         m_pLabelCongratulations;
    cocos2d::Label*                         m_pLabelDetail;
    cocos2d::ui::Button*                    m_pBackBtn;
};

#endif /* defined(__SuperLife__CongratulationsUI__) */
