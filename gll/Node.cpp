//
//  Node.cpp
//  gll
//
//  Created by lijingwei on 2022/1/4.
//

#include "Node.hpp"

Node::Node()
{
    setPosition(0, 0);
}

Node::~Node()
{
    
}

void Node::setPosition(float x, float y)
{
    m_Position.x = x;
    m_Position.y = y;
}

const Vec2& Node::getPosition() const
{
    return m_Position;
}
