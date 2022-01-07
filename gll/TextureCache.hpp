//
//  TextureCache.hpp
//  gll
//
//  Created by lijingwei on 2022/1/8.
//

#ifndef TextureCache_hpp
#define TextureCache_hpp

#include <stdio.h>
#include <string>
#include <unordered_map>
class Texture2D;
class TextureCache
{
public:
    static TextureCache* getInstance();
    Texture2D* getTextureByPath(const std::string& path);
    void addTexture(const std::string& path, Texture2D* texture);
    void removeTexture(const std::string& path, Texture2D* texture);
private:
    TextureCache(){}
    ~TextureCache(){}
private:
    std::unordered_map<std::string, Texture2D*> m_TextureCache;
};
#endif /* TextureCache_hpp */
