//
//  HelpInfoUI.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#include "HelpInfoUI.h"
#include "SceneFactory.h"
#include "UIMgr.h"
#include "GameConst.h"
#include "CommonUtility.h"
USING_NS_CC;
USING_NS_CC_EXT;
// 构造函数
HelpInfoUI::HelpInfoUI(BaseScene* owner)
{
    m_pOwnerScene = nullptr;
    m_pLabelHelpInfo = nullptr;
    m_pNextBtn = nullptr;
    m_pBackBtn = nullptr;
    m_pTableView = nullptr;
    m_pCurrentPage = 1;
}
// 析构函数
HelpInfoUI::~HelpInfoUI()
{
}
// 加载文件
void HelpInfoUI::loadUI(const std::string& file)
{
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    
    Size size = Director::getInstance()->getVisibleSize();
    m_pTableView = TableView::create(this, size);
    m_pTableView->setDirection(ScrollView::Direction::HORIZONTAL);
    m_pTableView->setColor(color);
    m_pTableView->setDelegate(this);
    this->addChild(m_pTableView);

    
    m_pLabelHelpInfo = Label::createWithTTF(CommonUtility::getLocalString("GameOrigins"), CommonUtility::getLocalString("MainFont"), 120);
    m_pLabelHelpInfo->setPosition(Vec2(470,580));
    m_pLabelHelpInfo->setColor(color);
    m_pLabelHelpInfo->setScale(0.5f);
    this->addChild(m_pLabelHelpInfo);
    
    m_pNextBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pNextBtn->setPosition(Vec2(750,80));
    m_pNextBtn->addTouchEventListener(CC_CALLBACK_2(HelpInfoUI::pressNextBtn, this));
    m_pNextBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pNextBtn->setTitleColor(color);
    m_pNextBtn->setTitleFontSize(24);
    m_pNextBtn->setTitleText(CommonUtility::getLocalString("NextPage"));
    m_pNextBtn->setColor(color);
    this->addChild(m_pNextBtn);
    
    m_pBackBtn = ui::Button::create("btnLBN.png","btnLBD.png");
    m_pBackBtn->setPosition(Vec2(750,80));
    m_pBackBtn->addTouchEventListener(CC_CALLBACK_2(HelpInfoUI::pressBackBtn, this));
    m_pBackBtn->setTitleFontName(CommonUtility::getLocalString("CommonFont"));
    m_pBackBtn->setTitleColor(color);
    m_pBackBtn->setTitleFontSize(24);
    m_pBackBtn->setTitleText(CommonUtility::getLocalString("Back"));
    m_pBackBtn->setColor(color);
    m_pBackBtn->setVisible(false);
    this->addChild(m_pBackBtn);
    
    m_pTableView->reloadData();
}
cocos2d::Size HelpInfoUI::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return Director::getInstance()->getVisibleSize();
}
cocos2d::extension::TableViewCell* HelpInfoUI::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    CCLOG("%zd",idx);
    Size size = Director::getInstance()->getVisibleSize();
    Color3B color = SceneFactory::getInstance()->getSceneColor();
    TableViewCell *cell = table->cellAtIndex(idx);
    if (!cell) {
        cell = TableViewCell::create();
        cell->setCascadeColorEnabled(true);
        cell->setColor(color);
        switch (idx) {
            case 0:
                {
                    Label* desc = Label::createWithTTF(CommonUtility::getLocalString("GameDesc"),CommonUtility::getLocalString("CommonFont"), 25, Size(550, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    desc->setPosition(Vec2(size.width*0.62f, size.height*0.5f));
                    cell->addChild(desc);
                    
                    Sprite *conwaySprite = Sprite::create("Conway.png");
                    conwaySprite->setPosition(Vec2(size.width*0.2f, size.height*0.5f));
                    cell->addChild(conwaySprite);
                }
                break;
            case 1:
                {
                    Label* gameRule = Label::createWithTTF(CommonUtility::getLocalString("GameRule"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    gameRule->setPosition(Vec2(size.width*0.5f, size.height*0.62f));
                    cell->addChild(gameRule);
                    
                    Label* detail = Label::createWithTTF(CommonUtility::getLocalString("GameRuleDetail"),CommonUtility::getLocalString("CommonFont"), 22, Size(660, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    detail->setPosition(Vec2(size.width*0.6f, size.height*0.435f));
                    
                    cell->addChild(detail);
                    
                    Label* ruleEnd = Label::createWithTTF(CommonUtility::getLocalString("GameRuleEnd"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    ruleEnd->setPosition(Vec2(size.width*0.5f, size.height*0.15f));
                    cell->addChild(ruleEnd);
                    
                    Animation *animation = Animation::create();
                    for (int i = 1; i <= 2; i++)
                    {
                        std::string str = String::createWithFormat("sample%d.png",i)->getCString();
                        animation->addSpriteFrameWithFile(str);
                    }
                    animation->setDelayPerUnit(0.5f);
                    animation->setRestoreOriginalFrame(true);
                    
                    Animate *action = Animate::create(animation);
                    Sprite *sampleSprite = Sprite::create();
                    sampleSprite->setPosition(Vec2(size.width*0.15f, size.height*0.53f));
                    sampleSprite->setScale(0.3f);
                    sampleSprite->runAction(RepeatForever::create(action));
                    cell->addChild(sampleSprite);
                }
                break;
            case 2:
                {
                    Label* patterns = Label::createWithTTF(CommonUtility::getLocalString("Patterns"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    patterns->setPosition(Vec2(size.width*0.5f, size.height*0.6f));
                    cell->addChild(patterns);
                    
                    Label* stillLifes = Label::createWithTTF(CommonUtility::getLocalString("Stable"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    stillLifes->setPosition(Vec2(size.width*0.5f, size.height*0.52f));
                    cell->addChild(stillLifes);
                    
                    Label* oscillators = Label::createWithTTF(CommonUtility::getLocalString("Oscillating"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    oscillators->setPosition(Vec2(size.width*0.5f, size.height*0.21f));
                    cell->addChild(oscillators);
                    
                    Sprite *stilllife1 = Sprite::create("stilllife1.png");
                    stilllife1->setPosition(Vec2(size.width*0.2f, size.height*0.58f));
                    stilllife1->setScale(0.3f);
                    cell->addChild(stilllife1);
                    
                    Sprite *stilllife2 = Sprite::create("stilllife2.png");
                    stilllife2->setPosition(Vec2(size.width*0.4f, size.height*0.58f));
                    stilllife2->setScale(0.3f);
                    cell->addChild(stilllife2);
                    
                    Sprite *stilllife3 = Sprite::create("stilllife3.png");
                    stilllife3->setPosition(Vec2(size.width*0.6f, size.height*0.58f));
                    stilllife3->setScale(0.3f);
                    cell->addChild(stilllife3);
                    
                    Sprite *stilllife4 = Sprite::create("stilllife4.png");
                    stilllife4->setPosition(Vec2(size.width*0.8f, size.height*0.58f));
                    stilllife4->setScale(0.3f);
                    cell->addChild(stilllife4);
                    
                    Sprite *oscillators1 = Sprite::create("oscillators1.png");
                    oscillators1->setPosition(Vec2(size.width*0.2f, size.height*0.27f));
                    oscillators1->setScale(0.3f);
                    cell->addChild(oscillators1);
                    
                    Sprite *oscillators2 = Sprite::create("oscillators2.png");
                    oscillators2->setPosition(Vec2(size.width*0.4f, size.height*0.27f));
                    oscillators2->setScale(0.3f);
                    cell->addChild(oscillators2);
                    
                    Sprite *oscillators3 = Sprite::create("oscillators3.png");
                    oscillators3->setPosition(Vec2(size.width*0.6f, size.height*0.27f));
                    oscillators3->setScale(0.3f);
                    cell->addChild(oscillators3);
                    
                }
                break;
            case 3:
                {
                    Label* spaceships = Label::createWithTTF(CommonUtility::getLocalString("Moving"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    spaceships->setPosition(Vec2(size.width*0.5f, size.height*0.6f));
                    cell->addChild(spaceships);
                    
                    Label* chaos = Label::createWithTTF(CommonUtility::getLocalString("Infinite"),CommonUtility::getLocalString("CommonFont"), 22, Size(850, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    chaos->setPosition(Vec2(size.width*0.5f, size.height*0.25f));
                    cell->addChild(chaos);
                    
                    Sprite *spaceships1 = Sprite::create("spaceships1.png");
                    spaceships1->setPosition(Vec2(size.width*0.2f, size.height*0.65f));
                    spaceships1->setScale(0.3f);
                    cell->addChild(spaceships1);
                    
                    Sprite *stilllife2 = Sprite::create("spaceships2.png");
                    stilllife2->setPosition(Vec2(size.width*0.4f, size.height*0.65f));
                    stilllife2->setScale(0.3f);
                    cell->addChild(stilllife2);
                    
                    Sprite *chaos1 = Sprite::create("chaos1.png");
                    chaos1->setPosition(Vec2(size.width*0.2f, size.height*0.3f));
                    chaos1->setScale(0.3f);
                    cell->addChild(chaos1);
                    
                    Sprite *chaos2 = Sprite::create("chaos2.png");
                    chaos2->setPosition(Vec2(size.width*0.4f, size.height*0.3f));
                    chaos2->setScale(0.3f);
                    cell->addChild(chaos2);
                    
                    Sprite *chaos3 = Sprite::create("chaos3.png");
                    chaos3->setPosition(Vec2(size.width*0.6f, size.height*0.3f));
                    chaos3->setScale(0.3f);
                    cell->addChild(chaos3);
                }
                break;
            case 4:
                {
                    Label* webSites = Label::createWithTTF(CommonUtility::getLocalString("WebSites"),CommonUtility::getLocalString("CommonFont"), 25, Size(660, 300), TextHAlignment::LEFT, TextVAlignment::TOP);
                    webSites->setPosition(Vec2(size.width*0.5f, size.height*0.5f));
                    cell->addChild(webSites);
                }
                break;
            default:
                break;
        }
       
    }
    
    return cell;
}
ssize_t HelpInfoUI::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return 5;
}
void HelpInfoUI::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
}
// 点击下一页按钮
void HelpInfoUI::pressNextBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        Size size = Director::getInstance()->getVisibleSize();
        m_pTableView->setContentOffsetInDuration(Vec2(-size.width*m_pCurrentPage,0),0.5f);
        m_pCurrentPage++;
        if(m_pCurrentPage == 2)
        {
            m_pLabelHelpInfo->setString(CommonUtility::getLocalString("GameRules"));
        }
        else if(m_pCurrentPage == 3)
        {
            m_pLabelHelpInfo->setString(CommonUtility::getLocalString("ExampleOfPatterns"));
        }
        else if(m_pCurrentPage == 5)
        {
            m_pLabelHelpInfo->setString(CommonUtility::getLocalString("References"));
            m_pNextBtn->setVisible(false);
            m_pBackBtn->setVisible(true);
            m_pCurrentPage = 1;
        }
    }
}
// 点击返回按钮
void HelpInfoUI::pressBackBtn(Ref* p,TouchEventType eventType)
{
    if(eventType == TouchEventType::ENDED)
    {
        BaseScene* mainScene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
        Director::getInstance()->replaceScene(mainScene);
    }
}