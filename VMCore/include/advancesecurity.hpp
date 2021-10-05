#ifndef _ADVM_SEC_HPP
#define _ADVM_SEC_HPP

#include <iostream>

#include "vmcpu.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    /* ****** HEADERS ****** */
    #include <intrin.h>
    /* ****** FUNCTIONS ****** */
#else //_LINUX_DEV_ENVIRONMENT
    /* ****** HEADERS ****** */
    #include <unistd.h>
    #include <sys/ptrace.h>
    #include <cpuid.h>
    /* ****** FUNCTIONS ****** */
    void checkPtrace(int);
#endif

/* ****** FUNCTIONS ****** */
void isHypervisor(void);

#endif //_ADVM_SEC_HPP