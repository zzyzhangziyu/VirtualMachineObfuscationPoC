#ifndef _ADVM_SEC_HPP
#define _ADVM_SEC_HPP

#include <iostream>

#include "vmcpu.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    
#else //_LINUX_DEV_ENVIRONMENT
    /* ****** HEADERS ****** */
    #include <unistd.h>
    #include <sys/ptrace.h>
    /* ****** FUNCTIONS ****** */
    void checkPtrace(int);
#endif

#endif //_ADVM_SEC_HPP