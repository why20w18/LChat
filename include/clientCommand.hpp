#ifndef __CLIENT_COMMAND_HPP__
#define __CLIENT_COMMAND_HPP__

#include <string>
#include <iostream>
#include "enum.hpp"

std::string& setColorStr(std::string& msg,SERVER_STR_COLORS ssc_renk = SSC_KIRMIZI , SERVER_STR_TYPE sst_type = SST_KALIN){

    std::string renkKodu = "\033[" + std::to_string(sst_type) + ";" + std::to_string(ssc_renk) + "m";
    std::string bitisKodu = "\033[0m";
    msg = renkKodu+msg+bitisKodu;

    return msg;
}

CLIENT_COMMAND commandParser(const std::string command){
    //GELEN STRING KOMUTU PARSE EDECEK KIYAS YOLUYLA BIR ENUM CEVIRECEK

    if(command == "!help")
    return CC_HELP;
    
    else if(command == "!exit")
    return CC_EXIT;


    else if(command == "!sinfo")
    return CC_SINFO;

    return CC_ERROR;
}


//KOMUTA GORE CAGRILACAK FONKSIYONLAR
void cchelp(){

    std::string tittle= "       ----------------[CLIENT-HELP]----------------\n";
    std::string help  = "!help  =";
    std::string exit  = "!exit  =";
    std::string minfo = "!minfo =";
    std::string sinfo = "!sinfo =";
    std::string list  = "!list  =";

    std::cout << setColorStr(tittle,SSC_MOR);
    std::cout << setColorStr(help,SSC_MAVI)  <<" YARDIM SAYFASINI BASLATIR\n";
    std::cout << setColorStr(exit,SSC_MAVI)  <<" MEVCUT OTURUMU SONLANDIRIR\n";
    std::cout << setColorStr(minfo,SSC_MAVI) <<" MEVCUT OTURUM HAKKINDA INFO VERIR\n";
    std::cout << setColorStr(sinfo,SSC_MAVI) <<" BAGLI OLUNAN SERVER HAKKINDA INFO VERIR\n";
    std::cout << setColorStr(list,SSC_MAVI)  <<" MEVCUT SERVERA BAGLI OLANLARIN LISTESINI VERIR\n";
  
}
void ccexit(){
    exit(EXIT_SUCCESS);
}
void ccsinfo(){

}
void cclist(){
   
}



#endif //__CLIENT_COMMAND_HPP__