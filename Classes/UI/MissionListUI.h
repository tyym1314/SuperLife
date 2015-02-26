//
//  MissionListUI.h
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#ifndef __SuperLife__MissionListUI__
#define __SuperLife__MissionListUI__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "IUIReader.h"
class BaseScene;
class ControlPanel;
class MissionListUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    MissionListUI(BaseScene* owner);
    // 析构函数
    virtual ~MissionListUI();
    // 加载文件
    void loadUI(const std::string& file);
protected:
    // 点击任务序号按钮
    void pressLevelSelectBtn(Ref* p,TouchEventType eventType);
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
private:
    BaseScene*                              m_pOwnerScene;
    cocos2d::Label*                         m_pLabelLevelSelect;
    cocos2d::ui::ScrollView*                m_pScrollView;
    cocos2d::ui::Button*                    m_pBackBtn;
    
};

#endif /* defined(__SuperLife__MissionListUI__) */
