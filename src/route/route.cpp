//
// Created by Administrator on 2023/12/10.
//

#include "route.h"

std::vector<std::string> Router::parsePattern(const std::string &pattern)
{
    std::vector<std::string> parts;
    std::istringstream iss(pattern);
    std::string item;
    while (std::getline(iss, item, '/'))
    {
        if (!item.empty())
        {
            parts.push_back(item);
            if (item[0] == '*')
            {
                break;
            }
        }
    }
    return parts;
}

std::string Router::join(const std::vector<std::string> &parts, size_t start, const std::string &delimiter)
{
    std::string result;
    for (size_t i = start; i < parts.size(); i++)
    {
        result += parts[i];
        if (i != parts.size() - 1)
        {
            result += delimiter;
        }
    }
    return result;
}

void Router::addRoute(const std::string &method, const std::string &pattern, RouteHandler handler)
{
    std::vector<std::string> parts = parsePattern(pattern);
    std::string key = method + "-" + pattern;
    if (roots.find(method) == roots.end())
    {
        roots[method] = new Node("", false);
    }
    roots[method]->insert(pattern, parts, 0);
    handlers[key] = std::move(handler);
}

std::pair<Node *, std::map<std::string, std::string>>
Router::getRoute(const std::string &method, const std::string &path)
{
    std::vector<std::string> searchParts = parsePattern(path);
    std::map<std::string, std::string> params;
    auto it = roots.find(method);
    if (it == roots.end())
    {
        return {nullptr, params};
    }
    Node *root = it->second;
    Node *n = root->search(searchParts, 0);
    if (n != nullptr)
    {
        std::vector<std::string> parts = parsePattern(n->getPattern());
        for (size_t i = 0; i < parts.size(); i++)
        {
            if (parts[i][0] == ':')
            {
                params[parts[i].substr(1)] = searchParts[i];
            }
            if (parts[i][0] == '*' && parts[i].length() > 1)
            {
                params[parts[i].substr(1)] = join(searchParts, i, "/");
                break;
            }
        }
        return {n, params};
    }
    return {nullptr, params};
}

RouteHandler Router::getHandler(const std::string &method, const std::string &pattern) const
{
    auto it = handlers.find(method + '-' + pattern);
    if (it == handlers.end())
    {
        return nullptr;
    }
    return it->second;
}
