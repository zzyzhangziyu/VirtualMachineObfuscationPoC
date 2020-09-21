#include <iostream>
#include "../VMCore/include/opcodes.hpp"
#include "../VMCore/include/vmdebug.hpp"
#include <arpa/inet.h>

int main()
{
    std::cout << R"(
 _   ____  _______________ _____ _____ _____ _____ _____ 
| | | |  \/  || ___ \ ___ \  _  |_   _|  ___/  __ \_   _|
| | | | .  . || |_/ / |_/ / | | | | | | |__ | /  \/ | |  
| | | | |\/| ||  __/|    /| | | | | | |  __|| |     | |  
\ \_/ / |  | || |   | |\ \\ \_/ / | | | |___| \__/\ | |  
 \___/\_|  |_/\_|   \_| \_|\___/  \_/ \____/ \____/ \_/  
                                                         
                                                         
______ ___________ _   _ _____ _____  ___________        
|  _  \  ___| ___ \ | | |  __ \  __ \|  ___| ___ \       
| | | | |__ | |_/ / | | | |  \/ |  \/| |__ | |_/ /       
| | | |  __|| ___ \ | | | | __| | __ |  __||    /        
| |/ /| |___| |_/ / |_| | |_\ \ |_\ \| |___| |\ \        
|___/ \____/\____/ \___/ \____/\____/\____/\_| \_|       
                                                         
    )" << std::endl;
    std::cout << "version 0.2.200921.2026" << std::endl;

    int cliSocket = 0;
    struct sockaddr_in serv_addr;

    if ((cliSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    { 
        std::cout << "[ERROR] Failed socket creation\n"; 
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)  
    { 
        std::cout << "[ERROR] Invalid address\n";
        return -1;
    }

    if (connect(cliSocket, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
    { 
        std::cout << "[ERROR] Connection failed\n";
        return -1;
    }

    bool connLoop = true;
    MESSAGE_TO_DEBUGGER msgToDebg;
    MESSAGE_FROM_DEBUGGER msgFromDebg;
    char bufferMSGtoDbg[PACKET_TO_DEBUGGER_SIZE];
    char bufferMSGfromDbg[PACKET_FROM_DEBUGGER_SIZE];

    //TODO *******************
    while(connLoop)
    {

        connLoop = false;
    }

    close(cliSocket);
    return 0;
}