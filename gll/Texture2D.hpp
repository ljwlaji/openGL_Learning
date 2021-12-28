//
//  Texture2D.hpp
//  gll
//
//  Created by lijingwei on 2021/12/28.
//

#ifndef Texture2D_hpp
#define Texture2D_hpp

#include <stdio.h>
#include <string>

class Texture2D {
    
public:
    Texture2D(const std::string& path);
    ~Texture2D();
    
    
    int GetWidth() const { return m_Width; }
    int GetHeight() const { return m_Height; }
    const char* GetPath() const { return m_Path.c_str(); }
    
    void Bind(unsigned char slot = 0);
    void UnBind();
    
private:
    unsigned int m_RendererID;
    std::string m_Path;
    int m_Width;
    int m_Height;
    unsigned char* m_Data;
    int m_BitsPerPixal;
};


#endif /* Texture2D_hpp */
