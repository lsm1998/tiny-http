//
// Created by 刘时明 on 2023/12/9.
//

#include "http_request.h"

HttpRequest::~HttpRequest()
{
    if (this->body)
    {
        delete[] this->body;
    }
}
