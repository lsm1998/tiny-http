//
// Created by 刘时明 on 2023/12/10.
//

#include "handler.h"
#include "http_response.h"
#include "http_request.h"

// 线程的运行函数
void *handler(void *args)
{
    auto clientArgs = reinterpret_cast<ClientArgs *>(args);

    // 循环处理
    HttpRequest request(clientArgs->fd);
    HttpResponse response(clientArgs->fd);

    if (request.getPath() == "/")
    {
    }
    delete clientArgs;
    return nullptr;
}