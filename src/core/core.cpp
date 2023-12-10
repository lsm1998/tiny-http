//
// Created by 刘时明 on 2023/12/9.
//

#include "core.h"

std::vector<std::string> METHOD_LIST = {"GET", "POST", "DELETE", "PUT"};

void TinyHttpServer::run()
{
    // socket
    this->setServerAddr();

    // bind
    this->bind();

    // listen
    this->listen();

    // accept
    this->accept();
}

void TinyHttpServer::setBlock(bool block)
{
    this->block = block;
}

void TinyHttpServer::setHost(const std::string &host)
{
    this->host = host;
}

void TinyHttpServer::setPort(int port)
{
    this->port = port;
}

void TinyHttpServer::setServerAddr()
{
    if ((this->fd = ::socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("reason");
        throw std::runtime_error("setServerAddr fail");
    }
    memset(&this->server_addr, 0, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    inet_aton(this->host.c_str(), &server_addr.sin_addr);
    server_addr.sin_port = htons(this->port);
}

void TinyHttpServer::bind()
{
    int optval = 1;
    if (this->reuseaddr && setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
    {
        perror("reason");
        throw std::runtime_error("setsockopt fail");
    }

    if (::bind(this->fd, (struct sockaddr *) &this->server_addr, sizeof(this->server_addr)) < 0)
    {
        perror("reason");
        throw std::runtime_error("bind fail");
    }
}

void TinyHttpServer::listen() const
{
    // 监听
    if (::listen(this->fd, this->backlog) < 0)
    {
        perror("reason");
        throw std::runtime_error("listen fail");
    }
}

void TinyHttpServer::accept() const
{
    if (netSetBlock(this->fd, this->block ? 0 : 1) < 0)
    {
        throw std::runtime_error("netSetBlock fail");
    }
    std::cout << "start http server on " << this->host << ":" << this->port << "..." << std::endl;
    while (this->loop)
    {
        struct sockaddr_in client_addr{};
        socklen_t len = sizeof(client_addr);
        int client_fd = ::accept(this->fd, (struct sockaddr *) &client_addr, &len);
        if (client_fd < 0)
        {
            perror("fail to accept!");
            continue;
        }
        pthread_t pt;
        auto *args = new ClientArgs;
        args->fd = client_fd;
        args->client_addr = client_addr;
        args->router = this->router;
        int ret = pthread_create(&pt, nullptr, handler, (void *) (args));
        if (ret < 0)
        {
            throw std::runtime_error("pthread_create fail");
        }
        pthread_detach(pt);
    }
}

TinyHttpServer::~TinyHttpServer()
{
    this->loop = false;
    delete this->router;
    close(this->fd);
}

void TinyHttpServer::addRoute(const std::string &path, const RouteHandler &handler)
{
    for (auto &method: METHOD_LIST)
    {
        this->addRoute(method, path, handler);
    }
}

void TinyHttpServer::setStaticDir(const std::string &dir)
{
    this->staticDir = dir;
}

void TinyHttpServer::addRoute(const std::string &method, const std::string &path, const RouteHandler &handler)
{
    if (std::find(METHOD_LIST.begin(), METHOD_LIST.end(), method)->empty())
    {
        throw std::runtime_error("unsupported request method");
    }

    if (!path.empty() && path.at(0) == '/')
    {
        this->router->addRoute(method, path, handler);
    } else
    {
        this->router->addRoute(method, "/" + path, handler);
    }
}
