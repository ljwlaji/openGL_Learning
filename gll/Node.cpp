//
//  Node.cpp
//  gll
//
//  Created by lijingwei on 2022/1/4.
//

#include "Node.hpp"

Node::Node() : m_Parent(nullptr)
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

void Node::addTo(Node* parent)
{
	if (!parent || getParent())
		return;
	parent->addChild(this);
}

void Node::addChild(Node* child)
{ 
	if (!child) 
		return; 
	m_Children.push_back(child); 
	child->setParent(this);
	child->retain();
}
