//
// Created by 刘时明 on 2023/12/9.
//

#ifndef TINY_HTTP_GLOBAL_H
#define TINY_HTTP_GLOBAL_H

#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <unistd.h>
#include <cstring>

constexpr int MAX_BUF_SIZE = 1024 * 4;

constexpr int OK = 1;
constexpr int FAIL = -1;

// 101: "Protocols",
constexpr const char *VERSION = "HTTP/1.1";

constexpr const char *BLANK = " ";

constexpr const char *SEPARATOR = "\r\n";

constexpr const char *COLON = ":";

#endif //TINY_HTTP_GLOBAL_H
