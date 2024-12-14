#include "client.hpp"
#include <iostream>
//client main
using namespace std;

int main(){
    string message,clientName;
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

        
    }

    Client client(clientName,portNo,ipAdresi,sd,st);
    client.clientInfo();
    client.clientSendMSG(true); //ISIM SERVERA GONDERILDI
    

    //MESAJLARI AYRI BIR THREAD OLARAK CEKECEGIZ 
    //ASAGIDAKI THREAD RECVMSG ICINDE SONSUZ DONGUDE KALACAK
    thread recvMSGThread(&Client::clientRecvMSG,&client);
    recvMSGThread.detach();

    while(true){
        cout << ">>";
        getline(cin,message);
        
        if(message == "!exit"){
            break;
        }    

        client.clientSendMSG(false,message);
    }

    return 0x0;
}