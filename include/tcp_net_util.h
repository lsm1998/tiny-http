//
// Created by 刘时明 on 2023/12/10.
//

#ifndef TINY_HTTP_TCP_NET_UTIL_CPP_H
#define TINY_HTTP_TCP_NET_UTIL_CPP_H

#include "global.h"
#include <fcntl.h>

extern int netSetBlock(int fd, int non_block);

extern size_t readUntilDelimiter(int fd, char delimiter, char *buf, ssize_t len);

#endif //TINY_HTTP_TCP_NET_UTIL_CPP_H
