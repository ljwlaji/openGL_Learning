//
//  Ref.cpp
//  gll
//
//  Created by lijingwei on 2022/1/7.
//

#include "Ref.hpp"


void Ref::release()
{
    if (--m_RefCount == 0)
    {
        delete this;
    }
}
