//
//  EncrytionUtility.cpp
//  SuperLife
//
//  Created by wang haibo on 14-8-22.
//
//

#include "EncrytionUtility.h"
USING_NS_CC;

bool EncrytionUtility::getBoolForKey(const char* pKey)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getBoolForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    return Value(UserDefault::getInstance()->getStringForKey(key.c_str())).asBool();
#endif
}
bool EncrytionUtility::getBoolForKey(const char* pKey, bool defaultValue)
{
#ifdef DEBUG
    return getBoolForKey(pKey, defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    return Value(UserDefault::getInstance()->getBoolForKey(key.c_str(), defaultValue)).asBool();
#endif
}
int EncrytionUtility::getIntegerForKey(const char* pKey)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getIntegerForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = Value(UserDefault::getInstance()->getIntegerForKey(key.c_str())).asString();
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return Value(value).asInt();
#endif
}
int EncrytionUtility::getIntegerForKey(const char* pKey, int defaultValue)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getIntegerForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = Value(UserDefault::getInstance()->getIntegerForKey(key.c_str(),defaultValue)).asString();
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return Value(value).asInt();
#endif
}
float EncrytionUtility::getFloatForKey(const char* pKey)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getFloatForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = Value(UserDefault::getInstance()->getFloatForKey(key.c_str())).asString();
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return Value(value).asFloat();
#endif
}
float EncrytionUtility::getFloatForKey(const char* pKey, float defaultValue)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getFloatForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = Value(UserDefault::getInstance()->getFloatForKey(key.c_str(),defaultValue)).asString();
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return Value(value).asFloat();
#endif
}
double EncrytionUtility::getDoubleForKey(const char* pKey)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getDoubleForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = Value(UserDefault::getInstance()->getDoubleForKey(key.c_str())).asString();
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return Value(value).asDouble();
#endif
}
double EncrytionUtility::getDoubleForKey(const char* pKey, double defaultValue)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getDoubleForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = Value(UserDefault::getInstance()->getDoubleForKey(key.c_str(),defaultValue)).asString();
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return Value(value).asDouble();
#endif
}
std::string EncrytionUtility::getStringForKey(const char* pKey)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getStringForKey(pKey);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str());
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return value;
#endif
}
std::string EncrytionUtility::getStringForKey(const char* pKey, const std::string & defaultValue)
{
#ifdef DEBUG
    return UserDefault::getInstance()->getStringForKey(pKey,defaultValue);
#else
    std::string key = pKey;
    strXor(key, 0, key.length()-1, PACKAGE_NAME);
    std::string value = UserDefault::getInstance()->getStringForKey(key.c_str(),defaultValue);
    strXor(value, 0, value.length()-1, PACKAGE_NAME);
    return value;
#endif
}


void EncrytionUtility::setBoolForKey(const char* pKey, bool value)
{
}
void EncrytionUtility::setIntegerForKey(const char* pKey, int value)
{
}
void EncrytionUtility::setFloatForKey(const char* pKey, float value)
{
}
void EncrytionUtility::setDoubleForKey(const char* pKey, double value)
{
}
void EncrytionUtility::setStringForKey(const char* pKey, const std::string & value)
{
}

bool EncrytionUtility::strXor(std::string& stream, int begin, int end, const char* secret)
{
    if (begin<0 || end>=stream.length() || begin>end || strlen(secret) == 0)
        return false;
    
    int keyLength = strlen(secret);
    int j = 0;
    for (int i=begin; i<=end; i++)
    {
        if (j>=keyLength)
        {
            j = 0;
        }
        stream[i] = stream[i] ^ secret[j];
        if(stream[i] == '\0')
        {
            stream[i] = secret[j];
        }
        j++;
    }
    
    return true;
}