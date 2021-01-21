#include "main.hpp"

void conn(int cliSocket)
{
    bool connLoop = true;
    MESSAGE_TO_DEBUGGER msgToDebg;
    MESSAGE_FROM_DEBUGGER msgFromDebg;
    char bufferMSGtoDbg[PACKET_TO_DEBUGGER_SIZE];
    char bufferMSGfromDbg[PACKET_FROM_DEBUGGER_SIZE];
    int retValFromFunc;
    int cmdDBG;

    while(connLoop)
    {
        retValFromFunc = recvData(cliSocket, bufferMSGtoDbg, PACKET_TO_DEBUGGER_SIZE);
        if(retValFromFunc == RECIVE_ERROR)
        {
            std::cout << "[ERROR] Failed receive data\n";
            #ifdef  _LINUX_DEV_ENVIRONMENT
                close(cliSocket);
            #else //_WIN32_DEV_ENVIRONMENT
                closesocket(cliSocket);
                WSACleanup();
            #endif
            exit(-1);
        }
        deserializeMSG(&msgToDebg,bufferMSGtoDbg);
SHOWOPTIONS:
        printOptions();
        std::cin >> cmdDBG;
        switch(cmdDBG)
        {
            case 1:
                msgFromDebg.cmdFlag = CMD_RUN;
                serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                break;
            case 2:
                msgFromDebg.cmdFlag = CMD_STEP;
                serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                break;
            case 3:
                msgFromDebg.cmdFlag = CMD_EXIT;
                connLoop = false;
                serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                break;
            case 4:
                {
                    int option;
                    VDWORD val;
                    int regNr;
                    std::cout << "Select a register to modify:\n"
                                << "\t1. PC\n"
                                << "\t2. SP\n"
                                << "\t3. Rx\n";
                    std::cout << "Choice: ";
                    std::cin >> option;
                    switch(option)
                    {
                        case 1:
                            std::cout << "Value (hex e.g. 1B or 1b): ";
                            std::cin >> std::hex >> val;
                            msgFromDebg.cmdFlag = CMD_SET_PC;
                            *(VDWORD*) &msgFromDebg.buffer[0] = val;
                            serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                            retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                            if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                            break;
                        case 2:
                            std::cout << "Value (hex e.g. 1B or 1b): ";
                            std::cin >> std::hex >> val;
                            msgFromDebg.cmdFlag = CMD_SET_SP;
                            *(VDWORD*) &msgFromDebg.buffer[0] = val;
                            serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                            retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                            if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                            break;
                        case 3:
                            std::cout << "register nr: ";
                            std::cin >> regNr;
                            std::cout << "Value (hex e.g. 1B or 1b): ";
                            std::cin >> std::hex >> val;
                            msgFromDebg.cmdFlag = CMD_SET_R;
                            msgFromDebg.buffer[0] = regNr + '0';
                            *(VDWORD*) &msgFromDebg.buffer[1] = val;
                            serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                            retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                            if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                            break;
                        default:
                            std::cout << "Unkonown command!\n";
                            goto SHOWOPTIONS;
                    }
                }
                break;
            case 5:
                {
                    int option;
                    std::cout << "Select a flag to modify:\n"
                                << "\t1. ZF\n"
                                << "\t2. CF\n";
                    std::cout << "Choice: ";
                    std::cin >> option;
                    char val;
                    switch(option)
                    {
                        case 1:
                            {
                                std::cout << "Value: ";
                                std::cin >> val;
                                msgFromDebg.cmdFlag = CMD_SET_ZF;
                                msgFromDebg.buffer[0] = val;
                                serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                                retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                                if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                            }
                            break;
                        case 2:
                            {
                                std::cout << "Value: ";
                                std::cin >> val;
                                msgFromDebg.cmdFlag = CMD_SET_CF;
                                msgFromDebg.buffer[0] = val;
                                serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                                retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                                if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                            }
                            break;
                        default:
                            std::cout << "Unkonown command!\n";
                            goto SHOWOPTIONS;
                    }
                }
                break;
            case 6:
                {
                    int numberDataToPrint = 0;
                    std::cout << "How many data to print: ";
                    std::cin >> numberDataToPrint;
                    if(numberDataToPrint > STACK_SIZE) numberDataToPrint = STACK_SIZE;
                    int sti = STACK_SIZE - 1;
                    while(sti >= (STACK_SIZE - numberDataToPrint))
                    {
                        std::cout << sti << ": " << std::bitset<32>(msgToDebg.stack[sti]) << std::endl;
                        --sti;
                    }
                    std::cout << "\n";
                    goto SHOWOPTIONS;
                }
                break;
            case 7:
                {
                    int numberDataToPrint = 0;
                    std::cout << "How many data to print: ";
                    std::cin >> numberDataToPrint;
                    if(numberDataToPrint > CODE_DATA_SIZE) numberDataToPrint = CODE_DATA_SIZE;
                    for(int i = 0; i < numberDataToPrint; i++)
                    {
                        std::cout << std::bitset<8>(msgToDebg.codeData[i]) << std::endl;
                    }
                    std::cout << "\n";
                    goto SHOWOPTIONS;
                }
                break;
            case 8:
                {
                    int numberDataToPrint = 0;
                    std::cout << "How many data to print: ";
                    std::cin >> numberDataToPrint;
                    if(numberDataToPrint > INPUT_BUFFER_SIZE) numberDataToPrint = INPUT_BUFFER_SIZE;
                    for(int i = 0; i < numberDataToPrint; i++)
                    {
                        std::cout << std::bitset<8>(msgToDebg.dataBuffer[i]) << std::endl;
                    }
                    std::cout << "\n";
                    goto SHOWOPTIONS;
                }
                break;
            case 9:
                std::cout << "PC: " << std::bitset<32>(msgToDebg.PC) << std::endl;
                std::cout << "SP: " << std::bitset<32>(msgToDebg.SP) << std::endl;
                for(int i = 0; i < 8; i++) 
                {
                    std::cout << "R[" << i << "]: " << std::bitset<32>(msgToDebg.R[i]) << std::endl;
                }
                std::cout << "ZF: " << std::bitset<8>(msgToDebg.ZF) << std::endl;
                std::cout << "CF: " << std::bitset<8>(msgToDebg.CF) << std::endl;
                goto SHOWOPTIONS;
                break;
            case 10:
                {
                    std::string toModify = "";
                    std::cout << "Data to modify (in bit, 1VBYTE==8bit): ";
                    std::cin >> toModify;
                    if((toModify.length()/8) > MSG_FROM_DBG_SIZE) 
                    {
                        toModify = toModify.substr(0, MSG_FROM_DBG_SIZE);
                    }
                    msgFromDebg.buffer[0] = (toModify.length()/8) + '0';
                    msgFromDebg.cmdFlag = CMD_WRITE_MEM;
                    int counter = 1;
                    for(int k = 0; k < toModify.length(); k+=8) 
                    {
                        std::string binary_num = toModify.substr(k, 8); 
                        msgFromDebg.buffer[counter++] = std::stol(binary_num, nullptr, 2); 
                    }
                    serializeMSG(&msgFromDebg, bufferMSGfromDbg);
                    retValFromFunc = sendData(cliSocket, bufferMSGfromDbg, PACKET_FROM_DEBUGGER_SIZE);
                    if(retValFromFunc == SEND_ERROR) errorSend(cliSocket);
                }
                break;
            default:
                std::cout << "Unkonown command!\n";
                goto SHOWOPTIONS;
        }
    }

#ifdef  _LINUX_DEV_ENVIRONMENT
    close(cliSocket);
#else //_WIN32_DEV_ENVIRONMENT
    closesocket(cliSocket);
    WSACleanup();
#endif
}