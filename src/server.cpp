#include "server.hpp"
#include <iostream>

#include <sstream>
#include <ctime>
#include <iomanip>


Server::Server(suint serverPortNo , const std::string serverIP , SERVER_DOMAIN sdaf , SERVER_TYPE st)
{
    //MEMBERLARI TUTUYORUZ ILERIDE ISIMIZE YARAYABILIR
    this->serverPortNo = serverPortNo;
    this->serverIP = serverIP;
    this->sdaf = sdaf;
    this->st = st;
    this->colorStr = "";

    //SERVER SOCKET FD BASLATIYORUZ
    serverFD = socket(sdaf,st,0);
    if(serverFD == -1){
        perror("\n[SERVER-ERROR] : SOCKET = ");
        exit(-1);
    }

    //SOKET KERNELDE TAKILI KALMASIN
    int yes = 1;
    int setSockOptStatus = setsockopt(serverFD,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof(int));
    if(setSockOptStatus == -1){
        perror("\n[SERVER-ERROR] : SETSOCKOPT = ");
        exit(-1);
    }

    //SERVERI YAPILANDIRIYORUZ
    serverConfig.sin_family = sdaf;
    serverConfig.sin_port = htons(serverPortNo); //NETWORK BYTE ORDERA GORE DUZENLEDIK
    serverConfig.sin_addr.s_addr = inet_addr(serverIP.c_str());
    memset(&serverConfig.sin_zero,0,8);

    //PORTU KONFIGURASYONA BAGLAMA
    int bindStatus = bind(serverFD,(sockaddr*)&serverConfig,sizeof(sockaddr));
    if(bindStatus == -1){
        perror("\n[SERVER-ERROR] : BIND = ");
        exit(-1);
    }
}

Server::~Server(){
    if(serverFD != -1)
    close(serverFD);
}

    
void Server::serverListen(){
    int clientChannelFD;
    socklen_t acceptSize = sizeof(sockaddr_in);
    static unsigned short countConnected = 1;
    char clientName[1024];
    int recvBytesClientName;
    std::string infoSendClient(setColorStr("SERVERA BAGLANDINIZ ",SSC_SARI));
    
    //SERVER ARTIK GELEN ISTEKLERI DINLEYEBILIR
    std::cout << setColorStr("\n[SERVER-LOG] : SERVER BASARIYLA BASLATILDI ISTEKLERI DINLIYOR\n",SSC_YESIL,SST_ITALIK);
    int listenStatus = listen(serverFD,BACKLOG_COUNT);
    if(listenStatus == -1){
        perror("\n[SERVER-ERROR] : LISTEN = ");
        exit(-1);
    }
    
    while(true)
    {   
        clientChannelFD = accept(serverFD,(sockaddr*)&clientConfigData,&acceptSize);
        if(clientChannelFD == -1){
            perror("\n[SERVER-ERROR] : ACCEPT = ");
            exit(-1);
        }
        //EGER ISTEK KABUL EDILIRSE ESKI ADI SIFIRLA
        memset(clientName,0,1024);


        //ILETISIM KANALI ACILABILDIYSE CLIENTFD'ye EKLEYELIM
        
        connectedClientList.push_back(clientChannelFD);
        recvBytesClientName = recv(clientChannelFD,clientName,sizeof(clientName),0);
        
        if(recvBytesClientName == -1){
            perror("\n[SERVER-ERROR] : ISIM ALINAMADI = ");
            exit(-1);
        }
        std::string *clientNameStr = new std::string(clientName);
        clientNameMap[clientChannelFD] = *clientNameStr;

        std::cout << setColorStr("[SERVER-LOG-"+std::to_string(countConnected++)+"] : ",SSC_YESIL) << *clientNameStr <<" SERVERA BAGLANDI\n";
        
        //BAGLANAN CLIENTA BAGLANDIGI BILGISINI GONDER
        int sendStatus = send(clientChannelFD, 
        (infoSendClient + *clientNameStr + "\n").c_str(), 
        (infoSendClient + *clientNameStr + "\n").length(), 
        0);
    
    delete clientNameStr;

    std::thread serverRecvThread(&Server::serverRecvMSG, this, clientChannelFD);
    serverRecvThread.detach();
    }

    if(clientChannelFD != -1)
    close(clientChannelFD);

}

//CLIENTIN GONDERDIGI MESAJLARI ALACAGIZ
//BU FONKSIYON AYRI THREADDE CALISTIRILACAK
void Server::serverRecvMSG(int clientChannelFD){
    char buffer[1024];
    int recvBytes = 0;
    std::string perrorMSG("\n[SERVER-ERROR] : "+clientNameMap[clientChannelFD]);
    while(true){ //DIGER MESAJLARI ALACAGIZ
        memset(buffer,0,1024);
        recvBytes = recv(clientChannelFD,buffer,sizeof(buffer),0);
        
        //MESAJ ALINAMADI
        if(recvBytes <=  0){
            if(recvBytes == -1)
                perror((perrorMSG+" MESAJI ALINAMADI").c_str());                
            
            if(recvBytes == 0)
                perror((perrorMSG+" SERVERDAN AYRILDI").c_str());


                //AYRILDIYSA ADINI MAPTEN CIKART VE O ANDA THREADLER AYNI ANDA ERISEMESIN DATA STRUCTSLARA
                {
                std::lock_guard lock(mutex);
                clientNameMap.erase(clientChannelFD);
                for(int i = 0 ; i < connectedClientList.size() ; i++){
                    if(connectedClientList[i] == clientChannelFD)
                    connectedClientList[i] = 0;
                    }
                }

                close(clientChannelFD);
                break;
        }

        buffer[recvBytes] = '\0';
        
        //MESAJ ALINDI SERVERA ALIINDI
        std::string timeDamga = getCurrentTime();

        std::cout << setColorStr("["+timeDamga+"][SERVER-MESSAGE] : ",SSC_SARI) << setColorStr(clientNameMap[clientChannelFD],SSC_MOR) << " : " << buffer << "\n";

        if(strcmp(buffer,"!list") == 0){
            ListFunc(clientChannelFD);
        }

        //MESAJ SERVERDAN TUM CLIENTLARA GONDERILECEK
        serverSendALL(clientChannelFD,"["+timeDamga+"] "+setColorStr(clientNameMap[clientChannelFD],SSC_YESIL,SST_ALTICIZGILI)+": "+std::string(buffer)+"\n");
    }
}
    

void Server::serverSendALL(int senderClientFD , const std::string &message){
    std::lock_guard<std::mutex> lock(mutex); //BU SCOPE ORTAK ERISIMDE KILITLER VE OTOMATIK ACAR

    for(int client : connectedClientList){
        if(client != senderClientFD){
            int sendStatus = send(client,message.c_str(),message.size(),0);
            if(sendStatus == -1){
                perror("[SERVER-ERROR] : DONT SEND ALL = ");
            }
        }
    }
}


void Server::serverInfo(){
    std::cout << setColorStr("\n-------------------------------------------------------\n");
    std::cout << setColorStr("[SERVER-INFO]\n",SSC_YESIL,SST_KALIN);
    std::cout << setColorStr("SERVER KIMLIGI   : ",SSC_MAVI) << serverFD << "\n";
    std::cout << setColorStr("SERVER PORT NO   : ",SSC_MAVI) << serverPortNo << "\n";
    std::cout << setColorStr("SERVER IP ADRESI : ",SSC_MAVI) << serverIP << "\n";
    std::cout << setColorStr("SERVER BACKLOG   : ",SSC_MAVI) << BACKLOG_COUNT << "\n";


    
    if(sdaf == AF_INET)
    std::cout << setColorStr("SERVER DOMAIN    : ",SSC_MAVI) << "IPV4" << "\n";    
    else if(sdaf == AF_INET6)
    std::cout << setColorStr("SERVER DOMAIN    : ",SSC_MAVI) << "IPV6" << "\n";    
    
    if(st == SOCK_STREAM)
    std::cout << setColorStr("SERVER TIP       : ",SSC_MAVI) << "TCP" << "\n";    
    else if(st == SOCK_DGRAM)
    std::cout << setColorStr("SERVER TIP       : ",SSC_MAVI) << "UDP" << "\n";    
    std::cout << setColorStr("-------------------------------------------------------\n\n");
}

void Server::ListFunc(int clientChannelFD){
    char *msg = "ONLINE OLANLAR\n";
    send(clientChannelFD,msg,strlen(msg),0);
    
     for(int i = 0 ; i < connectedClientList.size() ; i++){
        send(clientChannelFD,(clientNameMap[connectedClientList[i]]+"\n").c_str(),clientNameMap[connectedClientList[i]].size()+1,0); 
    }
}

std::string& Server::setColorStr(const std::string& msg,SERVER_STR_COLORS ssc_renk , SERVER_STR_TYPE sst_type){

    std::string renkKodu = "\033[" + std::to_string(sst_type) + ";" + std::to_string(ssc_renk) + "m";
    std::string bitisKodu = "\033[0m";
    colorStr = renkKodu+msg+bitisKodu;

    return colorStr;
}

std::string Server::getCurrentTime(){
    
    auto now = std::chrono::system_clock::now();
    std::time_t now_t = std::chrono::system_clock::to_time_t(now);
    std::tm *local = std::localtime(&now_t);
    
    std::ostringstream osstream;
    osstream << std::put_time(local,"%H:%M:%S");
    return osstream.str();
}
    