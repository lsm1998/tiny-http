//
// Created by 刘时明 on 2023/12/9.
//

#include "http_request.h"

HttpRequest::HttpRequest(int fd)
{
    this->fd = fd;
}

HttpRequest::~HttpRequest()
{
    if (this->body)
    {
        delete[] this->body;
    }
}

HttpRequest::HttpRequest(const HttpRequest &request)
{
    if(request.body && request.length > 0)
    {
        this->body = new char[request.length];
        memcpy(this->body , request.body , request.length);
    }
}

HttpRequest::String HttpRequest::getPath() const
{
    return this->path;
}
