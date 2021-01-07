#include "../include/main.hpp"
#include <string.h>
#include <fstream>
//#include <bitset>

VBYTE* loadProtectedCode(int &mcsize, std::string fileName)
{
    int codeSize;
    VBYTE *mc;
    std::ifstream fileBinToRead;
    
    fileBinToRead.open(fileName, std::ios::binary);

    if(fileBinToRead.is_open())
    {
        fileBinToRead.seekg(0, fileBinToRead.end);
        codeSize = fileBinToRead.tellg();
        fileBinToRead.seekg(0, fileBinToRead.beg);
        
        if(codeSize > 51202)
        {
            fileBinToRead.close();
            throw 100011;
        }

        VWORD highVBYTE = fileBinToRead.get();
        VWORD lowVBYTE = fileBinToRead.get();

        // std::cout << std::bitset<8>(highVBYTE) << std::endl;
        // std::cout << std::bitset<8>(lowVBYTE) << std::endl;
        // std::cout << std::hex << highVBYTE << std::endl;
        // std::cout << std::hex << lowVBYTE << std::endl;

        VDWORD magicNumber = (highVBYTE << 8) | lowVBYTE;

        if(magicNumber != MAGIC_NUMBER)
        {
            fileBinToRead.close();
            throw 100012;
        }

        fileBinToRead.seekg(0, fileBinToRead.beg);

        mc = new VBYTE[codeSize];
        char VBYTE;
        int counter = 0;

        //std::cout << "[DEBUG] *************" << std::endl;
        while(fileBinToRead.get(VBYTE))
        {
            mc[counter++] = VBYTE;
            //std::cout << "\t<READ> : " << static_cast<uint16_t>(mc[counter - 1]) << std::endl;
        }
        //std::cout << "[DEBUG] *************" << std::endl;
        fileBinToRead.close();
    }
    else
    {
        throw 100010;
    }

    mcsize = codeSize;
    return mc;
}