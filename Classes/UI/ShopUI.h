//
//  ShopUI.h
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#ifndef __SuperLife__ShopUI__
#define __SuperLife__ShopUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "IUIReader.h"
class BaseScene;
class ShopUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    ShopUI(BaseScene* owner);
    // 析构函数
    virtual ~ShopUI();
    // 加载文件
    void loadUI(const std::string& file);
protected:
    // 点击删除广告按钮
    void pressRemoveAdsViewBtn(Ref* p,TouchEventType eventType);
    // 点击解锁全部模版按钮
    void pressUnlockAllTemplatesBtn(Ref* p,TouchEventType eventType);
    // 点击解锁编辑模式按钮
    void pressUnlockEditorModeBtn(Ref* p,TouchEventType eventType);
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*                              m_pOwnerScene;
    cocos2d::Label*                         m_pLabelShop;
    cocos2d::ui::Button*                    m_pRemoveAdsViewBtn;
    cocos2d::ui::Button*                    m_pUnlockAllTemplatesBtn;
    cocos2d::ui::Button*                    m_pUnlockEditorModeBtn;
    cocos2d::ui::Button*                    m_pBackBtn;
    
};

#endif /* defined(__SuperLife__ShopUI__) */
