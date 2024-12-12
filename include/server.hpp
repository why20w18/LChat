//server.hpp
#ifndef __SERVER_H__
#define __SERVER_H__

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

typedef unsigned int servUINT;

//////////////////////////////////////////////////////////////////////PLATFORM BAGIMSIZLIGI
#ifdef __linux__
    #include <unistd.h>

    #include <arpa/inet.h>
    #include <netinet/in.h>
    #include <netdb.h>

    #include <sys/socket.h>
    #include <sys/time.h>
    #include <sys/types.h>
#endif

#ifdef _WIN32
    #include <windows.h>
#endif 

//////////////////////////////////////////////////////////////////////ENUM DEFINES
enum SERVER_TYPE{
    ST_TCP,
    ST_UDP
};

enum SERVER_SUPPORT_IP{
    SSI_IPV4,
    SSI_IPV6
};



//////////////////////////////////////////////////////////////////////CLASS DEKLERASYONLARI
class Server{
    protected:        
        struct sockaddr_in myServer;
    
        servUINT serverPort;
    
        int serverFD; //socket()'in actigi serverin file descriptoru
        int serverType;
        int serverSupportIP;

        std::string serverAddr;

    public:
        Server(servUINT listenerPORT ,const std::string &serverAddr , SERVER_TYPE type , SERVER_SUPPORT_IP ip);        
        bool startServer();
        virtual void addUserConnection(int userFD); //override edilecek Room icinde
        void showServerInfo() const;
};




class Room : public Server{
    private:
         std::vector<int> connectedServerList;
         std::string roomName;

    public:
        Room(servUINT listenerPORT ,const std::string &serverAddr , SERVER_TYPE type , SERVER_SUPPORT_IP ip , const std::string &roomName);        
        void addUser(int userFD);
        void showRoomInfo() const;
        void sendMSG_Room(const std::string &message);
};


#endif 
