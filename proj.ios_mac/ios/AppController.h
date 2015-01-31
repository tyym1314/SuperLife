#import <UIKit/UIKit.h>

@class RootViewController;
@class IOSIAP;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;
}

@property(nonatomic, readonly) RootViewController* viewController;
@property(nonatomic, readonly) IOSIAP* iap;

@end

