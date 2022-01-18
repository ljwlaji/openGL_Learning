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
    while (m_Children.size()) {
        removeChild(*m_Children.begin());
    }
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

void Node::removeFromParent()
{
	if (!getParent())
		return;
	getParent()->removeChild(this);
}

void Node::removeChild(Node* node)
{
	for (int i = 0; i != m_Children.size(); i++)
	{
		if (m_Children.at(i) == node)
		{
			m_Children.erase(m_Children.begin() + i);
            node->release();
			break;
		}
	}
}

