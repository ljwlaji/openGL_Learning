//
//  Renderer.cpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"
#include "VertexArrayObject.hpp"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* funcName, const char* file, int line)
{
    while (GLenum err = glGetError()) {
        std::cout << "[GLError]: " << file << " in line:" << line << " @function:" << funcName << "error : " << err << std::endl;
        return false;
    }
    return true;
}

void Renderer::Draw(const VertexArrayObject& vb, const IndexBuffer& ib)
{
    vb.Bind();
    ib.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
}

void Renderer::clear()
{
    GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}
