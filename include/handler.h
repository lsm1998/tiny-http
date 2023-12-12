//
// Created by 刘时明 on 2023/12/10.
//

#ifndef TINY_HTTP_HANDLER_H
#define TINY_HTTP_HANDLER_H

#include <netinet/in.h>
#include <functional>
#include "http_response.h"
#include "http_request.h"
#include "route.h"

class ClientArgs
{
public:
    int fd{};
    struct sockaddr_in client_addr{};
    Router* router{};
    std::string staticDir{};

    ~ClientArgs();
};

extern void *handler(void *args);

#endif //TINY_HTTP_HANDLER_H
