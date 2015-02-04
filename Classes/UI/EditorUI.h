//
//  EditorUI.h
//  SuperLife
//
//  Created by wang haibo on 15/1/7.
//
//

#ifndef __SuperLife__EditorUI__
#define __SuperLife__EditorUI__

#include "cocos2d.h"
#include "CocosGUI.h"
#include "cocos-ext.h"
#include "IUIReader.h"
class BaseScene;
class EditorUI : public cocos2d::ui::Layout, public IUIReader, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    // 构造函数
    EditorUI(BaseScene* owner);
    // 析构函数
    virtual ~EditorUI();
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
protected:
    // 点击保存按钮
    void pressSaveBtn(Ref* p,TouchEventType eventType);
    // 点击重置按钮
    void pressResetBtn(Ref* p,TouchEventType eventType);
    // 点击删除按钮
    void pressDeleteBtn(Ref* p,TouchEventType eventType);
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*                      m_pOwnerScene;
    cocos2d::Label*                 m_pLabelMode;
    cocos2d::Sprite*                m_pPanel1;
    cocos2d::extension::EditBox*    m_pEditBox;
    cocos2d::ui::Button*            m_pSaveBtn;
    cocos2d::ui::Button*            m_pResetBtn;
    cocos2d::ui::Button*            m_pDeleteBtn;
    cocos2d::ui::Button*            m_pBackBtn;
    cocos2d::extension::TableView*  m_pTableView;
    cocos2d::Label*                 m_pLabelErrorInfo;
    int                             m_nSelectIndex;
};

#endif /* defined(__SuperLife__EditorUI__) */
