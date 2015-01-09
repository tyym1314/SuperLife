//
//  CommonUtility.h
//  SuperLife
//
//  Created by wang haibo on 15/1/6.
//
//

#ifndef __SuperLife__CommonUtility__
#define __SuperLife__CommonUtility__

#include "cocos2d.h"
class CommonUtility
{
public:
    static std::string getLocalString(const char* key);
    static void screenshot(const std::string& fileName,const std::function<void(const std::string&)>& callback);
    static void renderNodeToFile(const std::string& fileName, cocos2d::Node* renderNode, const cocos2d::Vec2& offset, const std::function<void(const std::string&)>& callback);
};


#endif /* defined(__SuperLife__CommonUtility__) */
