//
// Created by Administrator on 2023/12/11.
//

#include "global.h"
#include "http_response.h"
#include "http_request.h"
#include "core.h"

void demoHandler(const HttpRequest &request, HttpResponse &response)
{
    auto name = request.query("name");
    response.setStatusCode(200);

    response.setHeader("Content-Type", "application/json");

    auto jsonStr = R"({"name" : "lsm" })";
    response.write(jsonStr, strlen(jsonStr));
}

void init(TinyHttpServer &server)
{
    server.addRoute("demo", demoHandler);
    server.addRoute("find", demoHandler);

    // 获取param参数
    server.addRoute("GET", "find/:id", [](const HttpRequest &request, HttpResponse &response)
    {
        std::cout << request.param("id") << std::endl;
        auto jsonStr = std::string(R"({"id" : ")");
        jsonStr = jsonStr + request.param("id") + R"("})";
        response.setHeader("Content-Type", "application/json");
        response.write(jsonStr.c_str(), jsonStr.size());
    });

    // 500错误
    server.addRoute("test500", [](const HttpRequest &request, HttpResponse &response)
    {
        response.setStatusCode(500);
    });

    // 读取JSON数据
    server.addRoute("POST", "submit", [](const HttpRequest &request, HttpResponse &response)
    {
        int len = request.contentLength();
        if (request.contentType() != "application/json" || len == 0)
        {
            response.setStatusCode(500);
            return;
        }
        char *data = new char[len];

        size_t t = request.readBody(data, len);
        if (t <= 0)
        {
            response.setStatusCode(500);
            return;
        }
        data[t] = '\0';

        std::cout << "收到数据" << std::endl;
        std::cout << data << std::endl;

        response.setHeader("Content-Type", "application/json");
        response.write(data, t);
    });
}
