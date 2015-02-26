//
//  UIMgr.h
//  SuperLife
//
//  Created by wang haibo on 14-8-11.
//
//

#ifndef __SuperLife__UIMgr__
#define __SuperLife__UIMgr__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class UIMgr : public cocos2d::Ref
{
    // 构造函数
    UIMgr();
public:
    // 单体
    static UIMgr* getInstance();
    // 析构函数
    ~UIMgr();
    //创建UI
    cocos2d::ui::Layout* createUI(int uiid);
};

#endif /* defined(__SuperLife__UIMgr__) */
