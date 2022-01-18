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
#include <vector>

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

typedef struct Size
{
    float width;
    float height;
} Size;

class Node : public Ref
{
public:
    Node();
    ~Node();
    
    void setPosition(float x, float y);
    const Vec2& getPosition() const;
    void addTo(Node* parent);
    Node* getParent() const                 { return m_Parent; }
    void setParent(Node* node)              { if (node) m_Parent = node; }
    std::vector<Node*>* getChildren()       { return &m_Children; }
    void addChild(Node* node);
private:
    Vec2 m_Position;
    Node* m_Parent;
    std::vector<Node*> m_Children;
};

#endif /* Node_hpp */
