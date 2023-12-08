//
// Created by 刘时明 on 2023/12/9.
//

#include "core.h"

void TinyHttpServer::run()
{

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
