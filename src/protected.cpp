#include "../include/main.hpp"
#include <string.h>
#include <fstream>

int loadProtectedCode(BYTE **mc, std::string fileName)
{
    int codeSize;
    std::ifstream fileStream(fileName, std::ios::binary);

    if(fileStream.is_open())
    {
        fileStream.seekg(0, fileStream.end);
        codeSize = fileStream.tellg();
        fileStream.seekg(0, fileStream.beg);
        
        if(codeSize > 51200)
        {
            fileStream.close();
            throw 100011;
        }

        *mc = new BYTE[codeSize];
        BYTE byte;
        int counter = 0;
        while(fileStream >> byte)
        {
            *mc[counter++] = byte;
        }
        fileStream.close();
    }
    else
    {
        throw 100010;
    }

    return codeSize;
}