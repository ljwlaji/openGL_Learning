//
//  IndexBuffer.cpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#include "IndexBuffer.hpp"
#include "Renderer.hpp"
#include <iostream>

IndexBuffer::IndexBuffer(unsigned short* data, unsigned int count) : m_Count(count)
{
    assert(sizeof(int) == sizeof(GLuint));
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GL_UNSIGNED_SHORT), data, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::UnBind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
