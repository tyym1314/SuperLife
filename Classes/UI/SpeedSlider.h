//
//  SpeedSlider.h
//  SuperLife
//
//  Created by wang haibo on 14-8-18.
//
//

#ifndef __SuperLife__SpeedSlider__
#define __SuperLife__SpeedSlider__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
class SpeedSlider : public cocos2d::ui::Slider
{
public:
    static SpeedSlider* create();
    
    void setColor(const cocos2d::Color3B& color);
};

#endif /* defined(__SuperLife__SpeedSlider__) */
