//
//  VertexBufferLayout.hpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#ifndef VertexBufferLayout_hpp
#define VertexBufferLayout_hpp

#include <stdio.h>
#include <../includes/GLEW/glew.h>
#include <vector>

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    unsigned char normalized;
    
    static unsigned int GetSizeOfType(unsigned int type)
    {
        switch (type) {
            case GL_FLOAT:          return 4;
            case GL_UNSIGNED_INT:   return 4;
            case GL_UNSIGNED_BYTE:  return 1;
        }
        throw(1);
    }
};

class VertexBufferLayout {
private:
    std::vector<VertexBufferElement> m_Elements;
    unsigned int m_Stride;
public:
    VertexBufferLayout() : m_Stride(0) {}
    ~VertexBufferLayout() {}
    
    
    template<typename T>
    void push(unsigned int count)
    {
        throw(1);
    }
    
    template<>
    void push<float>(unsigned int count)
    {
        m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
    }
    
    template<>
    void push<unsigned int>(unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_INT, count, GL_FALSE});
        m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
    }
    
    template<>
    void push<unsigned char>(unsigned int count)
    {
        m_Elements.push_back({GL_UNSIGNED_BYTE, count, GL_TRUE});
        m_Stride += count *  VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
    }
    
    inline const std::vector<VertexBufferElement>* GetElements() const { return &m_Elements; }
    inline unsigned int getStride() const { return m_Stride; }
};
#endif /* VertexBufferLayout_hpp */
