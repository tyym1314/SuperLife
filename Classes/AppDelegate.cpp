#include "AppDelegate.h"
#include "SceneFactory.h"
USING_NS_CC;

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
    
    Size screenSize = glview->getFrameSize();
    Size designSize = Size(960, 640);
    
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
    
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    FileUtils::getInstance()->setSearchResolutionsOrder(resDirOrders);
    
    glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::SHOW_ALL);
    
#if COCOS2D_DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

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
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
