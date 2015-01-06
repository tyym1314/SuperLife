//
//  CommonUtility.cpp
//  SuperLife
//
//  Created by wang haibo on 15/1/6.
//
//

#include "CommonUtility.h"
USING_NS_CC;

std::string CommonUtility::getLocalString(const char* key)
{
    ValueMap dict;
    LanguageType lt= CCApplication::getInstance()->getCurrentLanguage();
    switch (lt) {
        case LanguageType::CHINESE:
            dict = FileUtils::getInstance()->getValueMapFromFile("chinese.plist");
            CCASSERT(!dict.empty(), "cannot create dictionary");
            break;
            
        default:
            dict = FileUtils::getInstance()->getValueMapFromFile("english.plist");
            CCASSERT(!dict.empty(), "cannot create dictionary");
            break;
    }
    
    Value ret = dict[key];
    
    return ret.asString();
}

void CommonUtility::screenshot(const std::string& fileName,const std::function<void(const std::string&)>& callback)
{
    Image::Format format;
    //进行后缀判断
    if(std::string::npos != fileName.find_last_of(".")){
        auto extension = fileName.substr(fileName.find_last_of("."),fileName.length());
        if (!extension.compare(".png")) {
            format = Image::Format::PNG;
        } else if(!extension.compare(".jpg")) {
            format = Image::Format::JPG;
        } else{
            CCLOG("cocos2d: the image can only be saved as JPG or PNG format");
            return;
        }
    } else {
        CCLOG("cocos2d: the image can only be saved as JPG or PNG format");
        return ;
    }
    //获取屏幕尺寸，初始化一个空的渲染纹理对象
    cocos2d::Size winSize = Director::getInstance()->getWinSize();
    auto renderTexture = RenderTexture::create(winSize.width, winSize.height, Texture2D::PixelFormat::RGBA8888);
    //清空并开始获取
    renderTexture->beginWithClear(0.0f, 0.0f, 0.0f, 0.0f);
    //遍历场景节点对象，填充纹理到RenderTexture中
    Director::getInstance()->getRunningScene()->visit();
    //结束获取
    renderTexture->end();
    //保存文件
    renderTexture->saveToFile(fileName , format);
    //使用schedule在下一帧中调用callback函数
    auto fullPath = FileUtils::getInstance()->getWritablePath() + fileName;
    auto scheduleCallback = [&,fullPath,callback](float dt){
        callback(fullPath);
    };
    auto _schedule = Director::getInstance()->getRunningScene()->getScheduler();
    _schedule->schedule(scheduleCallback, Director::getInstance(), 0.0f,0,0.0f, false, "screenshot");
}