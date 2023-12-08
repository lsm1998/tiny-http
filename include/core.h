//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_CORE_H
#define TINY_HTTP_CORE_H

#include <utility>

#include "gloab.h"

constexpr char *DEFAULT_HOST = (char *) "127.0.0.1";
constexpr int DEFAULT_PORT = 8080;
constexpr bool DEFAULT_BLOCK = true;
constexpr int DEFAULT_LISTEN_SIZE = 1024;

class TinyHttpServer
{
public:
    explicit TinyHttpServer() : TinyHttpServer(DEFAULT_HOST, DEFAULT_PORT)
    {}

    explicit TinyHttpServer(std::string host, int port)
            : TinyHttpServer(std::move(host), port, DEFAULT_BLOCK)
    {}

    explicit TinyHttpServer(std::string host, int port, bool block) :
            TinyHttpServer(std::move(host), port, block, DEFAULT_LISTEN_SIZE)
    {}

    explicit TinyHttpServer(std::string host, int port, bool block, int listenSize)
            : host(std::move(host)), port(port), block(block), listenSize(listenSize)
    {}

public:
    void setBlock(bool block);

    void setHost(const std::string &host);

    void setPort(int port);

    void run();

private:
    std::string host;
    int port;
    bool block;
    int listenSize;
};

#endif //TINY_HTTP_CORE_H
