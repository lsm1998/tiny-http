//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_CORE_H
#define TINY_HTTP_CORE_H

#include "global.h"
#include "route.h"
#include "tcp_net_util.h"
#include "handler.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

constexpr char *DEFAULT_HOST = (char *) "127.0.0.1";
constexpr int DEFAULT_PORT = 8080;
constexpr bool DEFAULT_BLOCK = true;
constexpr int DEFAULT_BACKLOG = 1024;
constexpr bool DEFAULT_REUSEADDR = true;

extern std::vector<std::string> METHOD_LIST;

class TinyHttpServer
{
public:
    explicit TinyHttpServer() : TinyHttpServer(DEFAULT_HOST, DEFAULT_PORT)
    {}

    explicit TinyHttpServer(std::string host, int port)
            : TinyHttpServer(std::move(host), port, DEFAULT_BLOCK)
    {}

    explicit TinyHttpServer(std::string host, int port, bool block) :
            TinyHttpServer(std::move(host), port, block, DEFAULT_BACKLOG)
    {}

    explicit TinyHttpServer(std::string host, int port, bool block, int backlog)
            : host(std::move(host)), port(port), block(block), backlog(backlog)
    {
        this->router = new Router;
    }

    ~TinyHttpServer();

public:
    void setBlock(bool block);

    void setHost(const std::string &host);

    void setPort(int port);

    void run();

    void addRoute(const std::string &method, const std::string &path, const RouteHandler &handler);

    void addRoute(const std::string &path, const RouteHandler &handler);

    void setStaticDir(const std::string &dir);

private:
    void setServerAddr();

    void bind();

    void listen() const;

    void accept() const;

private:
    std::string host;
    int port;
    bool block;
    int backlog;
    bool reuseaddr;
    int fd;
    struct sockaddr_in server_addr{};
    Router *router;
    bool loop{true};
    std::string staticDir;
};

#endif //TINY_HTTP_CORE_H
