//
//  VertexBuffer.cpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#include "VertexBuffer.hpp"

#include "Renderer.hpp"
#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //设置vertex buffer object
    GLCall(glGenBuffers(1, &m_RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::UnBind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}
