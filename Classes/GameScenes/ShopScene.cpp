//
//  ShopScene.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/9.
//
//

#include "ShopScene.h"
#include "UIMgr.h"
#include "UIConst.h"
USING_NS_CC;
//构造
ShopScene::ShopScene()
{
    m_pShopUI = nullptr;
}
//析构
ShopScene::~ShopScene()
{
}
void ShopScene::onEnter()
{
    BaseScene::onEnter();
    m_pShopUI = UIMgr::getInstance()->createUI(SHOP_UI);
}
void ShopScene::onExit()
{
    BaseScene::onExit();
}
// 更新处理
void ShopScene::update(float delta)
{
    BaseScene::update(delta);
    if(m_pShopUI)
        m_pShopUI->update(delta);
}
// 设置场景颜色
void ShopScene::setSceneColor(const cocos2d::Color3B& color)
{
    m_pShopUI->setColor(color);
}