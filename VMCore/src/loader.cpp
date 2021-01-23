#include "../include/main.hpp"
#include "../include/opcodes.hpp"
#include <string.h>
#include <fstream>
#include <vector>

// #include <bitset>

#define CODE_DATA_SIZE 51200

VBYTE* loadProtectedCode(int &mcsize, std::string fileName, bool &areFramesNeeded, std::map<int, int> &frameMap)
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

int checkOpcodeSize(VBYTE opcode, bool isOpcode) 
{
    if(!isOpcode) return 0;
    switch(opcode) 
    {
        case 0x56:
        case 0x6d:
        case NOP:
            return 0;
        case EE:
            return 0;
        case MOV:
            return 2;
        case MOVMB:
            return 3;
        case MOVMW:
            return 3;  
        case MOVB:
            return 2;
        case MOVW:
           return 3;
        case MOVBM:
           return 3; 
        case MOVWM:
            return 3;
        case MOVMRB:
            return 2;
        case MOVMRW:
            return 2;
        case MOVMD:
            return 3;
        case MOVD:
            return 5;
        case MOVDM:
           return 3;
        case MOVMRD:
           return 2;
        case JMP:
           return 2;
        case JZ:
            return 2;
        case JNZ:
            return 2;
        case JAE:
           return 2;
        case JBE:
            return 2;
        case JB:
           return 2;
        case JA:
            return 2;
        case ADVR:
           return 3;
        case ADRR:
            return 2;
        case ADRRL:
            return 2;
        case SUBVR:
           return 3;
        case SUBRR:
            return 2;
        case SUBRRL:
           return 2;
        case XOR:
            return 2;
        case XORL:
           return 2;
        case NOT:
            return 1;
        case NOTB:
            return 1;
        case ADVRD:
           return 5;
        case SUBVRD:
           return 5;
        case SHR:
           return 2;
        case SHL:
            return 2;
        case CMP:
            return 2;
        case CMPL:
            return 2;
        case VMSYSBUS:
            return 1;
        case PUSH:
           return 1;
        case POP:
            return 1;
        case CLST:
           return 0;
        case SETSP:
            return 4;
        case POC:
           return 0;
        case POCN:
           return 0;
        case TIB:
           return 0;
        case GIC:
           return 1;
        case PIC:
            return 0;
        case PICN:
            return 0;
        case PXV:
           return 0;
        case PXVN:
            return 0;
        default:
            return 0;
    }
}