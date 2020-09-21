#ifndef _VM_DEBUG
#define _VM_DEBUG

#include "./vmcpu.hpp"

#define LINUX_SOCKET
/*
Not support development on Windows right now!
#define WIN_SOCK
*/

#ifdef LINUX_SOCKET

#include <string.h>

#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h>

#include "./nethelpers.h"

#define PORT 9313

#define PACKET_TO_DEBUGGER_SIZE sizeof(MESSAGE_TO_DEBUGGER)
#define PACKET_FROM_DEBUGGER_SIZE sizeof(MESSAGE_FROM_DEBUGGER)

struct MESSAGE_TO_DEBUGGER
{
    DWORD R[8];
    unsigned char ZF;
    unsigned char CF;
    DWORD PC;
    DWORD SP;
    BYTE codeData[CODE_DATA_SIZE];
    DWORD stack[STACK_SIZE];
    BYTE dataBuffer[INPUT_BUFFER_SIZE];
};

#define CMD_RUN 100
#define CMD_STEP 101
#define CMD_EXIT 102
#define CMD_SET_PC 103
#define CMD_SET_SP 104
#define CMD_SET_R 105
#define CMD_SET_ZF 106
#define CMD_SET_CF 107

struct MESSAGE_FROM_DEBUGGER
{
    int cmdFlag;
    DWORD value;
};

void serializeMSG(MESSAGE_TO_DEBUGGER *msgPacket, char *dataArray)
{
    DWORD *d1 = (DWORD *) dataArray;
    memcpy(d1, msgPacket->R, 8);    // ????
    
}

void deserializeMSG(char *dataArray, MESSAGE_TO_DEBUGGER *msgPacket)
{
    //TODO
}

void serializeMSG(MESSAGE_FROM_DEBUGGER *msgPacket, char *dataArray)
{
    //TODO
}

void deserializeMSG(char *dataArray, MESSAGE_FROM_DEBUGGER *msgPacket)
{
    //TODO
}

#endif

#endif