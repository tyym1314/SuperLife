//
//  SpeedSlider.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-18.
//
//

#include "SpeedSlider.h"
USING_NS_CC;
SpeedSlider* SpeedSlider::create()
{
    SpeedSlider* widget = new SpeedSlider();
    if (widget && widget->init())
    {
        widget->autorelease();
        return widget;
    }
    CC_SAFE_DELETE(widget);
    return nullptr;
}
void SpeedSlider::setColor(const Color3B& color)
{
    Slider::setColor(color);
    setOpacity(150);
    _slidBallNormalRenderer->setColor(color);
    _slidBallPressedRenderer->setColor(color);
    _slidBallDisabledRenderer->setColor(color);
}