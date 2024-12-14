#ifndef __ENUM_HPP__
#define __ENUM_HPP__

#include "common.hpp"

typedef unsigned int suint;

#define BACKLOG_COUNT 10

enum SERVER_DOMAIN{
    SD_IPV4 = AF_INET,
    SD_IPV6 = AF_INET6
};

enum SERVER_TYPE{
    ST_TCP = SOCK_STREAM,
    ST_UDP = SOCK_DGRAM
};

enum SERVER_STR_COLORS{
    SSC_SIYAH = 30,	
    SSC_KIRMIZI,
    SSC_YESIL,
    SSC_SARI,
    SSC_MAVI,
    SSC_MOR
};

enum SERVER_STR_TYPE{
    SST_VARSAYILAN = 0,
    SST_KALIN,
    SST_SOLUK,
    SST_ITALIK,
    SST_ALTICIZGILI,
    SST_REVCOLOR = 7
};


#endif //__ENUM_HPP__