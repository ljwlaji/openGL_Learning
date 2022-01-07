//
//  IndexBuffer.hpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#ifndef IndexBuffer_hpp
#define IndexBuffer_hpp

#include <stdio.h>

class IndexBuffer {
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
public:
    IndexBuffer(unsigned short* data, unsigned int count);
    ~IndexBuffer();
    void Bind() const;
    void UnBind() const;
    
    inline unsigned int getCount() const { return m_Count; }
};

#endif /* IndexBuffer_hpp */
