#include "../../include/drivers/sysbus.hpp"

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

    UNIX::UNIX() { }

    UNIX::~UNIX() { }

    int UNIX::createDirectory(std::string dirName, int dirMode)
    {
        sstruct stat st = {0};

        if (stat(dirName.c_str(), &st) == 0) // checking if the directory exists
        {
            if(!mkdir(dirName.c_str(), getMode(dirMode))) return DIR_CREATED_ERROR;
            return DIR_CREATED;
        }
        else return DIR_EXIST;
    }

    UNIX::mode_t getMode(int m)
    {
        mode_t mode = 0;
        std::string s = std::to_string(m);
        // 1111111111 == rwxrwxrwx
        // 1000000000 == ---------
        const char *perm = s.c_str();

        if (perm[1] == '1') mode |= 0400;
        if (perm[2] == '1') mode |= 0200;
        if (perm[3] == '1') mode |= 0100;
        if (perm[4] == '1') mode |= 0040;
        if (perm[5] == '1') mode |= 0020;
        if (perm[6] == '1') mode |= 0010;
        if (perm[7] == '1') mode |= 0004;
        if (perm[8] == '1') mode |= 0002;
        if (perm[9] == '1') mode |= 0001;

        return mode;
    }

#endif