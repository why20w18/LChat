#include "server.hpp"
#include <iostream>

using namespace std;

int main(){

    suint portNo;
    std::string ipAdresi;
    SERVER_DOMAIN sd;
    SERVER_TYPE st;

    char yn;
    cout << "OTOMATIK OLARAK BASLATILSIN MI (y/n) : ";
    cin >> yn;

    if(yn == 'y'){
        ipAdresi = "127.0.0.1";
        portNo = 8080;
        sd = SD_IPV4;
        st = ST_TCP;
    }
    else if(yn == 'n'){

    }

    Server myServer(portNo,ipAdresi,sd,st);
    myServer.serverInfo();
    myServer.serverListen();

    return 0x0;
}