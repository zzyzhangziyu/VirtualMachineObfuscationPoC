#include "../../include/drivers/sysbus.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    SYSBUS::SYSBUS()
    {

    }

    SYSBUS::~SYSBUS()
    {
        
    }

    int SYSBUS::createDirectory(std::string dirName, int dirMode)
    {
        if (CreateDirectoryA(dirName.c_str(), NULL)) return DIR_CREATED;
        else if (ERROR_ALREADY_EXISTS == GetLastError()) return DIR_EXIST;
        else return OTHER_ERROR;
    }

    int SYSBUS::deleteDirectory(std::string dirName)
    {

    }
#endif