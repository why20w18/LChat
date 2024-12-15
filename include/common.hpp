#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include <string>
#include <vector>
#include <thread>
#include <chrono>

#include <string.h>


#ifdef __linux__
    #include <arpa/inet.h>
    #include <netinet/in.h>
    
    #include <sys/socket.h>
    #include <sys/time.h>
    
    #include <unistd.h>
#endif //__linux__
 

#ifdef _WIN32
    #include <windows.h>
#endif //_WIN32



#endif //__COMMON_HPP__