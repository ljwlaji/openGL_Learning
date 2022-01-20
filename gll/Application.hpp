//
//  Application.hpp
//  gll
//
//  Created by lijingwei on 2022/1/19.
//

#ifndef Application_hpp
#define Application_hpp

#include <stdio.h>
#include <vector>

#define INDEX_PRIMARY_WINDOW 0

class GLWindow;
class Application {
    Application() {}
    virtual ~Application() {}
    
public:
    static Application* getInstance();
    void run();
    void createWindow(const std::string& name, float width, float height, bool shareGLContext = true);
    
private:
    std::vector<GLWindow*> m_Windows;
};

#endif /* Application_hpp */
