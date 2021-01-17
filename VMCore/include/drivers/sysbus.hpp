#ifndef _SYSTEM_BUS_HPP
#define _SYSTEM_BUS_HPP

#include "global.hpp"
#include <iostream>
#include <string>
#include <fstream>

#include "../../../SharedCode/datatypes.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    #include <Windows.h>
    #include <tchar.h>
    #include <shellapi.h>
#else _LINUX_DEV_ENVIRONMENT
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <stdlib.h>
#endif

#define DIR_CREATED 200000
#define DIR_CREATED_ERROR 200001
#define DIR_EXIST 200002
#define DELETE_DIR 200011
#define MOVE_DIR 200003
#define COPY_DIR 200004
#define OTHER_DIR_ERROR 200005
#define FILE_CREATED 200006
#define FILE_EXIST 200007
#define DELETE_FILE 200012
#define MOVE_FILE 200008
#define COPY_FILE 200009
#define OTHER_FILE_ERROR 200010

class SYSBUS {
    public:
        virtual int createDirectory(std::string, int)) = 0;
        virtual int deleteDirectory(std::string) = 0;
        virtual int moveDirectory(std::string, std::string) = 0;
        virtual int copyDirectory(std::string, std::string) = 0;
        int createFile(std::string fileName, VBYTE *dataToWrite)
        {
            int dataSize = sizeof(data);
            std::fstream fs;
            fs.open(fileName.c_str(), std::fstream::out | std::fstream::binary);
            fs.write((char*)data, dataSize);
	        fs.close();
            return 0;
        }
        virtual int deleteFile(std::string) = 0;
        virtual int moveFile(std::string, std::string) = 0;
        virtual int copyFile(std::string, std::string) = 0;
};

#endif