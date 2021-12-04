//
//  VertexBuffer.hpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#ifndef VertexBuffer_hpp
#define VertexBuffer_hpp

#include <stdio.h>

class VertexBuffer {
private:
    unsigned int m_RendererID;
    
public:
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    
    void Bind() const;
    void UnBind() const;
};

#endif /* VertexBuffer_hpp */
