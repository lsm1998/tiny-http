#include "core.h"
#include "trie.h"

void init(TinyHttpServer &server);

int main(int argc, char *argv[])
{
    TinyHttpServer server;
    server.setBlock(true);
    if (argc > 1)
    {
        server.setHost(argv[1]);
    }
    if (argc > 2)
    {
        server.setPort(std::stoi(argv[2]));
    }
    if (argc > 3)
    {
        server.setStaticDir(argv[3]);
    }
    init(server);
    server.run();
    return 0;
}
