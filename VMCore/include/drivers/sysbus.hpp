#ifndef _SYSTEM_BUS_HPP
#define _SYSTEM_BUS_HPP

#include "global.hpp"
#include <iostream>
#include <string>
#include <fstream>

#ifdef _WIN32_DEV_ENVIRONMENT
    #include <Windows.h>
    #include <tchar.h>
    #include <shellapi.h>
#else _LINUX_DEV_ENVIRONMENT
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>

    #include <stdio.h>
    #include <string.h>
    #include <stdlib.h>

    // POSIX dependencies
    #include <dirent.h>
    #include <sys/stat.h>
    #include <unistd.h>
#endif

#define DIR_CREATED 200000
#define DIR_EXIST 200001
#define MOVE_DIR_EXIST 200002
#define COPY_DIR_EXIST 200003
#define OTHER_DIR_ERROR 200004
#define FILE_CREATED 200005
#define FILE_EXIST 200006
#define MOVE_FILE_EXIST 200007
#define COPY_FILE_EXIST 200008
#define OTHER_FILE_ERROR 200009

class SYSBUS {
    public:
        virtual int createDirectory() = 0;
        virtual int deleteDirectory() = 0;
        
        virtual int createFile() = 0;
        virtual int deleteFile() = 0;
        virtual int moveFile() = 0;
        virtual int copyFile() = 0;
};

#endif