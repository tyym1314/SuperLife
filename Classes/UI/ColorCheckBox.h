//
//  ColorCheckBox.h
//  SuperLife
//
//  Created by wang haibo on 14-8-19.
//
//

#ifndef __SuperLife__ColorCheckBox__
#define __SuperLife__ColorCheckBox__

#include "UICheckBox.h"
class ColorCheckBox : public cocos2d::ui::CheckBox
{
public:
    static ColorCheckBox* create();
    
    void setColor(const cocos2d::Color3B& color);
};

#endif /* defined(__SuperLife__ColorCheckBox__) */
