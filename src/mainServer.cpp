#include "server.hpp"
#include <iostream>

using namespace std;

int main(){

    suint portNo;
    std::string ipAdresi,familyIP,tipStr;
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

                std::cout << "PORT NO   :";
        cin >> portNo;

        cin.ignore();
        std::cout << "IP ADRESI :";
        getline(cin,ipAdresi);

        std::cout << "IPV4/IPV6 :";
        getline(cin,familyIP);

        if(familyIP == "ip4" || tipStr == "ipv4" || tipStr == "IPV4")
            sd = SD_IPV4;
        
        else if(tipStr == "ip6" || tipStr == "ipv6" || tipStr == "IPV6")
            sd = SD_IPV6;

        std::cout << "TCP/UDP   :";
        getline(cin,tipStr);

        if(tipStr == "tcp" || tipStr == "TCP" || tipStr == "Tcp")
            st = ST_TCP;
        
        else if(tipStr == "udp" || tipStr == "UDP" || tipStr == "Udp")
            st = ST_UDP;

    }

    Server myServer(portNo,ipAdresi,sd,st);
    myServer.serverInfo();
    myServer.serverListen();

    return 0x0;
}