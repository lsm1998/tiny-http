//
// Created by 刘时明 on 2023/12/10.
//

#include "handler.h"

void routeDispatch(HttpRequest &request, int fd, Router *router)
{
    HttpResponse response(fd);

    auto node = router->getRoute(request.method(), request.path());
    if (node.first == nullptr)
    {
        response.setStatusCode(404);
        return;
    }
    for (const auto &param: node.second)
    {
        request.setParam(param.first, param.second);
    }

    auto handler = router->getHandler(request.method(), node.first->getPattern());
    if (handler != nullptr)
    {
        handler(request, response);
    }
}

// 线程的运行函数
void *handler(void *args)
{
    auto clientArgs = reinterpret_cast<ClientArgs *>(args);

    HttpRequest request(clientArgs->fd);
    if (request.isInvalid())
    {
        std::cerr << "Invalid request" << std::endl;
        goto end;
    }

    routeDispatch(request, clientArgs->fd, clientArgs->router);

    end:
    delete clientArgs;
    return nullptr;
}

ClientArgs::~ClientArgs()
{
    // 关闭连接
    close(this->fd);
}
