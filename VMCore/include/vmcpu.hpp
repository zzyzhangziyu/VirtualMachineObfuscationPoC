#ifndef _VM_CPU_HPP
#define _VM_CPU_HPP

#include <iostream>
#include <string.h>
#include <stdint.h>

#ifdef _WIN32_DEV_ENVIRONMENT
    #include <Windows.h>
#else _LINUX_DEV_ENVIRONMENT
    #include <unistd.h>
#endif

#include <mutex>
#include <thread>

#include "./opcodes.hpp"

#ifdef VMTESTS
    #include "./test.hpp"
#endif //VMTESTS

typedef uint8_t VBYTE;
typedef uint16_t VWORD;
typedef uint32_t VDWORD;

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
    public:
        bool areFramesNeeded;
        int countFrames;
        int *framesSizeArray;

    private:
        PADDRESS_SPACE AS;
        PREGISTERSS REGS;

        std::mutex memMutex;
        bool isVMcpuTurnOff;

        bool areFrames;

    private:
        int executer(VBYTE);
        void vmPrint(VBYTE s);
        void vmPrintHX(VDWORD);
        void vmPrintN(VBYTE s);
        void vmPrintHXN(VDWORD);
        //void vmScan();

        void memoryManager();

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