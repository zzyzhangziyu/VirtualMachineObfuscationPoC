#include "../include/main.hpp"
#include <string.h>
#include <fstream>

int loadProtectedCode(BYTE **mc, std::string fileName)
{
    int codeSize;
    std::ifstream fileStream;
    
    fileStream.open(fileName, std::ios::binary);

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
        char byte;
        int counter = 0;

        //std::cout << "[DEBUG] *************" << std::endl;
        while(fileStream.get(byte))
        {
            (*mc)[counter++] = byte;
            //std::cout << "\t<READ> : " << static_cast<uint16_t>((*mc)[counter - 1]) << std::endl;
        }
        //std::cout << "[DEBUG] *************" << std::endl;
        fileStream.close();
    }
    else
    {
        throw 100010;
    }

    return codeSize;
}