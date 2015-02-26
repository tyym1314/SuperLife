//
//  PaymentMgr_android.cpp
//  SuperLife
//
//  Created by wang haibo on 15/2/25.
//
//

#include "PaymentMgr.h"
#include "jni/JniHelper.h"
USING_NS_CC;

bool PaymentMgr::m_bPaying = false;
PaymentMgr* g_pPaymentMgrInstance = nullptr;
// 单体
PaymentMgr* PaymentMgr::getInstance()
{
    if( g_pPaymentMgrInstance == nullptr )
    g_pPaymentMgrInstance = new PaymentMgr();
    
    return g_pPaymentMgrInstance;
}
PaymentMgr::PaymentMgr()
:m_pPayResultListener(nullptr)
{
}
PaymentMgr::~PaymentMgr()
{
}

void PaymentMgr::payForProduct(TProductInfo info)
{
    if (m_bPaying)
    {
        CCLOG("Now is paying");
        return;
    }
    
    if (info.empty())
    {
        if (NULL != m_pPayResultListener)
        {
            onPayResult(kPayFail, "Product info error");
        }
        CCLOG("The product info is empty!");
        return;
    }
    else
    {
    }
}
void PaymentMgr::restorePurchase()
{
}
void PaymentMgr::onPayResult(PayResultCode ret, const char* msg)
{
    m_bPaying = false;
    if (m_pPayResultListener != nullptr)
    m_pPayResultListener->onPayResult(ret, msg, m_currentInfo);
    else
    CCLOG("Pay result listener is null!");
    
    m_currentInfo.clear();
    CCLOG("Pay result is : %d(%s)", (int) ret, msg);
}
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
void PaymentMgr::onRequestProductsResult(ProductsRequestResult ret, TProductList info, const char* msg)
{
    if(m_pPayResultListener != nullptr)
    m_pPayResultListener->onRequestProductsResult(ret, info);
    else
    CCLOG("Pay result listener is null!");
    if(ret == RequestSuccees)
    m_ProductList = info;
    CCLOG("request products result is : %d(%s)", (int) ret, msg);
}
#endif
const TProductList& PaymentMgr::getProductList() const
{
    return m_ProductList;
}
void PaymentMgr::setPayResultListener(PayResultListener* listener)
{
    m_pPayResultListener = listener;
}
