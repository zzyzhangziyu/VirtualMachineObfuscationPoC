#ifndef VM_NET_HELPERS_H
#define VM_NET_HELPERS_H

#include <unistd.h> 
#include <sys/socket.h> 
#include <netinet/in.h>

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