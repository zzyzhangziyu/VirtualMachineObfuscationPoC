#include "main.hpp"

void printIntro()
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
    std::cout << "version 0.3.240121.0026\n" << std::endl;
}

void printOptions()
{
    std::cout << "Options:\n"
                << "\t1. Execute a program on the VM\n"
                << "\t2. Step execution\n"
                << "\t3. Exit debugger and exit debug mode in the VM\n"
                << "\t4. Set a value in a register\n"
                << "\t5. Set a flag\n"
                << "\t6. Show the stack\n"
                << "\t7. Show the code data\n"
                << "\t8. Show the data buffer\n"
                << "\t9. Show all registers\n"
                << "\t10. Write to the code data"
                << std::endl;
    std::cout << "Choice: ";
}


void errorSend(int cliSocket)
{
    std::cout << "Failed send data in debug\n";
#ifdef  _LINUX_DEV_ENVIRONMENT
    close(cliSocket);
#else _WIN32_DEV_ENVIRONMENT
    closesocket(cliSocket);
    WSACleanup();
#endif
    exit(-1);
}