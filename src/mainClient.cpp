#include "client.hpp"
#include "clientCommand.hpp"
#include <iostream>

using namespace std;

int main(){
    string message,clientName,tipStr,familyIP;
    suint portNo;
    std::string ipAdresi;
    SERVER_DOMAIN sd;
    SERVER_TYPE st;

    cout << "NICKNAME: ";
    getline(cin,clientName);

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

    Client client(clientName,portNo,ipAdresi,sd,st);
    client.clientInfo();
    client.clientSendMSG(true); //ISIM SERVERA GONDERILDI
    

    //MESAJLARI AYRI BIR THREAD OLARAK CEKECEGIZ 
    //ASAGIDAKI THREAD RECVMSG ICINDE SONSUZ DONGUDE KALACAK
    thread recvMSGThread(&Client::clientRecvMSG,&client);
    recvMSGThread.detach();
    std::cout << "YARDIM KOMUTU !help\n";
    while(true){
        cout << ">>";
        getline(cin,message);
        
        if(message[0] == '!'){
            switch(commandParser(message)){
                case CC_HELP: cchelp(); break;
                case CC_EXIT: ccexit(); break;
                case CC_MINFO: client.clientInfo(); break;
                case CC_SINFO: ccsinfo(); break; //SERVERDAN GONDER
              
                case CC_ERROR:
                std::cerr << "GECERSIZ KOMUT GIRDINIZ !help KULLANIN\n";
                break;
            }

        }
        
        client.clientSendMSG(false,message);
    }

    return 0x0;
}