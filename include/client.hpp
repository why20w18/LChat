#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include "common.hpp"
#include "enum.hpp"

class Client{
private:
    suint clientPortNo;
    int clientFD;

    std::string clientName;
    std::string clientConnectIP;
    sockaddr_in connectServerConfig;

    SERVER_DOMAIN cc_sdaf;
    SERVER_TYPE cc_st;
    std::string colorStr;

public:
    
    Client(const std::string &clientName, 
           suint clientPortNo, 
           const std::string &clientConnectIP,
           SERVER_DOMAIN cc_sdaf,
           SERVER_TYPE cc_st);

    ~Client();

    void clientSendMSG(bool isName,const std::string &message = "");
    void clientRecvMSG();

    void clientInfo() ;
    std::string& setColorStr(const std::string& msg,SERVER_STR_COLORS ssc_renk = SSC_KIRMIZI , SERVER_STR_TYPE sst_type = SST_KALIN);
};




#endif //__CLIENT_HPP__