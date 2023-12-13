//
// Created by 刘时明 on 2023/12/9.
//

#include "http_response.h"
#include <sys/sendfile.h>

const std::map<int, std::string> CODE_MAP = {
        {101, "Protocols"},
        {200, "OK"},
        {400, "Bad Request"},
        {404, "Not Found"},
        {500, "Internal Server Error"},
};

HttpResponse::HttpResponse(int fd)
{
    this->fd = fd;
}

void HttpResponse::done() const
{
    if (this->_isDone)
    {
        return;
    }
    // 先写状态行
    this->writeRespLine();

    // 先写响应头
    this->writeRespHeader();

    // 写响应体
    this->writeRespBody();
}

void HttpResponse::setHeader(const std::string &key, const std::string &value)
{
    this->header[key] = value;
}

HttpResponse::~HttpResponse()
{
    this->done();
}

void HttpResponse::write(const char *data, size_t len)
{
    this->buf.write(data, (int) len);
}

void HttpResponse::setStatusCode(int code)
{
    this->_code = code;
}

void HttpResponse::writeRespLine() const
{
    auto desc = CODE_MAP.find(this->_code)->second;
    auto code = std::to_string(this->_code);
    ::write(this->fd, VERSION, strlen(VERSION));
    ::write(this->fd, BLANK, strlen(BLANK));
    ::write(this->fd, code.c_str(), code.size());
    ::write(this->fd, BLANK, strlen(BLANK));
    ::write(this->fd, desc.c_str(), desc.size());
    ::write(this->fd, SEPARATOR, 2);
}

void HttpResponse::writeRespHeader() const
{
    for (auto &item: this->header)
    {
        this->writeWithKV(item.first, item.second);
    }
}

void HttpResponse::writeRespBody() const
{
    auto data = this->buf.str();
    this->writeWithKV("Content-Length", std::to_string(data.size()));

    ::write(this->fd, SEPARATOR, 2);

    if (data.empty())
    {
        return;
    }
    ::write(this->fd, data.data(), data.size());
}

void HttpResponse::writeWithKV(const std::string &key, const std::string &value) const
{
    ::write(this->fd, key.data(), key.size());
    ::write(this->fd, COLON, 1);
    ::write(this->fd, BLANK, 1);
    ::write(this->fd, value.data(), value.size());
    ::write(this->fd, SEPARATOR, 2);
}

off_t HttpResponse::sendfile(const std::string &contentType, int file_fd, size_t count)
{
    // 发送响应头
    if (!contentType.empty())
    {
        this->setHeader("Content-Type", contentType);
    }
    this->setHeader("Content-Length", std::to_string(count));

    // 先写状态行
    this->writeRespLine();

    // 先写响应头
    this->writeRespHeader();

    // 空行
    ::write(this->fd, SEPARATOR, 2);

    off_t len{};
#ifdef __APPLE__
    if (::sendfile(file_fd, this->fd, 0, &len, nullptr, 0) <0)
#elif __linux__
    if (::sendfile(this->fd, file_fd, &len, count) < 0)
#endif
    {
        perror("sendfile error");
    }
    this->_isDone = true;
    return len;
}

int HttpResponse::getStatusCode() const
{
    return this->_code;
}
