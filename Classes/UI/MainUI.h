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
#include "ui/CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "IUIReader.h"
class BaseScene;
class ControlPanel;
class MainUI : public cocos2d::ui::Layout, public IUIReader, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
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
    
    cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event *unused_event);
private:
    // 点击开始按钮
    void pressStartBtn(Ref* p,TouchEventType eventType);
    // 点击重置按钮
    void pressResetBtn(Ref* p,TouchEventType eventType);
    // 点击恢复按钮
    void pressRestoreBtn(Ref* p,TouchEventType eventType);
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
    cocos2d::ui::Button*     m_pRestoreBtn;
    ControlPanel*     m_pControlPanel;
    cocos2d::ui::Button*     m_pBackBtn;
    cocos2d::extension::TableView*  m_pTableView;
    ssize_t                         m_nSelectIndex;
};

#endif /* defined(__SuperLife__MainUI__) */
