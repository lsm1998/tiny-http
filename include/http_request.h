//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_HTTP_REQUEST_H
#define TINY_HTTP_HTTP_REQUEST_H

#include "global.h"
#include "tcp_net_util.h"
#include "string_util.h"

class HttpRequest
{
    using String = std::string;

    using HttpHeader = std::map<String, std::vector<String>>;

    using FormData = HttpHeader;

public:
    explicit HttpRequest(int fd);

    ~HttpRequest();

    HttpRequest(const HttpRequest &request);

    [[nodiscard]] String path() const;

    [[nodiscard]] String method() const;

    [[nodiscard]] bool isInvalid() const;

    [[nodiscard]] String protocol() const;

    [[nodiscard]] String version() const;

    [[nodiscard]] std::vector<String> header(const String &key) const;

    [[nodiscard]] HttpHeader headers() const;

    [[nodiscard]] std::vector<String> query(const String &key) const;

    [[nodiscard]] FormData queryMap() const;

private:
    void parseRequestLine();

    void parseRequestHeader();

    void parseQuery();

private:
    bool _invalid{};

    String _method{};

    String _path{};

    String _protocol{};

    String _version{};

    char *body{};

    int length{};

    HttpHeader _header{};

    FormData _query{};

    FormData form{};

    int fd{};

    String queryRow;
};

#endif //TINY_HTTP_HTTP_REQUEST_H
