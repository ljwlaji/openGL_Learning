//
//  Sprite.hpp
//  gll
//
//  Created by lijingwei on 2022/1/4.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include "Node.hpp"
#include "Texture2D.hpp"
#include "Shader.hpp"

class Sprite : public Node
{
public:
    Sprite(const std::string& imgPath);
    ~Sprite();
    
    unsigned int getTextureID() const { return m_Texture2D->getRendererID(); }
    Texture2D* getTexture2D() const { return m_Texture2D; }
    void setShaderProgram(Shader* shader) { m_Shader = shader; }
    Shader* getShaderProgram() const { return m_Shader; }
private:
    Vec4 m_Color;
    Texture2D* m_Texture2D;
    Shader* m_Shader;
};
#endif /* Sprite_hpp */
