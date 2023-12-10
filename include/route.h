//
// Created by Administrator on 2023/12/10.
//

#ifndef TINY_HTTP_ROUTE_H
#define TINY_HTTP_ROUTE_H

#include "global.h"
#include "http_request.h"
#include "http_response.h"
#include "trie.h"
#include <functional>
#include <unordered_map>
#include <vector>

using RouteHandler = std::function<void(const HttpRequest &, HttpResponse &)>;

class Router
{
private:
    std::unordered_map<std::string, Node *> roots;
    std::unordered_map<std::string, RouteHandler> handlers;

public:
    explicit Router() = default;

    RouteHandler getHandler(const std::string &method, const std::string &pattern) const;

    std::vector<std::string> parsePattern(const std::string &pattern);

    std::string join(const std::vector<std::string> &parts, size_t start, const std::string &delimiter);

    void addRoute(const std::string &method, const std::string &pattern, RouteHandler handler);

    std::pair<Node *, std::map<std::string, std::string>> getRoute(const std::string &method, const std::string &path);
};

#endif //TINY_HTTP_ROUTE_H
