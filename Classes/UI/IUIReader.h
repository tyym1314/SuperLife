//
//  IUIReader.h
//  SuperLife
//
//  Created by wang haibo on 14-8-13.
//
//

#ifndef SuperLife_IUIReader_h
#define SuperLife_IUIReader_h

class IUIReader
{
public:
    virtual void loadUI(const std::string& file) = 0;
};

#endif
