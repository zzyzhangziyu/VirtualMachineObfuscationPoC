#ifndef DEBUGGER_MAIN_HPP
#define DEBUGGER_MAIN_HPP

#include <iostream>
#include "../VMCore/include/opcodes.hpp"
#include "../VMCore/include/vmdebug.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    #include <windows.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #include <stdlib.h>
    #include <stdio.h>

    // Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
    #pragma comment (lib, "Ws2_32.lib")
    #pragma comment (lib, "Mswsock.lib")
    #pragma comment (lib, "AdvApi32.lib")
#endif

#ifdef _LINUX_DEV_ENVIRONMENT
    #include <arpa/inet.h>
#endif

#include <bitset>

#include "../VMCore/include/global.hpp"

/* *****************  FUNCTIONS *****************  */
void printIntro();
void printOptions();

#ifdef _LINUX_DEV_ENVIRONMENT
    void errorSend(int);
    int setLinuxConnection();
#endif
/* **********************************************  */

#endif