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
    #include <fcntl.h>
    #include <unistd.h>
    #include <errno.h>
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
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
#define NO_IMPLEMENTED_ERROR 200110

#define SYSBUS_CREATE_DIR 1
#define SYSBUS_DELETE_DIR 2
#define SYSBUS_MOVE_DIR 3
#define SYSBUS_COPY_DIR 4
#define SYSBUS_CREATE_FILE 5
#define SYSBUS_DELETE_FILE 6
#define SYSBUS_MOVE_FILE 7
#define SYSBUS_COPY_FILE 8

class SYSBUS {
    public:
        virtual int createDirectory(std::string, int)) = 0;
        virtual int deleteDirectory(std::string) = 0;
        virtual int moveDirectory(std::string, std::string) = 0;
        virtual int copyDirectory(std::string, std::string) = 0;
        int createFile(std::string fileName, VBYTE *dataToWrite, int dataSize)
        {
            std::fstream fs;
            fs.open(fileName.c_str(), std::fstream::in);
            if(fs)
            {
                fs.close();
                fs.open(fileName.c_str(), std::fstream::out | std::fstream:: app| std::fstream::binary);
            }
            else fs.open(fileName.c_str(), std::fstream::out | std::fstream::binary);
            fs.write((char*)dataToWrite, dataSize);
            fs.close();
            return 0;
        }
        virtual int deleteFile(std::string) = 0;
        virtual int moveFile(std::string, std::string) = 0;
        virtual int copyFile(std::string, std::string) = 0;
};

#ifdef _LINUX_DEV_ENVIRONMENT
    class UNIX: public SYSBUS {
        public:
            UNIX();
            ~UNIX();
            int createDirectory(std::string, int);
            int deleteDirectory(std::string);
            int moveDirectory(std::string, std::string);
            int copyDirectory(std::string, std::string);
            int deleteFile(std::string);
            int moveFile(std::string, std::string);
            int copyFile(std::string, std::string);

        private:
            mode_t getMode(int);
    };
#endif
#ifdef _WIN32_DEV_ENVIRONMENT
    class WIN32: public SYSBUS {
        public:
            WIN32();
            ~WIN32();
            int createDirectory(std::string, int);
            int deleteDirectory(std::string);
            int moveDirectory(std::string, std::string);
            int copyDirectory(std::string, std::string);
            int deleteFile(std::string);
            int moveFile(std::string, std::string);
            int copyFile(std::string, std::string);

        private:
            bool deleteDir(LPCTSTR);
            bool copyDir(std::wstring, std::wstring);
            std::wstringstringToWString(const std::string&);
    };
#endif

#endif