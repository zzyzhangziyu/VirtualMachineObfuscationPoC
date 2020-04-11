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
        ++codeSize;
        fileStream.seekg(0, fileStream.beg);
        
        if(codeSize > 51200)
        {
            fileStream.close();
            throw 100011;
        }

        *mc = new BYTE[codeSize];
        BYTE byte;
        int counter = 0;

        //std::cout << "[DEBUG] *************" << std::endl;
        while(fileStream >> byte)
        {
            std::cout << " [READ] : " << static_cast<int16_t>(byte) << std::endl;
            (*mc)[counter++] = byte;
        }
        //std::cout << "[DEBUG] *************" << std::endl;
        fileStream.close();
        exit(-1);
    }
    else
    {
        throw 100010;
    }

    return codeSize;
}