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
#include "cocos-ext.h"
#include "IUIReader.h"
class BaseScene;
class HelpInfoUI : public cocos2d::ui::Layout, public IUIReader, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate
{
public:
    // 构造函数
    HelpInfoUI(BaseScene* owner);
    // 析构函数
    virtual ~HelpInfoUI();
    // 加载文件
    void loadUI(const std::string& file);
    
    cocos2d::Size cellSizeForTable(cocos2d::extension::TableView *table);
    cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    
    void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
protected:
    // 点击下一页按钮
    void pressNextBtn(Ref* p,TouchEventType eventType);
    // 点击返回按钮
    void pressBackBtn(Ref* p,TouchEventType eventType);
private:
    BaseScene*                              m_pOwnerScene;
    cocos2d::Label*                         m_pLabelHelpInfo;
    cocos2d::ui::Button*                    m_pNextBtn;
    cocos2d::ui::Button*                    m_pBackBtn;
    cocos2d::extension::TableView*          m_pTableView;
    int                                     m_pCurrentPage;
};

#endif /* defined(__SuperLife__HelpInfoUI__) */
