//
//  Sprite.cpp
//  gll
//
//  Created by lijingwei on 2022/1/4.
//

#include "Sprite.hpp"
#include "TextureCache.hpp"

Sprite::Sprite(const std::string& imgPath) : m_Texture2D(nullptr), m_Shader(nullptr)
{
    if (imgPath.size())
    {
        Texture2D* texture = TextureCache::getInstance()->getTextureByPath(imgPath);
        if (texture)
            m_Texture2D = texture;
        else
            m_Texture2D = new Texture2D(imgPath);
        m_Texture2D->retain();
    }
}


Sprite::~Sprite()
{
    if (m_Texture2D)
        m_Texture2D->release();
    if (m_Shader)
        m_Shader->release();
}


Vec2 Sprite::coverToWorldSpace() const
{
    Vec2 pos;
    const Node* currNode = this;
    do
    {
        pos.x += currNode->getPosition().x;
        pos.y += currNode->getPosition().y;
        /* code */
    } while (currNode = currNode->getParent());
    
    return pos;
}
