//
//  EditLevelUI.h
//  SuperLife
//
//  Created by wang haibo on 15/1/14.
//
//

#ifndef __SuperLife__EditLevelUI__
#define __SuperLife__EditLevelUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "IUIReader.h"
class BaseScene;
class ControlPanel;
class EditLevelUI : public cocos2d::ui::Layout, public IUIReader
{
public:
    // 构造函数
    EditLevelUI(BaseScene* owner);
    // 析构函数
    virtual ~EditLevelUI();
    // 加载文件
    void loadUI(const std::string& file);
public:
    // 更新处理
    void update(float delta);
private:
    // 点击开始按钮
    void pressStartBtn(Ref* p,TouchEventType eventType);
    // 点击重置按钮
    void pressResetBtn(Ref* p,TouchEventType eventType);
    // 点击恢复按钮
    void pressRestoreBtn(Ref* p,TouchEventType eventType);
    // 点击保存按钮
    void pressSaveBtn(Ref* p,TouchEventType eventType);
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*                      m_pOwnerScene;
    cocos2d::extension::EditBox*    m_pFileNameEditBox;
    cocos2d::extension::EditBox*    m_pLevelNameEditBox;
    cocos2d::extension::EditBox*    m_pGoalCellNumEditBox;
    cocos2d::extension::EditBox*    m_pGoalCellGenerationEditBox;
    cocos2d::extension::EditBox*    m_pStarterCellNumEditBox;
    cocos2d::Label*                 m_pLabelMode;
    cocos2d::Label*                 m_pLabelLifeNum;
    cocos2d::Label*                 m_pLabeGenerationNum;
    cocos2d::Sprite*                m_pPanel1;
    cocos2d::ui::Button*            m_pStartBtn;
    cocos2d::ui::Button*            m_pResetBtn;
    cocos2d::ui::Button*            m_pRestoreBtn;
    cocos2d::ui::Button*            m_pSaveBtn;
    cocos2d::ui::Button*            m_pBackBtn;
    cocos2d::Label*                 m_pLabelErrorInfo;
};

#endif /* defined(__SuperLife__EditLevelUI__) */
