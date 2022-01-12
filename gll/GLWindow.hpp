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
#include <list>
#include <array>
#define MAX_RECT_NUMBER 10000
#define MAX_QUAD_COMMAND 40000
#define MAX_INDEX_NUMBER 60000

typedef struct QuadCommand {
    QuadCommand(){}
    ~QuadCommand(){}
    Vec2 Position; /*8bit*/
    Vec2 UV; /*8bit*/
} QuadCommand;


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
class GLWindow {
public:
    GLWindow() {}
    ~GLWindow() {}
    void create(const std::string& name, float width, float height)
    {
        indices = new GLushort[MAX_INDEX_NUMBER];
        command = new QuadCommand[MAX_QUAD_COMMAND];
        if (!glfwInit())
            return;
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
        m_proj = glm::ortho(0.0f, 640.0f, 0.0f, 480.0f, -1.0f, 1.0f);
        GLFWwindow* window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
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
        m_Stopped = false;
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
        
        glGenBuffers(1, &m_EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, MAX_INDEX_NUMBER * sizeof(GL_UNSIGNED_SHORT), indices, GL_STATIC_DRAW);
    }
    
    void onUpdate()
    {
        int offset = 0;
        if (m_SpriteList.empty())
        {
            Shader* shader = Shader::Create("res/shaders/vertex.shader", "res/shaders/fragment.shader");
            shader->setUniform1i("u_Texture2D", 0);
            shader->Bind();
            shader->setUniform4f("u_Color", 1.0f, 1.f, 1.f, 1.0f);
            shader->setUniformMat4f("u_MVP", m_proj);
            for (int i = 0; i != 1000; i++)
            {
                Sprite* sprite = new Sprite("res/test.png");
                sprite->setShaderProgram(shader);
                sprite->setPosition(100, 100);
                m_SpriteList.push_back(sprite);
                memcpy(&command[offset++ * 4], createQuadCommand(sprite->getPosition().x, sprite->getPosition().y, sprite->getTexture2D()->GetWidth(), sprite->getTexture2D()->GetHeight()).data(), sizeof(QuadCommand) * 4);
            }
            for (int i = 0; i != 1000; i++)
            {
                Sprite* sprite = new Sprite("res/1111_ygfs.png");
                sprite->setShaderProgram(shader);
                sprite->setPosition(100, 100);
                m_SpriteList.push_back(sprite);
                memcpy(&command[offset++ * 4], createQuadCommand(sprite->getPosition().x, sprite->getPosition().y, sprite->getTexture2D()->GetWidth(), sprite->getTexture2D()->GetHeight()).data(), sizeof(QuadCommand) * 4);
            }
            for (int i = 0; i != 1000; i++)
            {
                Sprite* sprite = new Sprite("res/test.png");
                sprite->setShaderProgram(shader);
                sprite->setPosition(100, 100);
                m_SpriteList.push_back(sprite);
                memcpy(&command[offset++ * 4], createQuadCommand(sprite->getPosition().x, sprite->getPosition().y, sprite->getTexture2D()->GetWidth(), sprite->getTexture2D()->GetHeight()).data(), sizeof(QuadCommand) * 4);
            }
            unsigned int size = sizeof(QuadCommand) * 4 * m_SpriteList.size();
            GLCall(glBufferSubData(GL_ARRAY_BUFFER, 0, size, command));
        }
        
        unsigned int drawCount = 0;
        unsigned int startIndex = 0;
        (*m_SpriteList.begin())->getShaderProgram()->Bind();
        (*m_SpriteList.begin())->getTexture2D()->Bind();
        unsigned int currShader = 0;
        unsigned int currTextureID = 0;
        Texture2D* texture = nullptr;
        Shader* shader = nullptr;
        for (auto itr : m_SpriteList)
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
    
    bool render()
    {
        if (m_Stopped)
            return false;
        if (!glfwWindowShouldClose(m_Window))
        {
            glfwPollEvents();
            GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
            GLCall(glClear(GL_COLOR_BUFFER_BIT));
            onUpdate();
            glfwSwapBuffers(m_Window);
        }
        else
        {
            glfwTerminate();
            Sprite * spr = nullptr;
            while (!m_SpriteList.empty())
            {
                spr = (*m_SpriteList.begin());
                m_SpriteList.pop_front();
                delete spr;
            }
            m_Stopped = true;
        }
        return true;
    }
    
    GLFWwindow* getWindow() const { return m_Window; }
    void setWindow(GLFWwindow* window) { m_Window = window; }
    
private:
    GLFWwindow* m_Window;
    GLushort* indices;
    QuadCommand* command;
    unsigned int m_VAO;
    unsigned int m_VB;
    unsigned int m_EBO;
    std::list<Sprite*> m_SpriteList;
    glm::mat4 m_proj;
    bool m_Stopped;
};

#endif /* GLWindow_hpp */
