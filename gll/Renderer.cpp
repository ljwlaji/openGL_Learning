//
//  Renderer.cpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#include "Renderer.hpp"
#include <iostream>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLCheckError(const char* funcName, const char* file, int line)
{
    while (GLenum err = glGetError()) {
        std::cout << "[GLError]: " << file << " in line:" << line << " @function:" << funcName << err << std::endl;
        return false;
    }
    return true;
}

