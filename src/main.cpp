#include "core.h"

int main()
{
    TinyHttpServer server;
    server.setBlock(true);
    server.setHost("127.0.0.1");
    server.setPort(9999);
    server.run();
    return 0;
}
