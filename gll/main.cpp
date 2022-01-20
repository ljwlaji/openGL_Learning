//
//  main.cpp
//  gll
//
//  Created by lijingwei on 2021/12/3.
//

#include <iostream>
#include <array>


#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include <list>
#include "Sprite.hpp"
#include "GLWindow.hpp"
#include "Application.hpp"


unsigned short offset = 0;
unsigned int timeDiff = 0;
unsigned int renderCount = 0;



int main(int argc, const char * argv[]) {
    // insert code here...
    
    Application* app = Application::getInstance();
    app->createWindow("testName", 640, 480);
    app->createWindow("testName", 640, 480);
    app->run();
//    GLWindow* GLwindow = new GLWindow();
//    GLwindow->create("test Name", 640.f, 480.f);
//    GLwindow->setupContext();
//    
//    GLWindow* GLwindow2 = new GLWindow();
//    GLwindow2->create("test Name2", 640.f, 480.f, GLwindow->getWindow());
//    GLwindow2->setupContext();
//
//    
//    auto begin = std::chrono::high_resolution_clock::now();
//    while (1)
//    {
//        glfwPollEvents();
//        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
//        auto now = std::chrono::high_resolution_clock::now();
////        onUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count());
//        // Swap the screen buffers
//        bool a = GLwindow2->render();
//        bool b = GLwindow->render();
//        if (!a && !b)
//            break;
//        begin = now;
//        // glfwSwapBuffers(window);
//    }
    return 0;
}
