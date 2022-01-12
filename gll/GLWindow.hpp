//
//  GLWindow.hpp
//  gll
//
//  Created by lijingwei on 2022/1/12.
//

#ifndef GLWindow_hpp
#define GLWindow_hpp

#include <stdio.h>
#include "Renderer.hpp"
#include <../includes/GLFW/glfw3.h>
#include <../includes/glm/glm.hpp>
#include <../includes/glm/gtc/matrix_transform.hpp>
#include "Sprite.hpp"
#include "IndexBuffer.hpp"


#define MAX_RECT_NUMBER 10000
#define MAX_QUAD_COMMAND 40000
#define MAX_INDEX_NUMBER 60000


typedef struct QuadCommand {
    Vec2 Position; /*8bit*/
    Vec2 UV; /*8bit*/
} QuadCommand;

class GLWindow {
public:
    GLWindow() {}
    ~GLWindow() {}
    void create()
    {
        indices = new GLushort[MAX_INDEX_NUMBER];
        if (!glfwInit())
            return;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        
        GLFWwindow* window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }
        setWindow(window);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(1);
//        //这个操作必须在makeContextCurrent 之后
        if (glewInit() != GLEW_OK)
            return;
    }
    void setupContext()
    {
        for (int i = 0, n = 0; i < MAX_INDEX_NUMBER; i += 6, n++)
        {
            indices[i]      = n * 4;
            indices[i + 1]  = n * 4 + 1;
            indices[i + 2]  = n * 4 + 2;
            indices[i + 3]  = n * 4 + 2;
            indices[i + 4]  = n * 4;
            indices[i + 5]  = n * 4 + 3;
        }
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
        GLCall(glEnable(GL_BLEND));
        // gen vertex buffer
        GLCall(glGenBuffers(1, &m_VB));
        GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_VB));
        GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(QuadCommand) * MAX_QUAD_COMMAND, nullptr, GL_DYNAMIC_DRAW));
        // end gen vertex buffer
        
        // gen vertex buffer object
        glGenVertexArrays(1, &m_VAO);
        
        glBindVertexArray(m_VAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(QuadCommand), (const void*)offsetof(QuadCommand, Position));
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(QuadCommand), (const void*)offsetof(QuadCommand, UV));
    }
    
    GLFWwindow* getWindow() const { return m_Window; }
    void setWindow(GLFWwindow* window) { m_Window = window; }
    
    GLushort* getIndices() const { return indices; }
    
    unsigned int getVAO() const { return m_VAO; }
    
private:
    GLFWwindow* m_Window;
    GLushort* indices;
    unsigned int m_VAO;
    unsigned int m_VB;
};

#endif /* GLWindow_hpp */
