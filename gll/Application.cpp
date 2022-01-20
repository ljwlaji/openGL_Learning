//
//  Application.cpp
//  gll
//
//  Created by lijingwei on 2022/1/19.
//

#include "Application.hpp"
#include "GLWindow.hpp"

Application* Application::getInstance()
{
    static Application _Application;
    return &_Application;
}

void Application::createWindow(const std::string& name, float width, float height, bool shareGLContext)
{
    GLWindow* window = new GLWindow();
    window->create(name, width, height, (shareGLContext && m_Windows.size()) ? m_Windows.at(INDEX_PRIMARY_WINDOW)->getWindow() : nullptr);
    window->setupContext();
    m_Windows.push_back(window);
}

void Application::run()
{
    while (1)
    {
        if (!m_Windows.size())
            break;
        glfwPollEvents();
        int i = 0;
        do
        {
            GLWindow* curWindow = m_Windows.at(i);
            if (!curWindow->render())
            {
                m_Windows.erase(m_Windows.begin() + i--);
                delete curWindow;
                continue;
            }
        }
        while (++i < m_Windows.size());
    };
}
