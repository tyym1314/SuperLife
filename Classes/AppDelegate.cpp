#include "AppDelegate.h"
#include "SceneFactory.h"
#include "SimpleAudioEngine.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
    director->setProjection(cocos2d::Director::Projection::_2D);
    
    cocos2d::Size screenSize = glview->getFrameSize();
    cocos2d::Size designSize = cocos2d::Size(960, 640);
    
    std::vector<std::string> searchPaths;
    std::vector<std::string> resDirOrders;
    
    Platform platform = Application::getInstance()->getTargetPlatform();
    if (platform ==  Platform::OS_IPHONE)
    {
        searchPaths.push_back("published-iphone"); // Resources/published-iphone
    }
    else if(platform == Platform::OS_IPAD)
    {
        searchPaths.push_back("published-ipad"); // Resources/published-ipad
    }
    searchPaths.push_back("templates");
    searchPaths.push_back("fonts");
    searchPaths.push_back("levels");
    searchPaths.push_back("ui");
    searchPaths.push_back("sound");
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);
    
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
    
#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("bg.mp3");
    SimpleAudioEngine::getInstance()->playBackgroundMusic("bg.mp3", true);
    SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(0.5f);
    // create a scene. it's an autorelease object
    auto scene = SceneFactory::getInstance()->createSceneByID(SCENE_MENU);
    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
