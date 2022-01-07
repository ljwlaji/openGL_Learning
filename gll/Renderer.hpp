//
//  Renderer.hpp
//  gll
//
//  Created by lijingwei on 2021/12/4.
//

#ifndef Renderer_hpp
#define Renderer_hpp

#include <stdio.h>
#include <vector>
#include <../includes/GLEW/glew.h>

class VertexBuffer;
class IndexBuffer;
class VertexArrayObject;

#define ASSERT(x) if (!(x)) assert(false);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError(#x, __FILE__, __LINE__))

void GLClearError();
bool GLCheckError(const char* funcName, const char* file, int line);

class Renderer {
public:
    Renderer() {};
    ~Renderer() {};
    
    void clear();
    void Draw(const VertexArrayObject& vb, const IndexBuffer& ib);
    
    
private:
    
};
    


#endif /* Renderer_hpp */
