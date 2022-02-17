#include "../include/main.hpp"
#include "../include/vmcpu.hpp"
#include <string.h>
#include <fstream>
#include <vector>

// #include <bitset>

#define CODE_DATA_SIZE 51200

int VMCPU::checkOpcodeSize(VBYTE opcode, bool isOpcode) 
{
    if(!isOpcode) return 0;
    else
    {
        if(dOpcodesFunction.find(opcode) == dOpcodesFunction.end()) return 0;
        else return dOpcodesFunction[opcode].first;
    }
}

VBYTE* VMCPU::loadProtectedCode(int &mcsize, std::string fileName)
{
    VBYTE *mc;
    std::ifstream fileBinToRead;
    std::ofstream fileBinToWrite;
    int framesCount;
    
    fileBinToRead.open(fileName, std::ios::binary);

    if(fileBinToRead.is_open())
    {
        fileBinToRead.seekg(0, fileBinToRead.end);
        mcsize = fileBinToRead.tellg();
        fileBinToRead.seekg(0, fileBinToRead.beg);

        VWORD highVBYTE = fileBinToRead.get();
        VWORD lowVBYTE = fileBinToRead.get();
        // std::cout << std::bitset<8>(highVBYTE) << std::endl;
        // std::cout << std::hex << highVBYTE << std::endl;
        VDWORD magicNumber = (highVBYTE << 8) | lowVBYTE;

        if(magicNumber != MAGIC_NUMBER)
        {
            fileBinToRead.close();
            throw 100012;
        }
        
        if(mcsize > CODE_DATA_SIZE)
        {
            areFramesNeeded = true;
            framesCount = int((mcsize + CODE_DATA_SIZE - 1) / CODE_DATA_SIZE);
            for(int i = 0; i < framesCount; i++) frameMap[i] = 0;
        }

        fileBinToRead.seekg(0, fileBinToRead.beg);

        mc = new VBYTE[mcsize];
        char vb;
        int counter = 0;
        framesCount = 0;
        std::string tempFileToOpen;
        std::vector<VBYTE> readData;
        int argCount = 0;
        bool isOpcode;

        if(areFramesNeeded) {
            tempFileToOpen = ".cached." + std::to_string(framesCount++) + ".frame";
            fileBinToWrite.open(tempFileToOpen.c_str(), std::fstream::out | std::ios::binary);
        }
        while(fileBinToRead.get(vb))
        {   
            if(areFramesNeeded) {
                ++counter;
                if(argCount == 0) 
                {
                    isOpcode = true;
                    argCount = checkOpcodeSize(vb, isOpcode);
                }
                else if(vb == 0xEE)
                {
                    argCount = -1;
                    isOpcode = false;
                }
                else
                {
                    --argCount;
                    isOpcode = false;
                }
                if((counter + checkOpcodeSize(vb, isOpcode)) > CODE_DATA_SIZE) {
                    frameMap[framesCount - 1] = counter - 1;
                    VBYTE *dataToWrite = &readData[0];
                    fileBinToWrite.write((char*)dataToWrite, counter-1);
                    fileBinToWrite.close();

                    std::string tempFileToOpen = ".cached." + std::to_string(framesCount++) + ".frame";
                    fileBinToWrite.open(tempFileToOpen.c_str(), std::fstream::out | std::ios::binary);
                    
                    readData.clear();
                    readData.push_back(vb);
                    counter = 1;
                }
                else 
                {
                    if(framesCount == 1) mc[counter - 1] = vb;
                    readData.push_back(vb);
                }
            }
            else {
                mc[counter++] = vb;
                //std::cout << "\t<READ> : " << static_cast<uint16_t>(mc[counter - 1]) << std::endl;
            }
        }
        if(areFramesNeeded)
        {
            mcsize = frameMap[0];
            VBYTE *dataToWrite = &readData[0];
            frameMap[framesCount - 1] = counter;
            fileBinToWrite.write((char*)dataToWrite, counter);
            fileBinToWrite.close();
        }
        fileBinToRead.close();
    }
    else
    {
        throw 100010;
    }
    return mc;
}