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

#define MAX_RECT_NUMBER 10000
#define MAX_QUAD_COMMAND 40000
#define MAX_INDEX_NUMBER 60000
const float displayWidth = 640.0f;
const float displayHeight = 480.0f;
glm::mat4 proj = glm::ortho(0.0f, displayWidth, 0.0f, displayHeight, -1.0f, 1.0f);

std::list<Sprite*> spriteList;
QuadCommand command[MAX_QUAD_COMMAND];
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
    
    GLWindow* GLwindow = new GLWindow();
    GLwindow->create();
    GLFWwindow* window = GLwindow->getWindow();
    GLwindow->setupContext();

    auto VAO = GLwindow->getVAO();
    auto indices = GLwindow->getIndices();
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
