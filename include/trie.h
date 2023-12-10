//
// Created by Administrator on 2023/12/10.
//

#ifndef TINY_HTTP_TRIE_H
#define TINY_HTTP_TRIE_H

#include <functional>
#include "global.h"

class Node
{
private:
    std::string pattern{};
    std::string part{};
    std::vector<Node *> children;
    bool _isWild{};

public:
    explicit Node(std::string part, bool isWild = false);

    [[nodiscard]] std::string getPattern() const
    {
        return pattern;
    }

    void setPattern(const std::string &pattern);

    [[nodiscard]] std::string getPart() const;

    [[nodiscard]] bool isWild() const;

    [[nodiscard]] Node *matchChild(const std::string &part) const;

    [[nodiscard]] std::vector<Node *> matchChildren(const std::string &part) const;

    void insert(const std::string &pattern, const std::vector<std::string> &parts, int height);

    Node *search(const std::vector<std::string> &parts, int height);
};

#endif //TINY_HTTP_TRIE_H
