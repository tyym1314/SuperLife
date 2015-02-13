//
//  IOSIAP.m
//  SuperLife
//
//  Created by wang haibo on 15/1/29.
//
//

#import "IOSIAP.h"
#import "Reachability.h"
#include "PaymentMgr.h"
#include "CommonUtility.h"

#define OUTPUT_LOG(...)     if (self.debug) NSLog(__VA_ARGS__);

@implementation IOSIAP
@synthesize debug,_isServerMode;
NSSet * _productIdentifiers;
NSArray *_productArray;
bool _isAddObserver = false;
//productsRequest;
SKProductsRequest * _productsRequest;
//productTransation
NSArray * _transactionArray;
+ (BOOL) checkIAP {
    Reachability* curReach = [Reachability reachabilityForInternetConnection];
    NSParameterAssert([curReach isKindOfClass:[Reachability class]]);
    //监测网络是否可用
    if ([curReach currentReachabilityStatus] == NotReachable) {
        NSString* networkInfo = [NSString stringWithCString:CommonUtility::getLocalString("NetworkAvalid").c_str() encoding:NSUTF8StringEncoding];
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@""
                                                        message:networkInfo
                                                       delegate:self
                                              cancelButtonTitle:@"YES"
                                              otherButtonTitles:nil];
        [alert show];
        return NO;
    }
    //监测 IAP是否可用
    if ([SKPaymentQueue canMakePayments] == NO) {
        NSString* iapInfo = [NSString stringWithCString:CommonUtility::getLocalString("IAPAvalid").c_str() encoding:NSUTF8StringEncoding];
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                        message:iapInfo
                                                       delegate:self
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
        return NO;
    }
    return YES;
}
- (void) payForProduct: (NSMutableDictionary*) cpInfo{
    if([IOSIAP checkIAP])
    {
        //显示网络连接状态
        [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
        NSString * pid = [cpInfo objectForKey:@"productId"];
        SKProduct *skProduct = [self getProductById:pid];
        if(skProduct){
            SKMutablePayment *payment = [SKMutablePayment paymentWithProduct:skProduct];
            [[SKPaymentQueue defaultQueue] addPayment:payment];
            OUTPUT_LOG(@"add PaymentQueue");
        }
    }
}

- (void)restorePurchase {
    if([IOSIAP checkIAP]){
        //显示网络连接状态
        [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
        [[SKPaymentQueue defaultQueue] restoreCompletedTransactions];
    }
}

- (void) setDebugMode: (BOOL) _debug{
    self.debug = _debug;
}

+ (void) onPayResult:(id) obj withRet:(IAPResult) ret withMsg:(NSString*) msg
{
    const char* chMsg = [msg UTF8String];
    PayResultCode cRet = (PayResultCode) ret;
    PaymentMgr::getInstance()->onPayResult(cRet, chMsg);
}
+ (void) onRequestProductResult:(id)obj withRet:(ProductsRequestResult) ret withProducts:(NSArray *)products withMsg:(NSString*) msg{
    const char* chMsg = [msg UTF8String];
    TProductList pdlist;
    if (products) {
        for(SKProduct *product in products){
            TProductInfo info;
            info.insert(std::make_pair("productId", std::string([product.productIdentifier UTF8String])));
            info.insert(std::make_pair("productName", std::string([product.localizedTitle UTF8String])));
            info.insert(std::make_pair("productPrice", std::string([[product.price stringValue] UTF8String])));
            info.insert(std::make_pair("productDesc", std::string([product.localizedDescription UTF8String])));
            pdlist.push_back(info);
        }
    }
    PaymentMgr::getInstance()->onRequestProductsResult(ret,pdlist,chMsg);
}
/*------------------------IAP functions-------------------------------*/
-(void)setServerMode{
    _isServerMode = true;
}
-(void)requestProducts:(NSString*) paramMap{
    if(!_isAddObserver){
        [[SKPaymentQueue defaultQueue] addTransactionObserver:self];
        _isAddObserver = true;
    }
    if([IOSIAP checkIAP]) {
        //显示网络连接状态
        [UIApplication sharedApplication].networkActivityIndicatorVisible = YES;
    
        NSArray *producIdArray = [paramMap componentsSeparatedByString:@","];
        _productIdentifiers = [[NSSet alloc] initWithArray:producIdArray];
        OUTPUT_LOG(@"param is %@",_productIdentifiers);
        _productsRequest = [[SKProductsRequest alloc] initWithProductIdentifiers:_productIdentifiers];
        _productsRequest.delegate = self;
        [_productsRequest start];
    }
}

-(SKProduct *)getProductById:(NSString *)productid{
    for (SKProduct * skProduct in _productArray) {
        if([skProduct.productIdentifier isEqualToString:productid]){
            return skProduct;
        }
    }
    return NULL;
}

- (void)request:(SKRequest *)request didFailWithError:(NSError *)error {
    OUTPUT_LOG(@"Failed to load list of products.");
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    [IOSIAP onRequestProductResult:self withRet:RequestFail withProducts:NULL withMsg:[error description]];
    _productsRequest = nil;
}

//SKProductsRequestDelegate needed
- (void)productsRequest:(SKProductsRequest *)request didReceiveResponse:(SKProductsResponse *)response{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    _productArray = [[NSArray alloc] initWithArray:response.products];
    NSArray * skProducts = response.products;
    for (SKProduct * skProduct in skProducts) {
        OUTPUT_LOG(@"Found product: %@ %@ %0.2f",
                   skProduct.productIdentifier,
                   skProduct.localizedTitle,
                   skProduct.price.floatValue);
    }
    [IOSIAP onRequestProductResult:self withRet:RequestSuccees withProducts:skProducts withMsg:@""];
}

//SKPaymentTransactionObserver needed
- (void)paymentQueue:(SKPaymentQueue *)queue updatedTransactions:(NSArray *)transactions{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    _transactionArray = transactions;
    for (SKPaymentTransaction * transaction in transactions) {
        switch (transaction.transactionState)
        {
            case SKPaymentTransactionStatePurchased:
                [self completeTransaction:transaction];
                break;
            case SKPaymentTransactionStateFailed:
                [self failedTransaction:transaction];
                break;
            case SKPaymentTransactionStateRestored:
                [self restoreTransaction:transaction];
            default:
                break;
        }
    };
}
//SKPaymentTransactionObserver option
- (void)paymentQueue:(SKPaymentQueue *)queue restoreCompletedTransactionsFailedWithError:(NSError *)error{
    OUTPUT_LOG(@"Failed to restore products.");
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                    message:[error description]
                                                   delegate:self
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];
}
//SKPaymentTransactionObserver option
- (void)paymentQueueRestoreCompletedTransactionsFinished:(SKPaymentQueue *)queue{
    [UIApplication sharedApplication].networkActivityIndicatorVisible = NO;
    NSString* iapInfo = [NSString stringWithCString:CommonUtility::getLocalString("RestorePurchaseOK").c_str() encoding:NSUTF8StringEncoding];
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:nil
                                                    message:iapInfo
                                                   delegate:self
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];
}
- (void)completeTransaction:(SKPaymentTransaction *)transaction {
    OUTPUT_LOG(@"completeTransaction...");
    NSString *receipt = nil;
    if(_isServerMode){
        if (floor(NSFoundationVersionNumber) <= NSFoundationVersionNumber_iOS_6_1) {
            // iOS 6.1 or earlier.
            // Use SKPaymentTransaction's transactionReceipt.
            receipt = [self encode:(uint8_t *)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];
            
        } else {
            // iOS 7 or later.
            NSURL *receiptURL = [[NSBundle mainBundle] appStoreReceiptURL];
            NSData *recData = [[NSData dataWithContentsOfURL:receiptURL] base64EncodedDataWithOptions:0];
            receipt = [[NSString alloc] initWithData:recData encoding:NSUTF8StringEncoding];
            if (!receipt) {
                receipt = [self encode:(uint8_t *)transaction.transactionReceipt.bytes length:transaction.transactionReceipt.length];
            }
        }
        [IOSIAP onPayResult:self withRet:PaymentTransactionStatePurchased withMsg:receipt];
    }else{
        [self finishTransaction: transaction.payment.productIdentifier];
        [IOSIAP onPayResult:self withRet:PaymentTransactionStatePurchased withMsg:@""];
    }
    
}

- (void)restoreTransaction:(SKPaymentTransaction *)transaction {
    OUTPUT_LOG(@"restoreTransaction...");
    [self finishTransaction:transaction.payment.productIdentifier];
    [IOSIAP onPayResult:self withRet:PaymentTransactionStateRestored withMsg:transaction.payment.productIdentifier];
}

- (void)failedTransaction:(SKPaymentTransaction *)transaction {
    OUTPUT_LOG(@"failedTransaction...");
    if (transaction.error.code != SKErrorPaymentCancelled)
    {
        OUTPUT_LOG(@"Transaction error: %@", transaction.error.localizedDescription);
        [[[UIAlertView alloc] initWithTitle:@"支付结果" message:transaction.error.localizedDescription delegate:self cancelButtonTitle:@"确定" otherButtonTitles: nil] show];
    }
    
    [self finishTransaction:transaction.payment.productIdentifier];
    [IOSIAP onPayResult:self withRet:PaymentTransactionStateFailed withMsg:@""];
}

-(void) finishTransaction:(NSString *)productId{
    SKPaymentTransaction *transaction = [self getTranscationByProductId:productId];
    if(transaction){
        [[SKPaymentQueue defaultQueue] finishTransaction:transaction];
    }
}
-(SKPaymentTransaction *) getTranscationByProductId:(NSString *)productId{
    for(SKPaymentTransaction *tran in _transactionArray){
        if([tran.payment.productIdentifier isEqualToString:productId]){
            return tran;
        }
    }
    return NULL;
}
- (NSString *)encode:(const uint8_t *)input length:(NSInteger)length {
    static char table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
    
    NSMutableData *data = [NSMutableData dataWithLength:((length + 2) / 3) * 4];
    uint8_t *output = (uint8_t *)data.mutableBytes;
    
    for (NSInteger i = 0; i < length; i += 3) {
        NSInteger value = 0;
        for (NSInteger j = i; j < (i + 3); j++) {
            value <<= 8;
            
            if (j < length) {
                value |= (0xFF & input[j]);
            }
        }
        
        NSInteger index = (i / 3) * 4;
        output[index + 0] =                    table[(value >> 18) & 0x3F];
        output[index + 1] =                    table[(value >> 12) & 0x3F];
        output[index + 2] = (i + 1) < length ? table[(value >> 6)  & 0x3F] : '=';
        output[index + 3] = (i + 2) < length ? table[(value >> 0)  & 0x3F] : '=';
    }
    
    return [[NSString alloc] initWithData:data encoding:NSASCIIStringEncoding] ;
}
@end
