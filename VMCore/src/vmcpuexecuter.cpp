#include "../include/vmcpu.hpp"

int VMCPU::executer(VBYTE opcode)
{
    int valToReturn = 0;

    VBYTE bTmp_0, bTmp_1, bTmp_2;
    VWORD wTmp_0, wTmp_1;
    VDWORD dTmp_0, dTmp_1, dTmp_2;

    switch(opcode)
    {
        /* NOP */
        case 0x56:
        case 0x6d:
        case NOP:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] NOP" << std::endl;
            #endif
            opcode+=20;
            break;
        /* EE - end of code */
        case EE:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] EE" << std::endl;
            #endif
            valToReturn = 1;
            break;
        /*  ********************************
                        MOV
            ******************************** 
        */
        /*
            MOV - move from register to register
            01 02 05 => MOV R2, R5
            01 00 00 => MOV R0, R0
        */
        case MOV:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOV" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            bTmp_1 = AS->codeData[REGS->PC++];
            #ifdef V_DEBUG
                std::cout << std::hex << REGS->R[bTmp_0] << std::endl;
                std::cout << std::hex << REGS->R[bTmp_1] << std::endl;
                // std::cout << std::hex << bTmp_0 << "\n";
                // std::cout << std::hex << bTmp_1 << "\n";
                // std::cout << std::bitset<8>(bTmp_0) << std::endl;
                // std::cout << std::bitset<8>(bTmp_1) << std::endl;
            #endif
            if((bTmp_0 >= 0 && bTmp_0 <= 7) && (bTmp_1 >= 0 && bTmp_1 <= 7))
            {
                REGS->R[bTmp_0] = REGS->R[bTmp_1];
            }
            else goto EXCEPTION;
            break;
        /* 
            MOVMB - move and extend byte from memory to register 
            02 03 04 01 => MOVMB R3, 0104
        */
        case MOVMB:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVMB" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            //if(wTmp_0 >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC += 2;
            REGS->R[bTmp_0] = 0;
            if(areFramesNeeded && (wTmp_0 >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(wTmp_0, 1);
                if(isError) goto EXCEPTION;
                *(VBYTE*) &REGS->R[bTmp_0] = bytes[0];
            }
            else *(VBYTE*) &REGS->R[bTmp_0] = AS->codeData[wTmp_0];
            break;  
        /* 
            MOVMW - move and extend word from memory to register 
            03 03 04 01 => MOVMW R3, 0104
        */
        case MOVMW:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVMW" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            //if(wTmp_0 >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC += 2;
            if(areFramesNeeded && (wTmp_0 >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(wTmp_0, 2);
                if(isError) goto EXCEPTION;
                VBYTE hb = bytes[0];
                VBYTE lb = bytes[1];
                VWORD w = ((VWORD) hb << 8) | lb;
                *(VWORD*) &REGS->R[bTmp_0] = w;
            }
            else *(VWORD*) &REGS->R[bTmp_0] = *(VWORD*) &AS->codeData[wTmp_0];
            break;  
        /* 
            MOVB - move and extend byte to register 
            04 02 43 => MOVB R2, 43
        */
        case MOVB:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVB" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            REGS->R[bTmp_0] = 0;
            *(VBYTE *) &REGS->R[bTmp_0] = AS->codeData[REGS->PC++];
            break; 
        /* 
            MOVW - move and extend word to register 
            05 01 15 28 => MOVW R1, 2815
        */
        case MOVW:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVW" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            *(VWORD*) &REGS->R[bTmp_0] = *(VWORD *) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            break; 
        /* 
            MOVBM - move byte from register to memory location 
            07 43 13 04 => MOVBM 1343, R4
        */
        case MOVBM:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVBM" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            //if(wTmp_0 >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC += 2;
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            if(areFramesNeeded && (wTmp_0 >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> byteToWrite;
                byteToWrite.push_back(*(VBYTE*) &REGS->R[bTmp_0]);
                writeByteIntoFrame(wTmp_0, 1, byteToWrite);
                if(isError) goto EXCEPTION;
            }
            else AS->codeData[wTmp_0] = *(VBYTE*) &REGS->R[bTmp_0];
            break;  
        /* 
            MOVWM - move word from register to memory location 
            07 43 13 04 => MOVWM 1343,R4
        */
        case MOVWM:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVWM" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            //if(wTmp_0 >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC += 2;
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            if(areFramesNeeded && (wTmp_0 >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> byteToWrite;
                VWORD w = *(VWORD*) &REGS->R[bTmp_0];
                byteToWrite.push_back(w >> 8);
                byteToWrite.push_back(w & 0xff);
                writeByteIntoFrame(wTmp_0, 2, byteToWrite);
                if(isError) goto EXCEPTION;
            }
            else *(VWORD*) &AS->codeData[wTmp_0] = REGS->R[bTmp_0];
            break;
        /* 
            MOVMRB - move and extend byte from memory to register
                    get addr from register
            08 02 01 => MOVMRB R2, R1
        */
        case MOVMRB:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVMRB" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            //if(REGS->R[bTmp_1] >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->R[bTmp_0] = 0;
            if(areFramesNeeded && (REGS->R[bTmp_1] >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(REGS->R[bTmp_1], 1);
                if(isError) goto EXCEPTION;
                *(VBYTE*) &REGS->R[bTmp_0] = bytes[0];
            }
            else *(VBYTE*) &REGS->R[bTmp_0] = AS->codeData[REGS->R[bTmp_1]];
            break;
        /* 
            MOVMRW - move and extend word from memory to register
                    get addr from register
            09 02 01 => MOVMRW R2, R1
        */
        case MOVMRW:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVMRW" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            //if(REGS->R[bTmp_1] >= sizeof(AS->codeData)) goto EXCEPTION;
            if(areFramesNeeded && (REGS->R[bTmp_1] >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(REGS->R[bTmp_1], 2);
                if(isError) goto EXCEPTION;
                VBYTE hb = bytes[0];
                VBYTE lb = bytes[1];
                VWORD w = ((VWORD) hb << 8) | lb;
                *(VWORD*) &REGS->R[bTmp_0] = w;
            }
            else *(VWORD*) &REGS->R[bTmp_0] = *(VWORD*) &AS->codeData[REGS->R[bTmp_1]];
            break;
        /* 
            MOVMD - move double word from memory to register 
            0A 03 04 01 => MOVMW R3, 0104
        */
        case MOVMD:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVMD" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            dTmp_0 = *(VDWORD*) &AS->codeData[REGS->PC];
            //if(dTmp_0 >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC += 2;
            if(areFramesNeeded && (dTmp_0 >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(dTmp_0, 4);
                if(isError) goto EXCEPTION;
                VBYTE hb3 = bytes[0];
                VBYTE hb2 = bytes[1];
                VBYTE hb1 = bytes[2];
                VBYTE lb = bytes[3];
                VDWORD dw = ((VDWORD) hb3 << 24) | ((VDWORD) hb2 << 16) | ((VDWORD) hb1 << 8) | lb;
                REGS->R[bTmp_0] = dw;
            }
            else REGS->R[bTmp_0] = *(VDWORD*) &AS->codeData[dTmp_0];
            break;  
        /* 
            MOVD - move value to register 
            0B 01 00 00 15 28 => MOVW R1, 2815
        */
        case MOVD:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVD" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            REGS->R[bTmp_0] = *(VDWORD *) &AS->codeData[REGS->PC];
            REGS->PC += 4;
            break;  
        /* 
            MOVDM - move double word from register to memory location 
            0C 43 13 04 => MOVWM 1343, R4
        */
        case MOVDM:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVDM" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            //if(wTmp_0 >= sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC += 2;
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            if(areFramesNeeded && (wTmp_0 >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> byteToWrite;
                VDWORD dw = REGS->R[bTmp_0];
                byteToWrite.push_back(dw >> 24);
                byteToWrite.push_back(dw >> 16);
                byteToWrite.push_back(dw >> 8);
                byteToWrite.push_back(dw);
                writeByteIntoFrame(wTmp_0, 2, byteToWrite);
                if(isError) goto EXCEPTION;
            }
            else *(VDWORD*) &AS->codeData[wTmp_0] = REGS->R[bTmp_0];
            break;
        /* 
            MOVMRD - move double word from memory to register
                    get addr from register
            0D 02 01 => MOVMRW R2, R1
        */
        case MOVMRD:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] MOVMRD" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            //if(REGS->R[bTmp_1] >= sizeof(AS->codeData)) goto EXCEPTION;
            if(areFramesNeeded && (REGS->R[bTmp_1] >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(REGS->R[bTmp_1], 4);
                if(isError) goto EXCEPTION;
                VBYTE hb3 = bytes[0];
                VBYTE hb2 = bytes[1];
                VBYTE hb1 = bytes[2];
                VBYTE lb = bytes[3];
                VDWORD dw = ((VDWORD) hb3 << 24) | ((VDWORD) hb2 << 16) | ((VDWORD) hb1 << 8) | lb;
                REGS->R[bTmp_0] = dw;
            }
            else REGS->R[bTmp_0] = *(VDWORD*) &AS->codeData[REGS->R[bTmp_1]];
            break;
        /*  ********************************
                        JUMP
            ********************************
        */
        /*
            JMP - unconditional jump
            20 15 00 => JMP 0015
        */
        case JMP:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JMP" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            REGS->PC = wTmp_0;
            break; 
        /*
            JZ - jump if equal
            21 15 00 => JZ 0015
        */
        case JZ:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JZ" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            if(REGS->ZF) REGS->PC = wTmp_0;
            break;
        /*
            JNZ - jump if not equal
            22 15 00 => JNZ 0015
        */
        case JNZ:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JNZ" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            if(!REGS->ZF) REGS->PC = wTmp_0;
            break;
        /*
            JAE - jump if above or equal
            23 15 00 => JAE 0015
        */
        case JAE:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JAE" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            if(REGS->ZF || !REGS->CF) REGS->PC = wTmp_0;
            break;
        /*
            JBE - jump if below or equal
            24 15 00 => JBE 0015
        */
        case JBE:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JBE" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            if(REGS->ZF || REGS->CF) REGS->PC = wTmp_0;
            break;
        /*
            JB - jump if below
            25 15 00 => JB 0015
        */
        case JB:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JB" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            if(!REGS->ZF && REGS->CF) REGS->PC = wTmp_0;
            break;
        /*
            JA - jump if above
            26 15 00 => JA 0015
        */
        case JA:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] JA" << std::endl;
            #endif
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            // if(wTmp_0 > sizeof(AS->codeData)) goto EXCEPTION;
            if(!REGS->ZF && !REGS->CF) REGS->PC = wTmp_0;
            break;
        /*  ********************************
                        ARITHMETIC
            ********************************
        */
        /*
            ADVR - Add word value to register
            30 02 10 00 => ADVR R2, 10
        */
        case ADVR:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] ADVR" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            wTmp_1 = REGS->R[bTmp_0] + wTmp_0;          
            if(wTmp_1 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(wTmp_1 < REGS->R[bTmp_0]) REGS->CF = 1;
            else REGS->CF = 0;
            *(VWORD *) &REGS->R[bTmp_0] = wTmp_1;
            break;
        /*
            ADRR - Add two registers
                    and save result in first
            31 02 01 => ADRR R2, R1
        */
        case ADRR:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] ADRR" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            dTmp_0 = REGS->R[bTmp_0];
            dTmp_1 = REGS->R[bTmp_1];
            dTmp_2 = dTmp_0 + dTmp_1;
            REGS->R[bTmp_0] = dTmp_2;
            if(dTmp_2 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(dTmp_2 < dTmp_0) REGS->CF = 1;
            else REGS->CF = 0;
            break;
        /*
            ADRRL - Add two registers (low byte)
                    and save result in first
            32 02 01 => ADRR R2, R1
        */
        case ADRRL:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] ADRRL" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            bTmp_2 = *(VBYTE *) &REGS->R[bTmp_0];
            bTmp_1 = *(VBYTE *) &REGS->R[bTmp_1];
            bTmp_1 += bTmp_2;
            *(VBYTE *) &REGS->R[bTmp_0] = bTmp_1;
            if(bTmp_1 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(bTmp_1 < bTmp_2) REGS->CF = 1;
            else REGS->CF = 0;
            break;
        /*
            SUBVR - Substract word value from register
            33 02 10 00 => SUBVR R2, 10
        */
        case SUBVR:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SUBVR" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            wTmp_1 = REGS->R[bTmp_0] - wTmp_0;          
            if(wTmp_1 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(wTmp_1 > REGS->R[bTmp_0]) REGS->CF = 1;
            else REGS->CF = 0;
            *(VWORD *) &REGS->R[bTmp_0] = wTmp_1;
            break;
        /*
            SUBRR - Substract two registers
                    and save result in first
            34 02 01 => SUBRR R2, R1
        */
        case SUBRR:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SUBRR" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            dTmp_0 = REGS->R[bTmp_0];
            dTmp_1 = REGS->R[bTmp_1];
            dTmp_2 = dTmp_0 - dTmp_1;
            REGS->R[bTmp_0] = dTmp_2;
            if(dTmp_2 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(dTmp_2 > dTmp_0) REGS->CF = 1;
            else REGS->CF = 0;
            break;
        /*
            SUBRRL - Substract two registers (low byte)
                    and save result in first
            35 02 01 => ADRR R2, R1
        */
        case SUBRRL:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SUBRRL" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            bTmp_2 = *(VBYTE *) &REGS->R[bTmp_0];
            bTmp_1 = *(VBYTE *) &REGS->R[bTmp_1];
            bTmp_1 -= bTmp_2;
            *(VBYTE *) &REGS->R[bTmp_0] = bTmp_1;
            if(bTmp_1 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(bTmp_1 > bTmp_2) REGS->CF = 1;
            else REGS->CF = 0;
            break;
        /*
            XOR - Xor two registers
                and save result in first
            36 02 01 => XOR R2, R1
        */
        case XOR:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] XOR" << std::endl;
            #endif 
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            dTmp_0 = REGS->R[bTmp_0];
            dTmp_1 = REGS->R[bTmp_1];
            dTmp_2 = dTmp_0 ^ dTmp_1;
            if(dTmp_2 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            REGS->R[bTmp_0] = dTmp_2;
            REGS->CF = 0;
            break;
        /*
            XORL - Xor two registers (lower bytes)
                and save result in first
            37 02 01 => XOR R2, R1
        */
        case XORL:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] XORL" << std::endl;
            #endif 
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            bTmp_2 = REGS->R[bTmp_0];
            bTmp_1 = REGS->R[bTmp_1];
            bTmp_2 ^= bTmp_1;
            if(bTmp_2 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            *(VBYTE *) &REGS->R[bTmp_0] = bTmp_2;
            REGS->CF = 0;
            break;
        /*
            NOT - Bitwise not on value in a register
                and save result in this register
            38 02 => NOT R2
        */
        case NOT:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] NOT" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            REGS->R[bTmp_0] = ~ REGS->R[bTmp_0];
            break;
        /*
            NOTB - Bitwise not on value in a register (lower bytes)
                and save result in this register
            39 02 => NOT R2
        */
        case NOTB:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] NOTB" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            *(VBYTE *) &REGS->R[bTmp_0] = ~ (*(VBYTE *) &REGS->R[bTmp_0]);
            break;
        /*
            ADVRD - Add double word value to register
            3A 02 10 00 00 00 => ADVR R2, 10
        */
        case ADVRD:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] ADVRD" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            dTmp_0 = *(VDWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 4;
            dTmp_1 = REGS->R[bTmp_0] + dTmp_0;          
            if(dTmp_1 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(dTmp_1 < REGS->R[bTmp_0]) REGS->CF = 1;
            else REGS->CF = 0;
            REGS->R[bTmp_0] = dTmp_1;
            break;
            /*
            SUBVRD - Substract double word value from register
            3B 02 10 00 00 00 => SUBVR R2, 10
        */
        case SUBVRD:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SUBVRD" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            dTmp_0 = *(VDWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 4;
            dTmp_1 = REGS->R[bTmp_0] - dTmp_0;          
            if(dTmp_1 == 0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(dTmp_1 > REGS->R[bTmp_0]) REGS->CF = 1;
            else REGS->CF = 0;
            *(VDWORD *) &REGS->R[bTmp_0] = dTmp_1;
            break;
        /*
            SHR - Shift the bits of the operand destination to the right,
                  by the number of bits specified in the count operand
            3C 02 05 => SHR R2, 5
        */
        case SHR:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SHR" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            REGS->R[bTmp_0] = REGS->R[bTmp_0] >> bTmp_1;
            break;
        /*
            SHL -Shift the bits of the operand destination to the left,
                  by the number of bits specified in the count operand
            3D 02 05 => SHL R2, 5
        */
        case SHL:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SHL" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            REGS->R[bTmp_0] = REGS->R[bTmp_0] << bTmp_1;
            break;
        /*  ********************************
                        COMPARE
            ********************************
        */
        /*
            CMP - compare two registers
            50 02 01 => CMP R2, R1
        */
        case CMP:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] CMP" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            dTmp_0 = REGS->R[bTmp_0];
            dTmp_1 = REGS->R[bTmp_1];
            #ifdef V_DEBUG
                std::cout << dTmp_0 << std::endl;
                std::cout << dTmp_1 << std::endl;
            #endif
            if(dTmp_1 == dTmp_0) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(dTmp_1 > dTmp_0) REGS->CF = 1;
            else REGS->CF = 0;
            break;
        /*
            CMPL - compare two registers (lower byte)
            51 02 01 => CMP R2, R1
        */
        case CMPL:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] CMPL" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            bTmp_1 = AS->codeData[REGS->PC++];
            if(bTmp_1 > 8) goto EXCEPTION;
            bTmp_0 = *(VBYTE*) &REGS->R[bTmp_0];
            bTmp_1 = *(VBYTE*) &REGS->R[bTmp_1];
            if(bTmp_0 == bTmp_1) REGS->ZF = 1;
            else REGS->ZF = 0;
            if(bTmp_0 < bTmp_1) REGS->CF = 1;
            else REGS->CF = 0;
            break;
        /*  ********************************
                        VMSYSBUS
            ********************************
        */
        /*
            VMSYSBUS FUNC_CODE
            60 01 00 => SYSBUS createDirectory
        */
        case VMSYSBUS:
            wTmp_0 = *(VWORD*) &AS->codeData[REGS->PC];
            REGS->PC += 2;
            REGS->R[6] = 0;
            REGS->R[7] = 0;
            #ifdef V_DEBUG
                std::cout << "[DEBUG] VMSYSBUS" << std::endl;
                std::cout << "[DEBUG] CALL " << wTmp_0 << std::endl;
            #endif
            switch(wTmp_0)
            {
                case SYSBUS_CREATE_DIR:
                    {
                        wTmp_1 = AS->stack[REGS->SP]; // second arg
                        REGS->SP += 1;
                        wTmp_0 = AS->stack[REGS->SP]; // first arg
                        REGS->SP += 1;
                        std::string arg1 = "";
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->createDirectory(arg1, wTmp_1);
                    }
                    break;
                case SYSBUS_DELETE_DIR:
                    {
                        wTmp_0 = AS->stack[REGS->SP];
                        REGS->SP += 1;
                        std::string arg1 = "";
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->deleteDirectory(arg1);
                    }
                    break;
                case SYSBUS_MOVE_DIR:
                    {
                        wTmp_1 = AS->stack[REGS->SP]; // second arg
                        REGS->SP += 1;
                        wTmp_0 = AS->stack[REGS->SP]; // first arg
                        REGS->SP += 1;
                        std::string arg1 = "";
                        std::string arg2 = "";
                        getDataFromCodeData(arg2, wTmp_1);
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->moveDirectory(arg1, arg2);
                    }
                    break;
                case SYSBUS_COPY_DIR:
                    {
                        wTmp_1 = AS->stack[REGS->SP]; // second arg
                        REGS->SP += 1;
                        wTmp_0 = AS->stack[REGS->SP]; // first arg
                        REGS->SP += 1;
                        std::string arg1 = "";
                        std::string arg2 = "";
                        getDataFromCodeData(arg2, wTmp_1);
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->copyDirectory(arg1, arg2);
                    }
                    break;
                case SYSBUS_CREATE_FILE:
                    {
                        wTmp_1 = AS->stack[REGS->SP];
                        REGS->SP += 1;
                        wTmp_0 = AS->stack[REGS->SP];
                        REGS->SP += 1;
                        std::string arg2 = "";
                        int counter = wTmp_1;
                        int dataLength = 0;
                        VBYTE b;
                        std::vector<VBYTE> dataVbyte;
                        int frameNumberToRestore = currentFrameNumber;
                        while(true)
                        {
                            if(areFramesNeeded && (counter >= frameMap[currentFrameNumber])) counter = loadFrame(counter);
                            if(isError) goto EXCEPTION;
                            b = AS->codeData[counter++];
                            if((b == 0x3) && (AS->codeData[counter] == 0xD)) break;
                            ++dataLength;
                            dataVbyte.push_back(b);
                            std::cout << std::hex << b << std::endl;
                        }
                        currentFrameNumber = frameNumberToRestore;
                        restoreFrame();
                        if(isError) goto EXCEPTION;
                        VBYTE *dataToWrite = &dataVbyte[0];
                        std::string arg1 = "";
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->createFile(arg1, dataToWrite, dataLength);
                    }
                    break;
                case SYSBUS_DELETE_FILE:
                    {
                        wTmp_0 = AS->stack[REGS->SP];
                        REGS->SP += 1;
                        std::string arg1 = "";
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->deleteFile(arg1);
                    }
                    break;
                case SYSBUS_MOVE_FILE:
                    {
                        wTmp_1 = AS->stack[REGS->SP]; // second arg
                        REGS->SP += 1;
                        wTmp_0 = AS->stack[REGS->SP]; // first arg
                        REGS->SP += 1;
                        std::string arg1 = "";
                        std::string arg2 = "";
                        getDataFromCodeData(arg2, wTmp_1);
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->moveFile(arg1, arg2);
                    }
                    break;
                case SYSBUS_COPY_FILE:
                    {
                        wTmp_1 = AS->stack[REGS->SP]; // second arg
                        REGS->SP += 1;
                        wTmp_0 = AS->stack[REGS->SP]; // first arg
                        REGS->SP += 1;
                        std::string arg1 = "";
                        std::string arg2 = "";
                        getDataFromCodeData(arg2, wTmp_1);
                        getDataFromCodeData(arg1, wTmp_0);
                        REGS->R[6] = sysBus->copyFile(arg1, arg2);
                    }
                    break;
                default:
                    REGS->R[7] = 1;
            }
            break;
        /*  ********************************
                        STACK
            ********************************
        */
        /*
            PUSH REGISTER
            90 03 => PUSH R3
        */
        case PUSH:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] PUSH" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            REGS->SP -= 1;
            if(REGS->SP == 0xFFFFFFFF) {
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::OVERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK OVERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            AS->stack[REGS->SP] = REGS->R[bTmp_0];
            #ifdef V_DEBUG
                std::cout <<"val: " << std::hex << AS->stack[REGS->SP] << std::endl;
            #endif
            break;
            /*
            POP TO A REGISTER
            91 03 => POP R3
        */
        case POP:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] POP" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 > 8) goto EXCEPTION;
            if((&AS->stack[REGS->SP]) == (&AS->stack[sizeof(AS->stack)/sizeof(VDWORD)])){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            REGS->R[bTmp_0] = AS->stack[REGS->SP];
            REGS->SP += 1;
            break;
        /*
            Clear the stack
            92 => CLST
        */
        case CLST:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] CLST" << std::endl;
            #endif
            memset(AS->stack, 0, STACK_SIZE*sizeof(*(AS->stack)));
            REGS->SP = 0;
            break;
        /*
            Set the stack pointer
            93 01 00 00 00 => SETSP 1
        */
        case SETSP:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] SETSP" << std::endl;
            #endif
            REGS->SP = 0;
            REGS->SP = *(VDWORD *) &AS->codeData[REGS->PC];
            if(REGS->SP > STACK_SIZE) goto EXCEPTION;
            REGS->PC += 4;
            break;
        /*  ********************************
                        IN/OUT
            ********************************
        */
        /*
            POC - Print char without new line
                the value must be at the top of
                the stack
            A0 => POC
        */
        case POC:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] POC" << std::endl;
            #endif
            if(&AS->stack[REGS->SP] == &AS->stack[sizeof(AS->stack)/sizeof(VDWORD)]){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            if(areFramesNeeded && (AS->stack[REGS->SP] >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(AS->stack[REGS->SP++], 1);
                bTmp_0 = bytes[0];
            }
            else bTmp_0 = *(VBYTE*) &AS->codeData[AS->stack[REGS->SP++]];
            if(isError) goto EXCEPTION;
            vmPrint(bTmp_0);
            break;
        /*
            POCN - Print char with new line
                the value must be at the top of
                the stack
            A1 => POCN
        */
        case POCN:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] POCN" << std::endl;
            #endif
            if(&AS->stack[REGS->SP] == &AS->stack[sizeof(AS->stack)/sizeof(VDWORD)]){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            if(areFramesNeeded && (AS->stack[REGS->SP] >= frameMap[currentFrameNumber]))
            {
                std::vector<VBYTE> bytes = getByteFromFrame(AS->stack[REGS->SP++], 1);
                bTmp_0 = bytes[0];
            }
            else bTmp_0 = *(VBYTE*) &AS->codeData[AS->stack[REGS->SP++]];
            if(isError) goto EXCEPTION;
            vmPrintN(bTmp_0);
            break;
        /*
            TIB - Take input and move to the data buffer,
                  the length of the string is stored in R[7]
            A2 => TIB
        */
        case TIB:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] TIB" << std::endl;
            #endif
            {
                memset(AS->dataBuffer, 0, INPUT_BUFFER_SIZE*sizeof(*(AS->dataBuffer)));
                std::string inData = "";
                std::getline(std::cin, inData);
                VBYTE endOfText = 0x3;
                if(inData.length() > (INPUT_BUFFER_SIZE - 1)) 
                {
                    inData = inData.substr(0, (INPUT_BUFFER_SIZE - 1));
                }
                int counter = 0;
                for(char const &c: inData)
                {
                    AS->dataBuffer[counter++] = c;
                }
                AS->dataBuffer[counter++] = endOfText;
                REGS->R[7] = 0;
                *(VWORD *) &REGS->R[7] = counter;
            }
            break;
        /*
            GIC - Get a specific char from input, that is stored in the data buffer,
                  the value will be stored in R[7],
                  pass the position of char via a some register
            A3 02 => GIC R2
        */
        case GIC:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] GIC" << std::endl;
            #endif
            bTmp_0 = AS->codeData[REGS->PC++];
            if(bTmp_0 >= 0 && bTmp_0 <= 7)
            {
                if(REGS->R[bTmp_0] >= INPUT_BUFFER_SIZE)
                {
                    goto EXCEPTION;
                }
                REGS->R[7] = 0;
                *(VBYTE *) &REGS->R[7] = AS->dataBuffer[REGS->R[bTmp_0]];
            }
            else goto EXCEPTION;
            break;
        /*
            PIC - Print char from input without new line
                the value must be at the top of
                the stack
            A4 => PIC
        */
        case PIC:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] PIC" << std::endl;
            #endif
            if(&AS->stack[REGS->SP] == &AS->stack[sizeof(AS->stack)/sizeof(VDWORD)]){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            bTmp_0 = AS->stack[REGS->SP++];
            vmPrint(bTmp_0);
            break;
        /*
            PICN - Print char from input with new line
                the value must be at the top of
                the stack
            A5 => POCN
        */
        case PICN:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] PICN" << std::endl;
            #endif
            if(&AS->stack[REGS->SP] == &AS->stack[sizeof(AS->stack)/sizeof(VDWORD)]){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            bTmp_0 = AS->stack[REGS->SP++];
            vmPrintN(bTmp_0);
            break;
        /*
            PXV - Print a value in hex;
                the value must be at the top of the stack
            A6 => PXV
        */
        case PXV:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] PXV" << std::endl;
            #endif
            if(&AS->stack[REGS->SP] == &AS->stack[sizeof(AS->stack)/sizeof(VDWORD)]){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            dTmp_0 = AS->stack[REGS->SP++];
            vmPrintHX(dTmp_0);
            break;
        /*
            PXVN - Print a value in hex with a new line;
                the value must be at the top of the stack
            A7 => PXV
        */
        case PXVN:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] PXVN" << std::endl;
                // std::cout << std::bitset<32>(AS->stack[REGS->SP]) << std::endl;
            #endif
            if(&AS->stack[REGS->SP] == &AS->stack[sizeof(AS->stack)/sizeof(VDWORD)]){
                #ifdef _VM_CPU_TEST_
                    vcpuFlag = VCpuFlag::UNDERFLOW;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] STACK UNDERFLOW!" << std::endl;
                #endif
                goto EXCEPTION;
            }
            dTmp_0 = AS->stack[REGS->SP++];
            vmPrintHXN(dTmp_0);
            break;
        /*  
            ********************************
                        DEFAULT
            ********************************
        */
        default:
            #ifdef V_DEBUG
                std::cout << "[DEBUG] DEFAULT" << std::endl;
            #endif
            EXCEPTION:
                #ifdef _VM_CPU_TEST_
                    if(vcpuFlag == VCpuFlag::OK) vcpuFlag = VCpuFlag::ERROR;
                #endif
                #ifndef _VM_CPU_TEST_
                    std::cout << "[ERROR] vCPU CRASH!" << std::endl;
                #endif
                valToReturn = 1;
    }

    return valToReturn;
}