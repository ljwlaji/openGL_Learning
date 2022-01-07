//
//  main.cpp
//  gll
//
//  Created by lijingwei on 2021/12/3.
//

#include <iostream>
#include "Renderer.hpp"
#include <../includes/GLFW/glfw3.h>
#include <array>


#include "IndexBuffer.hpp"
#include "VertexBuffer.hpp"
#include "VertexArrayObject.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture2D.hpp"
#include <list>
#include <../includes/glm/glm.hpp>
#include <../includes/glm/gtc/matrix_transform.hpp>
#include "Sprite.hpp"

#define MAX_RECT_NUMBER 10000
#define MAX_QUAD_COMMAND 40000
#define MAX_INDEX_NUMBER 60000
const float displayWidth = 640.0f;
const float displayHeight = 480.0f;
glm::mat4 proj = glm::ortho(0.0f, displayWidth, 0.0f, displayHeight, -1.0f, 1.0f);

std::list<Sprite*> spriteList;
typedef struct QuadCommand {
    Vec2 Position; /*8bit*/
    Vec2 UV; /*8bit*/
} QuadCommand;
QuadCommand command[MAX_QUAD_COMMAND];
GLushort indices[MAX_INDEX_NUMBER];
unsigned short offset = 0;
unsigned int timeDiff = 0;
unsigned int renderCount = 0;
static std::array<QuadCommand, 4> createQuadCommand(float x, float y, float width, float height) {
    QuadCommand v0;
    v0.Position = { x, y};
    v0.UV = {0, 0};
    QuadCommand v1;
    v1.Position = { x + width, y};
    v1.UV = {1, 0};
    QuadCommand v2;
    v2.Position = { x + width, y + height};
    v2.UV = {1, 1};
    QuadCommand v3;
    v3.Position = { x, y + height};
    v3.UV = {0, 1};
    return { v0, v1, v2, v3 };
}

void render(const std::list<Sprite*>& spriteList)
{
    unsigned int drawCount = 0;
    unsigned int startIndex = 0;
    (*spriteList.begin())->getShaderProgram()->Bind();
    (*spriteList.begin())->getTexture2D()->Bind();
    unsigned int currShader = 0;
    unsigned int currTextureID = 0;
    Texture2D* texture = nullptr;
    Shader* shader = nullptr;
    for (auto itr : spriteList)
    {
        if (!itr->getTexture2D() || !itr->getShaderProgram())
            continue;
        texture = itr->getTexture2D();
        shader = itr->getShaderProgram();
        if (texture->getRendererID() != currTextureID ||
            shader->getRandererID() != currShader)
        {
            
            // new draw command
            currTextureID = texture->getRendererID();
            currShader = shader->getRandererID();
            if (drawCount)
            {
                GLCall(glDrawElements(GL_TRIANGLES, 6 * drawCount, GL_UNSIGNED_SHORT, (GLvoid*)((startIndex * sizeof(GLushort)))));
                texture->Bind();
                shader->Bind();
                startIndex += drawCount * 6;
                drawCount = 0;
            }
            ++drawCount;
        }
        else
        {
            ++drawCount;
        }
    }
    if (drawCount)
    {
        GLCall(glDrawElements(GL_TRIANGLES, 6 * drawCount, GL_UNSIGNED_SHORT, (GLvoid*)((startIndex * sizeof(GLushort)))));
    }
}

void onUpdate(unsigned int diff)
{
    if (spriteList.empty())
    {
        Shader* shader = Shader::Create("res/shaders/vertex.shader", "res/shaders/fragment.shader");
        shader->setUniform1i("u_Texture2D", 0);
        shader->Bind();
        shader->setUniform4f("u_Color", 1.0f, 1.f, 1.f, 1.0f);
        shader->setUniformMat4f("u_MVP", proj);
        for (int i = 0; i != 1000; i++)
        {
            Sprite* sprite = new Sprite("res/test.png");
            sprite->setShaderProgram(shader);
            sprite->setPosition(100, 100);
            spriteList.push_back(sprite);
            memcpy(&command[offset++ * 4], createQuadCommand(sprite->getPosition().x, sprite->getPosition().y, sprite->getTexture2D()->GetWidth(), sprite->getTexture2D()->GetHeight()).data(), sizeof(QuadCommand) * 4);
        }
        for (int i = 0; i != 1000; i++)
        {
            Sprite* sprite = new Sprite("res/1111_ygfs.png");
            sprite->setShaderProgram(shader);
            sprite->setPosition(100, 100);
            spriteList.push_back(sprite);
            memcpy(&command[offset++ * 4], createQuadCommand(sprite->getPosition().x, sprite->getPosition().y, sprite->getTexture2D()->GetWidth(), sprite->getTexture2D()->GetHeight()).data(), sizeof(QuadCommand) * 4);
        }
        for (int i = 0; i != 1000; i++)
        {
            Sprite* sprite = new Sprite("res/test.png");
            sprite->setShaderProgram(shader);
            sprite->setPosition(100, 100);
            spriteList.push_back(sprite);
            memcpy(&command[offset++ * 4], createQuadCommand(sprite->getPosition().x, sprite->getPosition().y, sprite->getTexture2D()->GetWidth(), sprite->getTexture2D()->GetHeight()).data(), sizeof(QuadCommand) * 4);
        }
        unsigned int size = sizeof(QuadCommand) * 4 * spriteList.size();
        GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, command));
    }
    render(spriteList);
    renderCount++;
    if (timeDiff + diff > 1000)
    {
        timeDiff = 0;
        printf("fps: %d\n", renderCount);
        renderCount = 0;
    }
    else
        timeDiff += diff;
}


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
    GLFWwindow* window = glfwCreateWindow(displayWidth, displayHeight, "Wave Simulation", NULL, NULL);
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
    GLint nrVertexAttrib;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrVertexAttrib);
    std::cout << "从系统支持的顶点属性最大为：" << nrVertexAttrib;
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
    unsigned int VB;
    GLCall(glGenBuffers(1, &VB));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VB));
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(QuadCommand) * MAX_QUAD_COMMAND, nullptr, GL_DYNAMIC_DRAW));
    // end gen vertex buffer
    
    // gen vertex buffer object
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, sizeof(QuadCommand), (const void*)offsetof(QuadCommand, Position));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, sizeof(QuadCommand), (const void*)offsetof(QuadCommand, UV));
    IndexBuffer ib(indices, MAX_INDEX_NUMBER);
    ib.Bind();
    auto begin = std::chrono::high_resolution_clock::now();
    while (!glfwWindowShouldClose(window))
    {
        // Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
        glfwPollEvents();
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        glBindVertexArray(VAO);
        auto now = std::chrono::high_resolution_clock::now();
        onUpdate(std::chrono::duration_cast<std::chrono::milliseconds>(now - begin).count());
        // Swap the screen buffers
        begin = now;
        glfwSwapBuffers(window);
    }
    
    Sprite * spr = nullptr;
    while (!spriteList.empty())
    {
        spr = (*spriteList.begin());
        spriteList.pop_front();
        delete spr;
    }
    
    glfwTerminate();
    return 0;
}
