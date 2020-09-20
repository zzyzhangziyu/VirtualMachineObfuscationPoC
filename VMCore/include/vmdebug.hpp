#ifndef _VM_DEBUG
#define _VM_DEBUG

#include "./vmcpu.hpp"

#define LINUX_SOCKET
/*
Not support development on Windows right now!
#define WIN_SOCK
*/

#ifdef LINUX_SOCKET

#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h>

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

#define CMD_RUN 1
#define CMD_STEP 2
#define CMD_SET_PC 3
#define CMD_SET_SP 4
#define CMD_SET_R 5
#define CMD_SET_ZF 6
#define CMD_SET_CF 7

struct MESSAGE_FROM_DEBUGGER
{
    int cmdFlag;
    DWORD value;
};

void serializeMSG(MESSAGE_TO_DEBUGGER *msgPacket, char *data)
{
    //TODO
}

void deserializeMSG(char *data, MESSAGE_TO_DEBUGGER *msgPacket)
{
    //TODO
}

void serializeMSG(MESSAGE_FROM_DEBUGGER *msgPacket, char *data)
{
    //TODO
}

void deserializeMSG(char *data, MESSAGE_FROM_DEBUGGER *msgPacket)
{
    //TODO
}

#define SEND_ALL_DATA 1
#define SEND_ZERO 0
#define SEND_ERROR -1
#define RECIVE_ZERO 0
#define RECIVE_ERROR -1

int sendData(int socket, void *buffer, size_t length)
{
    char *ptr = (char*) buffer;
    int i;

    while (length > 0)
    {
        i = send(socket, ptr, length, 0);
        if (i < 0) return SEND_ERROR;
        else if(i == 0) return SEND_ZERO;
        ptr += i;
        length -= i;
    }
    return SEND_ALL_DATA;
}

int recvData(int socket, void *buffer, size_t length)
{
    char *ptr = (char*) buffer;
    int i;
    int iteration = 0;
    bool loopFinish = false;

    while (!loopFinish)
    {
        i = recv(socket, ptr, length, 0);
        if (i == -1) return RECIVE_ERROR;
        else if(i == 0)
        {
            if(iteration == 0) return RECIVE_ZERO;
            else loopFinish = true;
        }
        ptr += i;
        length -= i;
        ++iteration;
        if(length <= 0) loopFinish = true;
    }
    return i;
}

#endif

#endif