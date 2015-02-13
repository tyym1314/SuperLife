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
} ProductsRequestResult;
typedef enum {
    RestoreSuccees=0,
    RestoreFail,
    RestoreTimeout,
} PurchaseRestoreResult;
@interface IOSIAP : NSObject<SKProductsRequestDelegate,SKPaymentTransactionObserver>
+ (BOOL) checkIAP;
- (void) payForProduct: (NSMutableDictionary*) profuctInfo;
- (void) setDebugMode: (BOOL) debug;
- (void) restorePurchase;

@property BOOL debug;

+ (void) onPayResult:(id) obj withRet:(IAPResult) ret withMsg:(NSString*) msg;
+ (void) onRequestProductResult:(id)ojb withRet:(ProductsRequestResult) ret withProducts:(NSArray *)products withMsg:(NSString*) msg;
/* ---------iap functions-------*/
- (void) requestProducts:(NSString*) paralist;
- (void) setServerMode;
// when complete payment whether success or fail call this function
- (void)finishTransaction:(NSString *)productId;

//SKProductsRequestDelegate needed
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response;

//SKPaymentTransactionObserver needed
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions;

//SKPaymentTransactionObserver option
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error;

//SKPaymentTransactionObserver option
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue;

@property (nonatomic,assign) BOOL _isServerMode;
@end
