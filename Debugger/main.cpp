#include "./main.hpp"

int main()
{
    printIntro();
#ifdef _WIN32_DEV_ENVIRONMENT
    return 0;
#else _LINUX_DEV_ENVIRONMENT
    return setLinuxConnection();
#endif
}