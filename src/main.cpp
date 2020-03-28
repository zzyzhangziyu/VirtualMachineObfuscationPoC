#include "../include/main.hpp"
#include "../include/vmcpu.hpp"

int main(int argc, char *argv[])
{
    std::cout << "***************" << std::endl;
    std::cout << "VMPROTECT v0.1" << std::endl;
    std::cout << "***************" << std::endl;

    if(argc != 2) {
        std::cout << "[ERROR] WRONG ARGUMENTS!" << std::endl;
        std::cout << "Usage: VMPROTECT file_name_to_run" << std::endl;
        exit(1);
    }

    std::string fileName;
    std::stringstream ssFileName;
    VMCPU *vm = new VMCPU();
    std::string password;

    ssFileName << argv[1];
    ss >> fileName;
    ssFileName.clear();

    do {
        std::cout << "PASSWORD: ";
        std::cin >> password;
    } while(password.size() < 2 || password.size() > 26);

    BYTE *usrInput = new BYTE(password.size() + 1);
    try {
        memset(usrInput, 0, sizeof(usrInput)/sizeof(usrInput[0]));
        for(unsigned int i =0; i < password.size(); i++) {
            usrInput[i] = (BYTE) password[i];
        }
        usrInput[password.size()] = (BYTE) 0;
    } catch (...) {
        delete[] usrInput;
        delete vm;
        return -1;
    }

    BYTE *mc = NULL;

    int mcsize = -1;
    try
    {
        mcsize = loadProtectedCode(&mc, fileName);
    }
    catch (int e)
    {
        std::cout << "[ERROR " + e + "] NO FILE OR STH ELSE \n";
        delete[] usrInput;
        delete[] mc;
        exit(1);
    }
    if(!vm->loadCode(mc, mcsize, usrInput, password.size()))
    {
        delete[] usrInput;
        delete[] mc;
        delete vm;
        return -1;
    }

    delete[] usrInput;
    delete[] mc;
    
    try{
        vm->run();
    } catch(...){
        delete vm;
        return -1;
    }

    delete vm;
    return 0;
}
