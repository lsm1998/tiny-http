//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_CORE_H
#define TINY_HTTP_CORE_H

#include "global.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

constexpr char *DEFAULT_HOST = (char *) "127.0.0.1";
constexpr int DEFAULT_PORT = 8080;
constexpr bool DEFAULT_BLOCK = true;
constexpr int DEFAULT_BACKLOG = 1024;

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
    {}

public:
    void setBlock(bool block);

    void setHost(const std::string &host);

    void setPort(int port);

    void run();

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
    int fd;
    struct sockaddr_in server_addr{};
};

#endif //TINY_HTTP_CORE_H
