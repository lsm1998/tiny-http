//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_HTTP_RESPONSE_H
#define TINY_HTTP_HTTP_RESPONSE_H

#include "global.h"
#include <map>

// 101: "Protocols",
constexpr const char *VERSION = "HTTP/1.1";

constexpr const char *BLANK = " ";

const std::map<int, std::string> CODE_MAP = {
        {101, "Protocols"},
        {200, "OK"},
        {400, "Bad Request"},
        {404, "Not Found"},
        {500, "Internal Server Error"},
};

class HttpResponse
{
public:
    explicit HttpResponse(int fd);

private:
    int fd;
};

#endif //TINY_HTTP_HTTP_RESPONSE_H
