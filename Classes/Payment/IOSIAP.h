//
//  IOSIAP.h
//  SuperLife
//
//  Created by wang haibo on 15/1/29.
//
//

#import <Foundation/Foundation.h>
#import <StoreKit/StoreKit.h>

typedef enum {
    PaymentTransactionStatePurchased = 0,
    PaymentTransactionStateFailed,
    PaymentTransactionStateRestored,
    PaymentTransactionStateTimeout,
} IAPResult;
typedef enum {
    RequestSuccees=0,
    RequestFail,
    RequestTimeout,
} ProductRequest;

@interface IOSIAP : NSObject<SKProductsRequestDelegate,SKPaymentTransactionObserver>

- (void) payForProduct: (NSMutableDictionary*) profuctInfo;
- (void) setDebugMode: (BOOL) debug;

@property BOOL debug;

+ (void) onPayResult:(id) obj withRet:(IAPResult) ret withMsg:(NSString*) msg;
+ (void) onRequestProduct:(id)ojb withRet:(ProductRequest) ret withProducts:(NSArray *)products;

/* ---------iap functions-------*/
- (void) requestProducts:(NSString*) paralist;
- (void) setServerMode;
// when complete payment whether success or fail call this function
- (void)finishTransaction:(NSString *)productId;

//SKProductsRequestDelegate needed
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

//SKPaymentTransactionObserver needed
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;
@property (nonatomic,assign) BOOL _isServerMode;
@end
