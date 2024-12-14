#include "server.hpp"

int main(){

    Server myServer(8080,"127.0.0.1",SD_IPV4,ST_TCP);
    myServer.serverInfo();
    myServer.serverListen();

    return 0x0;
}