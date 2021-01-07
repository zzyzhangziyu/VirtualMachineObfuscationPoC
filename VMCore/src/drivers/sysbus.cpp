#include "../../include/drivers/sysbus.hpp"

SYSBUS::SYSBUS()
{

}

SYSBUS::~SYSBUS()
{
    
}

int SYSBUS::createDirectory(std::string dirName, int dirMode)
{
#ifdef _WIN32_DEV_ENVIRONMENT
    if (CreateDirectoryA(dirName.c_str(), NULL)) return DIR_CREATED;
    else if (ERROR_ALREADY_EXISTS == GetLastError()) return DIR_EXIST;
    else return OTHER_ERROR;
#else _LINUX_DEV_ENVIRONMENT
    struct stat st = {0};
    int status;

    if (stat(dirName.c_str(), &st) == -1) // checking if the directory exists
    {
        status = mkdir(dirName.c_str(), dirMode);
        if(status != 0) return MKDIR_ERROR;
        return DIR_CREATED;
    }
    else 
    {
        return DIR_EXIST;
    }
#endif
}