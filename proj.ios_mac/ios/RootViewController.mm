/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "RootViewController.h"
#import "cocos2d.h"
#import "CCEAGLView.h"
extern "C"{
#import "GADBannerView.h"
}
#import "GADRequest.h"
@implementation RootViewController

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}

*/
// Override to allow orientations other than the default portrait orientation.
// This method is deprecated on ios6
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return UIInterfaceOrientationIsLandscape( interfaceOrientation );
}

// For ios6, use supportedInterfaceOrientations & shouldAutorotate instead
- (NSUInteger) supportedInterfaceOrientations{
#ifdef __IPHONE_6_0
    return UIInterfaceOrientationMaskAllButUpsideDown;
#endif
}

- (BOOL) shouldAutorotate {
    return YES;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
    [super didRotateFromInterfaceOrientation:fromInterfaceOrientation];

    cocos2d::GLView *glview = cocos2d::Director::getInstance()->getOpenGLView();

    if (glview)
    {
        CCEAGLView *eaglview = (CCEAGLView*) glview->getEAGLView();

        if (eaglview)
        {
            CGSize s = CGSizeMake([eaglview getWidth], [eaglview getHeight]);
            cocos2d::Application::getInstance()->applicationScreenSizeChanged((int) s.width, (int) s.height);
        }
    }
}

//fix not hide status on ios7
- (BOOL)prefersStatusBarHidden
{
    return YES;
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];

    // Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

- (void)initAdBannerView {
    hasShowAds = false;
    receiveAdmob = 0;
    iAdBannerView = [[ADBannerView alloc] initWithAdType:ADAdTypeBanner];
    if(iAdBannerView != nil)
    {
        // Initialize the banner at the bottom of the screen.
        CGRect rect = CGRectMake(0, self.view.frame.size.height - iAdBannerView.frame.size.height, iAdBannerView.frame.size.width, iAdBannerView.frame.size.height);
        [iAdBannerView setFrame:rect];
        [iAdBannerView setDelegate:self];
        iAdBannerView.hidden = YES;
        [self.view addSubview:iAdBannerView];
    }
    
    if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) {
        
        CGPoint origin = CGPointMake(0,self.view.frame.size.height - CGSizeFromGADAdSize(kGADAdSizeBanner).height);
        // NOTE:
        // Add your publisher ID here and fill in the GADAdSize constant for the ad
        // you would like to request.
        admobBannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeBanner origin:origin];
    } else {
        CGPoint origin = CGPointMake(0,self.view.frame.size.height - CGSizeFromGADAdSize(kGADAdSizeFullBanner).height);
        // NOTE:
        // Add your publisher ID here and fill in the GADAdSize constant for the ad
        // you would like to request.
        admobBannerView = [[GADBannerView alloc] initWithAdSize:kGADAdSizeFullBanner origin:origin];
    }
    if(admobBannerView != nil)
    {
        admobBannerView.adUnitID = @"ca-app-pub-3628527903442392/8408101866";
        //// Interstitial ca-app-pub-3628527903442392/3838301464
        //admobBannerView.delegate = self;
        [admobBannerView setRootViewController:self];
        admobBannerView.hidden = YES;
        [self.view addSubview:admobBannerView];
        
        //[admobBannerView loadRequest:[self createRequest]];
    }
}
- (void) showAdsView {
    if(admobBannerView != nil)
    {
        admobBannerView.delegate = self;
        [admobBannerView loadRequest:[self createRequest]];
    }
    if(iAdBannerView != nil && iAdBannerView.bannerLoaded == YES)
    {
        iAdBannerView.hidden = NO;
    }
    hasShowAds = true;
}
- (void) hideAdsView {
    if(admobBannerView != nil)
    {
        admobBannerView.delegate = nil;
        admobBannerView.hidden = YES;
    }
    if(iAdBannerView != nil)
    {
        iAdBannerView.hidden = YES;
    }
}
- (void) showRateAppViewCH {
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"chinese" ofType:@"plist"];
    NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
    NSString* rateTitle = [data objectForKey:@"RateTitle"];
    NSString* rateMessage = [data objectForKey:@"RateMessage"];
    NSString* rateNow = [data objectForKey:@"RateNow"];
    NSString* rateNever = [data objectForKey:@"RateNever"];
    NSString* rateLater = [data objectForKey:@"RateLater"];
    [RateThisAppDialog threeButtonLayoutWithTitle:rateTitle
                                          message:rateMessage
                                rateNowButtonText:rateNow
                              rateLaterButtonText:rateLater
                              rateNeverButtonText:rateNever];
}
- (void) showRateAppViewEN {
    NSString *plistPath = [[NSBundle mainBundle] pathForResource:@"english" ofType:@"plist"];
    NSMutableDictionary *data = [[NSMutableDictionary alloc] initWithContentsOfFile:plistPath];
    NSString* rateTitle = [data objectForKey:@"RateTitle"];
    NSString* rateMessage = [data objectForKey:@"RateMessage"];
    NSString* rateNow = [data objectForKey:@"RateNow"];
    NSString* rateNever = [data objectForKey:@"RateNever"];
    NSString* rateLater = [data objectForKey:@"RateLater"];
    [RateThisAppDialog threeButtonLayoutWithTitle:rateTitle
                                          message:rateMessage
                                rateNowButtonText:rateNow
                              rateLaterButtonText:rateLater
                              rateNeverButtonText:rateNever];
}
- (GADRequest *)createRequest {
    GADRequest *request = [GADRequest request];
    // Requests test ads on devices you specify. Your test device ID is printed to the console when
    // an ad request is made.
    request.testDevices = [NSArray arrayWithObjects:
                           GAD_SIMULATOR_ID,                               // Simulator
                           nil];
    return request;
}

#pragma mark ADBannerViewDelegate impl
- (BOOL)bannerViewActionShouldBegin:(ADBannerView *)banner willLeaveApplication:(BOOL)willLeave
{
    NSLog(@"bannerViewActionShouldBegin");
    return YES;
}

- (void)bannerViewActionDidFinish:(ADBannerView *)banner
{
    NSLog(@"bannerViewActionDidFinish");
}

- (void)bannerViewDidLoadAd:(ADBannerView *)banner
{
    NSLog(@"bannerViewActionDidFinish %d",iAdBannerView.bannerLoaded);
    if(hasShowAds)
        iAdBannerView.hidden = NO;
    
    if (admobBannerView != nil)
    {
        [admobBannerView setDelegate:nil];
        [admobBannerView removeFromSuperview];
        admobBannerView = nil;
    }
    [iAdBannerView.superview bringSubviewToFront:iAdBannerView];
}

- (void)bannerView:(ADBannerView *)banner didFailToReceiveAdWithError:(NSError *)error
{
    NSLog(@"didFailToReceiveAdWithError:%@",error);
    iAdBannerView.hidden = YES;
}

#pragma mark GADBannerViewDelegate impl

- (void)adViewDidReceiveAd:(GADBannerView *)adView {
    NSLog(@"Received ad");
    admobBannerView.hidden = NO;
    receiveAdmob++;
    if (receiveAdmob > 5 && iAdBannerView != nil)
    {
        [iAdBannerView setDelegate:nil];
        [iAdBannerView removeFromSuperview];
        iAdBannerView = nil;
    }
    [admobBannerView.superview bringSubviewToFront:admobBannerView];
}

- (void)adView:(GADBannerView *)view
didFailToReceiveAdWithError:(GADRequestError *)error {
    NSLog(@"Failed to receive ad with error: %@", [error localizedFailureReason]);
}

@end
