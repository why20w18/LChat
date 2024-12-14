#include "client.hpp"
#include <iostream>

Client::Client(const std::string &clientName,suint clientPortNo,const std::string &clientConnectIP,SERVER_DOMAIN cc_sdaf,SERVER_TYPE cc_st)
{
    this->clientName = clientName;
    this->clientPortNo = clientPortNo;
    this->clientConnectIP = clientConnectIP;
    this->cc_sdaf = cc_sdaf;
    this->cc_st = cc_st;
    this->colorStr = "";

    //CLIENT SOKET FD OPEN
    clientFD = socket(cc_sdaf,cc_st,0);
    if(clientFD == -1){
        perror("\n[CLIENT-ERROR] : SOCKET = ");
        exit(-1);
    }

    //BAGLANILACAK SERVER KONFIGURASYONU
    connectServerConfig.sin_family = cc_sdaf;
    connectServerConfig.sin_addr.s_addr = inet_addr(clientConnectIP.c_str());
    connectServerConfig.sin_port = htons(clientPortNo);
    memset(&connectServerConfig.sin_zero,0,8);

    int connectStatus = connect(clientFD,(sockaddr*)&connectServerConfig,sizeof(sockaddr));
    if(connectStatus == -1){
        perror("\n[CLIENT-ERROR] : CONNECT = ");
        exit(-1);
    }

}

Client::~Client(){
    std::cout << clientName+" CIKIS YAPTINIZ\n";
    if(clientFD != -1)
    close(clientFD);
}

void Client::clientSendMSG(bool isName,const std::string &message){
    int sendStatus = 0;
    if(isName){
        sendStatus = send(clientFD,clientName.c_str(),clientName.size(),0);
        if(sendStatus == -1){
            perror("\n[CLIENT-ERROR] : MESAJ GONDERILEMEDI = ");
        }
    }
    else if(!isName){
        sendStatus = send(clientFD,message.c_str(),message.size(),0);
        if(sendStatus == -1){
            perror("\n[CLIENT-ERROR] : MESAJ GONDERILEMEDI = ");
        }
    }
    
}

void Client::clientRecvMSG(){
    char buffer[1024] = {0};

    while(true){
        int recvBytes = recv(clientFD,buffer,sizeof(buffer),0);

        if(recvBytes <= 0){
            if(recvBytes == 0){
                fprintf(stderr,(setColorStr("\n[CLIENT-ERROR] : ",SSC_MOR,SST_ITALIK)+" SERVER KAPATILDI = ").c_str());
            }
            else if(recvBytes == -1){
                perror("\n[CLIENT-ERROR] : VERI ALINAMADI = ");
            }
            break;
        }
        //GELEN VERIYI CLIENTA GOSTER
        std::cout << buffer << "\n";
        //VERI ALINDIKTAN SONRA SIFIRLA
        memset(buffer,0,sizeof(buffer));
    }

    clientFD = -1;
    close(clientFD);
}




void Client::clientInfo() {


    std::cout << setColorStr("\n-------------------------------------------------------\n");
    std::cout << setColorStr("[CLIENT-INFO]\n",SSC_YESIL,SST_KALIN);
    std::cout << setColorStr("CLIENT ADI                 : ",SSC_MAVI) << clientName << "\n";
    std::cout << setColorStr("CLIENT KIMLIGI             : ",SSC_MAVI) << clientFD << "\n";
    std::cout << setColorStr("CLIENT CONNECTED PORT NO   : ",SSC_MAVI) << clientPortNo << "\n";
    std::cout << setColorStr("CLIENT CONNECTED ADRESI    : ",SSC_MAVI) << clientConnectIP << "\n";

    
    if(cc_sdaf == AF_INET)
    std::cout << setColorStr("CLIENT CONNECTED DOMAIN    : ",SSC_MAVI) << "IPV4" << "\n";    
    else if(cc_sdaf == AF_INET6)
    std::cout << setColorStr("CLIENT CONNECTED DOMAIN    : ",SSC_MAVI) << "IPV6" << "\n";    
    
    if(cc_st == SOCK_STREAM)
    std::cout << setColorStr("CLIENT CONNECTED TIP       : ",SSC_MAVI) << "TCP" << "\n";    
    else if(cc_st == SOCK_DGRAM)
    std::cout << setColorStr("CLIENT CONNECTED TIP       : ",SSC_MAVI) << "UDP" << "\n";    
    std::cout << setColorStr("-------------------------------------------------------\n\n");

}

std::string& Client::setColorStr(const std::string& msg,SERVER_STR_COLORS ssc_renk , SERVER_STR_TYPE sst_type){

    std::string renkKodu = "\033[" + std::to_string(sst_type) + ";" + std::to_string(ssc_renk) + "m";
    std::string bitisKodu = "\033[0m";
    colorStr = renkKodu+msg+bitisKodu;

    return colorStr;
}