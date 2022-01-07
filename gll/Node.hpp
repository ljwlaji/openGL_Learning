//
//  Node.hpp
//  gll
//
//  Created by lijingwei on 2022/1/4.
//

#ifndef Node_hpp
#define Node_hpp

#include <stdio.h>
#include "Ref.hpp"

typedef struct Vec2{
    float x;
    float y;
} Vec2;

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

typedef struct Vec4 {
    float x;
    float y;
    float z;
    float w;
} Vec4;

class Node : public Ref
{
public:
    Node();
    ~Node();
    
    void setPosition(float x, float y);
    const Vec2& getPosition() const;
    
private:
    Vec2 m_Position;
};

#endif /* Node_hpp */
