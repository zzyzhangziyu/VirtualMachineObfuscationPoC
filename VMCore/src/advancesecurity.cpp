#include "../include/advancesecurity.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT

#else //_LINUX_DEV_ENVIRONMENT
    void checkPtrace()
    {
        int offset = 10;
        if (ptrace(PTRACE_TRACEME, 0, 1, 0) == 0) offset = 66;
        if (ptrace(PTRACE_TRACEME, 0, 1, 0) == -1) offset *= 23;
        if (offset != 66 * 23) 
        {
            unsigned milliseconds = 100 * argc;
            VMCPU *vm = new VMCPU();
            usleep(milliseconds * 1000);
            exit(0);
        }
    }
#endif