#include "../../include/drivers/sysbus.hpp"

#ifdef _LINUX_DEV_ENVIRONMENT
    class UNIX: public SYSBUS {
        public:
            UNIX();
            ~UNIX();
            int createDirectory();
            int deleteDirectory();
            int moveDirectory();
            int copyDirectory();
            int createFile();
            int deleteFile();
            int moveFile();
            int copyFile();

        private:
            int rmtree(const char *path);

    };

    UNIX::UNIX()
    {

    }

    UNIX::~UNIX()
    {
        
    }

    int UNIX::createDirectory()
    {
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
    }

    int UNIX::deleteDirectory()
    {
        return rmtree(dirName.c_str());
    }

    int UNIX::rmtree(const char *path)
    {
        size_t path_len;
        char *full_path;
        DIR *dir;
        struct stat stat_path, stat_entry;
        struct dirent *entry;

        // stat for the path
        stat(path, &stat_path);

        // if path does not exists or is not dir - exit with status -1
        if (S_ISDIR(stat_path.st_mode) == 0) return -1;

        // if not possible to read the directory for this user
        if ((dir = opendir(path)) == NULL) return -1;

        // the length of the path
        path_len = strlen(path);

        // iteration through entries in the directory
        while ((entry = readdir(dir)) != NULL)
        {
            // skip entries "." and ".."
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

            // determinate a full path of an entry
            full_path = calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
            strcpy(full_path, path);
            strcat(full_path, "/");
            strcat(full_path, entry->d_name);

            // stat for the entry
            stat(full_path, &stat_entry);

            // recursively remove a nested directory
            if (S_ISDIR(stat_entry.st_mode) != 0) {
                rmtree(full_path);
                continue;
            }

            // remove a file object
            if (unlink(full_path) == 0)
                printf("Removed a file: %s\n", full_path);
            else
                printf("Can`t remove a file: %s\n", full_path);
            free(full_path);
        }

        // remove the devastated directory and close the object of it
        if (rmdir(path) == 0)
        {
            printf("Removed a directory: %s\n", path);
            closedir(dir);
            return 0;
        }
        else
        {
            printf("Can`t remove a directory: %s\n", path);
            closedir(dir);
            return 0;
        }
    }
#endif