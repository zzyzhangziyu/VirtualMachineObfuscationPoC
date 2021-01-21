#ifndef _VM_CPU_HPP
#define _VM_CPU_HPP

#include <iostream>
#include <string.h>
#include <stdint.h>
#include <vector>
#include <sstream>

#include "./opcodes.hpp"
#include "./advancesecurity.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    #include "./drivers/win32sysbus.hpp"
#else //_LINUX_DEV_ENVIRONMENT
    #include "./drivers/linuxsysbus.hpp"
#endif

// #define V_DEBUG

#ifdef VMTESTS
    #include "./test.hpp"
#endif //VMTESTS

#include "../../SharedCode/datatypes.hpp"

#define CODE_DATA_SIZE 51200
#define STACK_SIZE 256
#define INPUT_BUFFER_SIZE 1024

#include "./vmdebug.hpp"

typedef struct {
    /* Here will be a code to execute and other data - 50KB*/
    VBYTE codeData[CODE_DATA_SIZE];

    /* Size of one element is VDWORD 
    in order to be able to push addresses. */
    VDWORD stack[STACK_SIZE];

    /* Here will be a user input*/
    VBYTE dataBuffer[INPUT_BUFFER_SIZE];
} ADDRESS_SPACE, *PADDRESS_SPACE;

typedef struct {
    /* General Purpose Registers R0 -> R7 */
    VDWORD R[8];
    struct {
        /* Zero Flag 
            value 1 - flag is set if the result of the last comparison was zero
            value 0 - flag is not set
        */
        unsigned char ZF : 1;
        /* Carry Flag 
            value 1 - flag is set the results of the last comparison was moving
            value 0 - flag is not set
        */
        unsigned char CF : 1;
    };
    /* Program Counter */
    VDWORD PC;
    /* Stack Pointer */
    VDWORD SP;
} REGISTERSS, *PREGISTERSS;


#ifdef _VM_CPU_TEST_
    enum class VCpuFlag {OK = 0, ERROR, UNDERFLOW, OVERFLOW};
#endif // _VM_CPU_TEST_

class VMCPU {
    private:
        PADDRESS_SPACE AS;
        PREGISTERSS REGS;
        #ifdef _WIN32_DEV_ENVIRONMENT
            WIN32 *sysBus;
        #else //_LINUX_DEV_ENVIRONMENT
            UNIX *sysBus;
        #endif

    private:
        int executer(VBYTE);
        void getDataFromCodeData(std::string &, int);
        void vmPrint(VBYTE s);
        void vmPrintHX(VDWORD);
        void vmPrintN(VBYTE s);
        void vmPrintHXN(VDWORD);
        //void vmScan();

    public:
        VMCPU();
        ~VMCPU();
        void run();
        void debug();
        bool loadCode(VBYTE *, int);

    #ifdef _VM_CPU_TEST_
    public:
        static const bool bIsOnTest = true;
        VCpuFlag vcpuFlag;

        PADDRESS_SPACE getAS() { return AS; }
        PREGISTERSS getREGS() { return REGS; }
    #endif // _VM_CPU_TEST_
};

#endif //_VM_CPU_HPP