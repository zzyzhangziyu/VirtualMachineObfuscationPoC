#include "../include/main.hpp"
#include "./opcodes.hpp"
#include <string.h>
#include <fstream>
//#include <bitset>

#define CODE_DATA_SIZE_WITH_MAGIC 51202

VBYTE* loadProtectedCode(int &mcsize, std::string fileName, bool &areFramesNeeded, int &framesCount, int *framesSizeArray)
{
    VBYTE *mc;
    std::ifstream fileBinToRead;
    std::ofstream fileBinToWrite;
    
    fileBinToRead.open(fileName, std::ios::binary);

    if(fileBinToRead.is_open())
    {
        fileBinToRead.seekg(0, fileBinToRead.end);
        mcsize = fileBinToRead.tellg();
        fileBinToRead.seekg(0, fileBinToRead.beg);
        
        if(mcsize > CODE_DATA_SIZE_WITH_MAGIC)
        {
            areFramesNeeded = true;
            framesCount = int((mcsize + CODE_DATA_SIZE_WITH_MAGIC - 1) / CODE_DATA_SIZE_WITH_MAGIC)
            framesSizeArray = new int[framesCount];
        }

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

        fileBinToRead.seekg(0, fileBinToRead.beg);

        mc = new VBYTE[mcsize];
        char VBYTE;
        int counter = 0;

        fileBinToWrite
        if(areFramesNeeded) {
            std::string tempFileToOpen = ".cached." + (++framesCount) + ".frame"
            fileBinToWrite.open(tempFileToOpen.c_str(), std::ios::binary)
        }
        //std::cout << "[DEBUG] *************" << std::endl;
        while(fileBinToRead.get(VBYTE))
        {
            if(areFramesNeeded) {
                // **************************************************************************
                // TODO: create frames

                tempFileToOpen.put(VBYTE);

                auto opcodeSize = checkOpcodeSize(VBYTE);
                if(counter == CODE_DATA_SIZE_WITH_MAGIC) {
                    fileBinToRead.close();
                    std::string tempFileToOpen = ".cached." + (++framesCount) + ".frame"
                    fileBinToWrite.open(tempFileToOpen.c_str(), std::ios::binary)
                }
                // **************************************************************************
            }
            else {
                mc[counter++] = VBYTE;
                //std::cout << "\t<READ> : " << static_cast<uint16_t>(mc[counter - 1]) << std::endl;
            }
        }
        if(areFramesNeeded) fileBinToWrite.close();
        //std::cout << "[DEBUG] *************" << std::endl;
        fileBinToRead.close();
    }
    else
    {
        throw 100010;
    }
    return mc;
}

int checkOpcodeSize(VBYTE opcode) 
{
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