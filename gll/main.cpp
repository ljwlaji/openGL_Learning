//
//  main.cpp
//  gll
//
//  Created by lijingwei on 2021/12/3.
//

#include <iostream>
#include <../includes/GLEW/glew.h>
#include <../includes/GLFW/glfw3.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    
    if (!glfwInit())
        return 0;
    
    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }
    
    glfwMakeContextCurrent(window);
    
    //这个操作必须在makeContextCurrent 之后
    if (glewInit() != GLEW_OK)
        return 0;
    
    std::cout << "GL_Version : " << glGetString(GL_VERSION) << std::endl;
    
    float positions[] = {
        -0.5, -0.5,
         0.0,  0.5,
         0.5, -0.5
    };
    unsigned int buffer;
    glGenBuffers(1, &buffer); //number of buffers, return an id of buffer which written in the povide uint pointer
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    //https://www.youtube.com/watch?v=0p9VxImr7Y0&list=PLlrATfBNZ98foTJPJ_Ev03o2oq3-GGOS2&index=4 18:00 glBindBuffer
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    //size 每组vertex长度 这边位置信息始2个float组成一个vertex 所以是2
    //type 单个数据的类型
    //normal 是否需要让数据归一化 bool
    //stride 每组vertex数据的步长 bit为单位 这边为2个float的长度 8
    //pointer pos/tex_cord/color 指代起始位置
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (const void*)0);
    
    
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}
