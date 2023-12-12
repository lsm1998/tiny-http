//
// Created by Administrator on 2023/12/10.
//

#include "string_util.h"

std::map<std::string, std::string> CONTENT_TYPE_MAP = {
        {"txt",  "text/plain"},
        {"html", "text/html"},
        {"htm",  "text/html"},
        {"css",  "text/css"},
        {"js",   "application/javascript"},
        {"json", "application/json"},
        {"jpg",  "image/jpeg"},
        {"jpeg", "image/jpeg"},
        {"png",  "image/png"},
        {"gif",  "image/gif"},
        {"ico",  "image/x-icon"},
        {"mp3",  "audio/mp3"},
        {"mp4",  "video/mpeg4"},
        {"mpeg", "video/mpeg"},
        {"pdf",  "application/pdf"},
        {"doc",  "application/msword"},
        {"xls",  "application/vnd.ms-excel"},
        {"ppt",  "application/vnd.ms-powerpoint"},
        {"xml",  "text/xml"},
};

std::vector<std::string> split(const std::string &str, const std::string &delimiter, int n)
{
    std::vector<std::string> tokens;

    size_t pos = 0;
    size_t found;
    int count = 1;

    while ((found = str.find(delimiter, pos)) != std::string::npos && (n == -1 || count++ < n))
    {
        tokens.push_back(str.substr(pos, found - pos));
        pos = found + delimiter.size();
    }

    tokens.push_back(str.substr(pos));

    return tokens;
}

std::vector<std::string> split(const std::string &str, char token, int n)
{
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    int count = 0;

    std::string tokenizedPart;
    while (getline(iss, tokenizedPart, token) && (n == -1 || count++ < n))
    {
        tokens.push_back(tokenizedPart);
    }
    return tokens;
}

template<>
std::string toString(const std::vector<std::string> &val)
{
    std::stringstream buf;
    buf.write("[", 1);
    for (auto &item: val)
    {
        buf.write(item.c_str(), static_cast<std::streamsize>(item.size()));
        buf.write(",", 1);
    }
    std::string result = buf.str();
    if (result.size() == 1)
    {
        return "[]";
    }
    result.pop_back();
    result.append("]");
    return result;
}

std::string eductionContentType(const std::string &path)
{
    size_t pos = path.find_last_of('.');
    std::map<std::string, std::string>::iterator iter;
    if (pos == std::string::npos ||
        (iter = CONTENT_TYPE_MAP.find(path.substr(pos + 1))) == CONTENT_TYPE_MAP.end())
    {
        return "application/octet-stream";
    }
    return iter->second;
}