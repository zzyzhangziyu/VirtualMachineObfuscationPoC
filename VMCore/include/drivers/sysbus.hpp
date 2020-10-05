#ifndef _SYSTEM_BUS_HPP
#define _SYSTEM_BUS_HPP

#include "global.hpp"
#include <iostream>
#include <string>

#ifdef _WIN32_DEV_ENVIRONMENT
    #include <Windows.h>

    #define DIR_CREATED 200000
    #define DIR_EXIST 200001
    #define OTHER_ERROR 200002
#else _LINUX_DEV_ENVIRONMENT
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #define DIR_CREATED 200000
    #define DIR_EXIST 200001
    #define MKDIR_ERROR 200002
#endif

class SYSBUS {
    private:

    public:
        SYSBUS();
        ~SYSBUS();
        int createDirectory(std::string, int);
        // int deleteDirectory(std::string);
        // int moveDirectory(std::string);
        // int copyDirectory(std::string);

        // int createFile(std::string, int);
        // int deleteFile(std::string);
        // int moveFile(std::string);
        // int copyFile(std::string);

        // int getProcessPid(std::string);
        // int killProcess(int);
};

#endif