//
//  ControlPanel.h
//  SuperLife
//
//  Created by wang haibo on 14-8-18.
//
//

#ifndef __SuperLife__ControlPanel__
#define __SuperLife__ControlPanel__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "IUIReader.h"
class ControlPanel : public cocos2d::ui::Widget, public IUIReader
{
    ControlPanel();
public:
    static ControlPanel* create();
    // 加载文件
    void loadUI(const std::string& file);
    // 设置颜色
    void setColor(const cocos2d::Color3B& color);
    // 点击CkeckBox回调
    void checkBoxPressed(Ref* p,TouchEventType eventType);
    // 拖动滑动条回调
    static void sliderPercentChanged(Ref* p,cocos2d::ui::Slider::EventType eventType);
private:
    cocos2d::Sprite*         m_pPanel;
    cocos2d::ui::Slider*     m_pSpeedSlider;
    cocos2d::Label*          m_pLabelSlow;
    cocos2d::Label*          m_pLabelQuick;
    
    cocos2d::ui::CheckBox*     m_pSelectColorCB0;
    cocos2d::ui::CheckBox*     m_pSelectColorCB1;
    cocos2d::ui::CheckBox*     m_pSelectColorCB2;
    cocos2d::ui::CheckBox*     m_pSelectColorCB3;
    cocos2d::ui::CheckBox*     m_pSelectColorCB4;
    cocos2d::ui::CheckBox*     m_pSelectColorCB5;
    cocos2d::ui::CheckBox*     m_pSelectColorCB6;
};

#endif /* defined(__SuperLife__ControlPanel__) */
