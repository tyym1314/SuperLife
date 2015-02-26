//
//  ColorCheckBox.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#include "ColorCheckBox.h"
USING_NS_CC;
ColorCheckBox* ColorCheckBox::create()
{
    ColorCheckBox* widget = new ColorCheckBox();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}

void ColorCheckBox::setColor(const cocos2d::Color3B& color)
{
    CheckBox::setColor(color);
    _backGroundBoxRenderer->setColor(color);
    _backGroundBoxRenderer->setOpacity(127);
    _backGroundSelectedBoxRenderer->setColor(color);
    _frontCrossRenderer->setColor(color);
    
}