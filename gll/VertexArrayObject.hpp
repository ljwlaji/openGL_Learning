//
//  VertexArrayObject.hpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#ifndef VertexArrayObject_hpp
#define VertexArrayObject_hpp

#include <stdio.h>
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"

class VertexArrayObject {
private:
    unsigned int m_RendererID;
public:
    VertexArrayObject();
    ~VertexArrayObject();
    
    void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
    
    template<typename T>
    inline void push(T t)
    {
        throw(1);
    };
    
    void Bind() const;
    void UnBind() const;
};
#endif /* VertexArrayObject_hpp */
