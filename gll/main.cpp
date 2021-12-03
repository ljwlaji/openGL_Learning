//
//  main.cpp
//  gll
//
//  Created by lijingwei on 2021/12/3.
//

#include <iostream>
#include <../includes/GLFW/glfw3.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    if (!glfwInit())
        return 0;
//    glfwWindowHint(GLFW_TRANSPARENT_FRAMEBUFFER, GLFW_TRUE);
//    glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
    GLFWwindow* window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return 0;
    }
    
    glfwMakeContextCurrent(window);
    
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.0f, 0.5f);
        glVertex2f(0.5f, -0.5f);
        glEnd();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    std::cout << "Hello, World!\n";
    return 0;
}
