//
//  Renderer.hpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <../includes/GLEW/glew.h>

#define ASSERT(x) if (!(x)) assert(false);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError();
bool GLCheckError(const char* funcName, const char* file, int line);

class Renderer {
private:
    
public:
    Renderer();
    ~Renderer();
};
    


#endif /* Renderer_hpp */
