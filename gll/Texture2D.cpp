//
//  Texture2D.cpp
//  gll
//
//  Created by lijingwei on 2021/12/28.
//

#include "Texture2D.hpp"
#include "stbImage.hpp"

#include "Renderer.hpp"

Texture2D::Texture2D(const std::string& path) : m_RendererID(0), m_Path(path),
    m_Width(0), m_Height(0), m_BitsPerPixal(0), m_Data(nullptr)
{
    stbi_set_flip_vertically_on_load(1);
    GLCall(glGenTextures(1, &m_RendererID));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID ));
    m_Data = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BitsPerPixal, 4);
    
    
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE ));
    
    
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data ))
    
    if (m_Data)
    {
        stbi_image_free(m_Data);
        m_Data = nullptr;
    }
}

Texture2D::~Texture2D()
{
     GLCall(glDeleteTextures(1, &m_RendererID));
}


void Texture2D::Bind(unsigned char slot)
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture2D::UnBind()
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
