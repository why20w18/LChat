#include "client.hpp"
#include <iostream>
//client main
using namespace std;

int main(){
    string message,clientName;
    cout << "NICKNAME: ";
    getline(cin,clientName);

    Client client(clientName,8080,"127.0.0.1",SD_IPV4,ST_TCP);
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