//
//  Ref.hpp
//  gll
//
//  Created by lijingwei on 2022/1/7.
//

#ifndef Ref_hpp
#define Ref_hpp

#include <stdio.h>

class Ref {
public:
    Ref() : m_RefCount(0) {}
    virtual ~Ref(){}
    void retain() { m_RefCount++; }
    void release();
    
private:
    unsigned short m_RefCount;
};
#endif /* Ref_hpp */
