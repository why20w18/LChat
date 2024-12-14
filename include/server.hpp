#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include "common.hpp"
#include "enum.hpp"
#include <map>
#include <mutex>

class Server{
protected:
    int serverFD;
    suint serverPortNo;

    sockaddr_in serverConfig;
    sockaddr_in clientConfigData;
    std::string serverIP;

    SERVER_DOMAIN sdaf;
    SERVER_TYPE st;

    std::vector<int> connectedClientList;
    std::map<int,std::string> clientNameMap;
    std::mutex mutex;   //KITLEME SENKRONIZASYONU ICIN

    std::string colorStr;

public:
    Server(suint serverPortNo , const std::string serverIP , SERVER_DOMAIN sdaf , SERVER_TYPE st);
    ~Server();

    void serverInfo();
    void serverListen();
    void serverRecvMSG(int clientChannelFD);
    void serverSendALL(int senderClientFD , const std::string &message);
    
    std::string& setColorStr(const std::string& msg,SERVER_STR_COLORS ssc_renk = SSC_KIRMIZI,SERVER_STR_TYPE sst_type = SST_KALIN);
};



#endif //__SERVER_HPP__