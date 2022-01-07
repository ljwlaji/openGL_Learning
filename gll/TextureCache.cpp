//
//  TextureCache.cpp
//  gll
//
//  Created by lijingwei on 2022/1/8.
//

#include "TextureCache.hpp"
#include "Texture2D.hpp"

TextureCache* TextureCache::getInstance()
{
    static TextureCache _TextureCache;
    return &_TextureCache;
}

Texture2D* TextureCache::getTextureByPath(const std::string& path)
{
    if (m_TextureCache.find(path) == m_TextureCache.end())
        return nullptr;
    return m_TextureCache[path];
}

void TextureCache::addTexture(const std::string& path, Texture2D* texture)
{
    if (m_TextureCache.find(path) == m_TextureCache.end())
        m_TextureCache[path] = texture;
}

void TextureCache::removeTexture(const std::string& path, Texture2D* texture)
{
    if (m_TextureCache.find(path) != m_TextureCache.end())
        m_TextureCache.erase(m_TextureCache.find(path));
}

