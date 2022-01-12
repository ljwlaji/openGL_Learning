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


unsigned short offset = 0;
unsigned int timeDiff = 0;
unsigned int renderCount = 0;



int main(int argc, const char * argv[]) {
    // insert code here...
    
    GLWindow* GLwindow = new GLWindow();
    GLwindow->create("test Name", 640.f, 480.f);
    GLwindow->setupContext();

    
    auto begin = std::chrono::high_resolution_clock::now();
    while (1)
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        auto now = std::chrono::high_resolution_clock::now();
//        onUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count());
        // Swap the screen buffers
        if (!GLwindow->render())
            break;
        begin = now;
        // glfwSwapBuffers(window);
    }
    return 0;
}
