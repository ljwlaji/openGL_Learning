//
//  main.cpp
//  gll
//
//  Created by lijingwei on 2021/12/3.
//

#include <iostream>
#include "Renderer.hpp"
#include <../includes/GLFW/glfw3.h>

#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArrayObject.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"


int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (!glfwInit())
        return 0;
    
//    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
//    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  #ifdef __APPLE__
    std::cout << "I'm apple machine" << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  #endif
    GLFWwindow* window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }
    
    glfwMakeContextCurrent(window);
    
    
    glfwSwapInterval(1);
    //这个操作必须在makeContextCurrent 之后
    if (glewInit() != GLEW_OK)
        return 0;
    
    std::cout << "GL_Version : " << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
        -0.5, -0.5, 0.0f, 0.0f, //0
         0.5, -0.5, 1.0f, 0.0f,//1
         0.5,  0.5, 1.0f, 1.0f,
        -0.5,  0.5, 0.0f, 1.0f,
    };
    
    unsigned int indices[] = {
        0, 1, 2,
        2, 0, 3
    };
    
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
    GLCall(glEnable(GL_BLEND));
    VertexBuffer vb(positions, 4 * 4  * sizeof(float));
    
    IndexBuffer ib(indices, 6);
    
    Renderer renderer;

    VertexArrayObject VAO;
    VertexBufferLayout layout;
    layout.push<float>(2);
    layout.push<float>(2);
    VAO.AddBuffer(vb, layout);
    Shader* shader = Shader::Create("res/shaders/vertex.shader", "res/shaders/fragment.shader");
    Texture2D texture("res/test.png");
    texture.Bind();
    shader->setUniform1i("u_Texture2D", 0);
    shader->Bind();
    shader->setUniform4f("u_Color", 1.0f, 0.2f, 0.2f, 1.0f);
    
    float r = 0.0f;
    float inc = 0.01f;
    
    glBindVertexArray(0);
    glUseProgram(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();

        // Render
        // Clear the colorbuffer
        renderer.clear();
        
        shader->Bind();
        shader->setUniform4f("u_Color", r, 0.2f, 0.2f, 1.0f);
            
        renderer.Draw(VAO, ib);
        
        if (r > 1.0f)
            inc = -0.01f;
        else if (r < 0.0f)
            inc = 0.01f;
        r += inc;
        
        // Swap the screen buffers
        glfwSwapBuffers(window);
    }
    
    delete shader;
    shader = nullptr;
    glfwTerminate();
    return 0;
}
