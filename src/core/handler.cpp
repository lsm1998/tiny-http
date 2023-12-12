//
// Created by 刘时明 on 2023/12/10.
//

#include "handler.h"
#include <sys/stat.h>

// 处理静态资源
bool staticDispatch(HttpRequest &request, const int &fd, const std::string &staticDir, HttpResponse &response)
{
    if (request.method() != "GET")
    {
        return false;
    }
    std::string path = request.path();
    if (path.length() > 0 && path[0] != '/')
    {
        path = '/' + path;
    }
    path = staticDir + path;

    struct stat fileStat{};
    int ret = stat(path.c_str(), &fileStat);
    if (ret < 0 || S_ISDIR(fileStat.st_mode))
    {
        std::cout << "File not found: " << path << std::endl;
        return false;
    }
    int static_fd = open(path.c_str(), O_RDONLY);
    response.sendfile(eductionContentType(path), static_fd, fileStat.st_size);
    close(static_fd);
    return true;
}

void routeDispatch(HttpRequest &request, const int &fd, Router *router, const std::string &staticDir)
{
    HttpResponse response(fd);

    auto node = router->getRoute(request.method(), request.path());
    size_t isStatic = false;
    if (node.first == nullptr && !(isStatic = staticDispatch(request, fd, staticDir, response)))
    {
        response.setStatusCode(404);
        return;
    } else if (isStatic)
    {
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

    routeDispatch(request, clientArgs->fd, clientArgs->router, clientArgs->staticDir);

    end:
    delete clientArgs;
    return nullptr;
}

ClientArgs::~ClientArgs()
{
    // 关闭连接
    close(this->fd);
}
