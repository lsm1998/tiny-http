//
// Created by Administrator on 2023/12/10.
//

#include "trie.h"

Node::Node(std::string part, bool isWild)
{
    this->part = part;
    this->_isWild = isWild;
}

void Node::setPattern(const std::string &pattern)
{
    this->pattern = pattern;
}

std::string Node::getPart() const
{
    return part;
}

bool Node::isWild() const
{
    return this->_isWild;
}

Node *Node::matchChild(const std::string &part) const
{
    for (Node *child: children)
    {
        if (child->getPart() == part || child->isWild())
        {
            return child;
        }
    }
    return nullptr;
}

std::vector<Node *> Node::matchChildren(const std::string &part) const
{
    std::vector<Node *> nodes;
    for (Node *child: children)
    {
        if (child->getPart() == part || child->isWild())
        {
            nodes.push_back(child);
        }
    }
    return nodes;
}

void Node::insert(const std::string &pattern, const std::vector<std::string> &parts, int height)
{
    if (parts.size() == height)
    {
        setPattern(pattern);
        return;
    }
    std::string part = parts[height];
    Node *child = matchChild(part);
    if (child == nullptr)
    {
        child = new Node(part, part[0] == ':' || part[0] == '*');
        children.push_back(child);
    }
    child->insert(pattern, parts, height + 1);
}

Node *Node::search(const std::vector<std::string> &parts, int height)
{
    if (parts.size() == height || getPart()[0] == '*')
    {
        if (getPattern().empty())
        {
            return nullptr;
        }
        return this;
    }
    std::string part = parts[height];
    std::vector<Node *> matchedChildren = matchChildren(part);
    for (Node *child: matchedChildren)
    {
        Node *result = child->search(parts, height + 1);
        if (result != nullptr)
        {
            return result;
        }
    }
    return nullptr;
}
