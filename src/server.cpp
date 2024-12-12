//server.cpp
#include "server.hpp"
        
using namespace std;

//////////////////////////////////////////////////////////////////////SERVER CLASS
Server::Server(servUINT listenerPORT ,const std::string &serverAddr , SERVER_TYPE type , SERVER_SUPPORT_IP ip)
{
    switch(type){
        case ST_TCP:
            this->serverType = SOCK_STREAM;
            break;
        case ST_UDP:
            this->serverType = SOCK_DGRAM;
            break;
    }

    switch(ip){
        case SSI_IPV4: 
            this->serverSupportIP = AF_INET;
            break;
        case SSI_IPV6:
            this->serverSupportIP = AF_INET6;
            break;
    }

    this->serverSupportIP = ip;
    this->serverAddr = serverAddr;
    this->serverPort = listenerPORT;
    
    if((this->serverFD = socket(serverSupportIP,serverType,0)) == -1){
        perror("Server socket FAILED");
        exit(-1);
    }

    myServer.sin_family = serverSupportIP;
    myServer.sin_port = htons(listenerPORT);
    myServer.sin_addr.s_addr = inet_addr(serverAddr.c_str());
    memset(&myServer.sin_zero,'\0',8);
}

bool Server::startServer(){
    if(bind(serverFD,(struct sockaddr*)&myServer,sizeof(myServer)) == -1){
        perror("startServer FAILED:");
        return false;
    }
    return true;
}

void Server::addUserConnection(int userFD){


}

void Server::showServerInfo() const{
    cout << "[SERVER-INFO] : SERVER ADRES : " << serverAddr << endl;
    cout << "[SERVER-INFO] : SERVER PORT  : " << serverPort << endl;
    cout << "[SERVER-INFO] : SERVER FD    : " << serverFD << endl;

    switch(serverType){
    case ST_TCP:
        cout << "[SERVER-INFO] : SERVER TIPI  : " << "TCP" << endl;
    break;
    
    case ST_UDP:
        cout << "[SERVER-INFO] : SERVER TIPI  : " << "UDP" << endl;
    break;
    }

}



//////////////////////////////////////////////////////////////////////ROOM CLASS
Room::Room(servUINT listenerPORT ,const std::string &serverAddr , SERVER_TYPE type , SERVER_SUPPORT_IP ip , const std::string &roomName)
: Server(listenerPORT,serverAddr,type,ip)
{
    this->roomName = roomName;
    connectedServerList.clear();
}     

void Room::addUser(int userFD){
    connectedServerList.push_back(userFD);
    cout << this->roomName << " ADLI ODAYA BIRISI GIRIS YAPTI" << endl;
}

void Room::showRoomInfo() const{
    showServerInfo();
    cout << "[ROOM-INFO]   : ODA ADI      : " << this->roomName << endl;
}

void Room::sendMSG_Room(const std::string &message){}





