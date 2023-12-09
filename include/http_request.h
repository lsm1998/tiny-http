//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_HTTP_REQUEST_H
#define TINY_HTTP_HTTP_REQUEST_H

#include "global.h"
#include <map>

class HttpRequest
{
    using String = std::string;

    using HttpHeader = std::map<String, std::vector<String>>;

    using FormData = std::map<String, std::vector<String>>;

public:
    explicit HttpRequest(int fd);

    ~HttpRequest();

    HttpRequest(const HttpRequest& request);

    String getPath() const;

private:
    bool invalid{};

    String method{};

    String path{};

    String version{};

    char *body{};

    int length{};

    HttpHeader header{};

    FormData query{};

    FormData form{};

    int fd{};

private:

};

#endif //TINY_HTTP_HTTP_REQUEST_H
