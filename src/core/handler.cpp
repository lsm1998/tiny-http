//
// Created by 刘时明 on 2023/12/10.
//

#include "handler.h"
#include "http_response.h"
#include "http_request.h"

void demoHandler(const HttpRequest &request, HttpResponse &response)
{
    auto name = request.query("name");
    response.setStatusCode(200);

    response.setHeader("Content-Type", "application/json");

    auto jsonStr = R"({"name" : "lsm" })";
    response.write(jsonStr, strlen(jsonStr));
}

void routMatch(const HttpRequest &request, int fd)
{
    HttpResponse response(fd);
    if (request.path() == "/demo")
    {
        demoHandler(request, response);
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

    routMatch(request, clientArgs->fd);

    end:
    delete clientArgs;
    return nullptr;
}

ClientArgs::~ClientArgs()
{
    // 关闭连接
    close(this->fd);
}
