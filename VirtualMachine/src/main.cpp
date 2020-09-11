#include "../include/main.hpp"
#include "../include/vmcpu.hpp"
#include <sstream>

int main(int argc, char *argv[])
{

// TODO: to change


//     if(argc != 2) {
//         std::cout << "[ERROR] WRONG ARGUMENTS!" << std::endl;
//         std::cout << "Usage: VMPROTECT file_name_to_run" << std::endl;
//         exit(1);
//     }

//     std::string fileName;
//     std::stringstream fileStream;
//     VMCPU *vm = new VMCPU();
//     std::string password;

//     fileStream << argv[1];
//     fileStream >> fileName;

//     BYTE *mc;
    
//     int mcsize = -1;
//     try
//     {
//         mc = loadProtectedCode(mcsize, fileName);
//     }
//     catch (int e)
//     {
//         std::cout << "[ERROR " << e << "] NO FILE OR STH ELSE \n";
//         return -1;
//     }

//     do {
//         password.clear();
//         std::cout << "PASSWORD: ";
//         std::cin >> password;
//     } while((password.length()) < 2 || (password.length()) > 100);

//     BYTE *usrInput = new BYTE((password.length()) + 1);
//     try {
//         memset(usrInput, 0, (password.length()));
//         for(unsigned int i = 0; i < (password.length()); i++) {
//             usrInput[i] = (BYTE) password[i];
//         }
//         usrInput[(password.length())] = (BYTE) 0;
//     } catch (...) {
//         std::cout << "[ERROR] FAILED ON GET INPUT \n";
//         goto ERROR;
//     }

//     if(!vm->loadCode(mc, mcsize, usrInput, password.size()))
//     {
//         goto ERROR;
//     }

//     goto OK;

// ERROR:
//     delete[] usrInput;
//     delete[] mc;
//     return -1;
// OK:
//     delete[] usrInput;
//     delete[] mc;
    
//     try{
//         vm->run();
//     } catch(...){
//         return -1;
//     }

    return 0;
}
