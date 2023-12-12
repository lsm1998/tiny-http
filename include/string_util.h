//
// Created by Administrator on 2023/12/10.
//

#ifndef TINY_HTTP_STRING_UTIL_H
#define TINY_HTTP_STRING_UTIL_H

#include <typeindex>
#include "global.h"

extern std::map<std::string,std::string> CONTENT_TYPE_MAP;

extern std::vector<std::string> split(const std::string &str, const std::string &delimiter, int n = -1);

extern std::vector<std::string> split(const std::string &str, char token, int n = -1);

template<typename T>
std::string toString(const T &val)
{
    if constexpr (std::is_same_v<T, std::string>)
    {
        return val;
    } else
    {
        std::cout << std::string(typeid(val).name()) << std::endl;
        return "Type: " + std::string(typeid(val).name());
    }
}

extern std::string eductionContentType(const std::string &path);

#endif //TINY_HTTP_STRING_UTIL_H
