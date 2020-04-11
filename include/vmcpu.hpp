#ifndef _VM_CPU_HPP
#define _VM_CPU_HPP

#include <iostream>
#include <string.h>
#include <stdint.h>

//#include "./test.hpp"

typedef uint8_t BYTE;
typedef uint16_t WORD;
typedef uint32_t DWORD;

typedef struct {
    /* Here will be a code to execute and other data - 50KB*/
    BYTE codeData[51200];

    /* Size of one element is DWORD 
    in order to be able to push addresses. */
    DWORD stack[256];
} ADDRESS_SPACE, *PADDRESS_SPACE;

typedef struct {
    /* General Purpose Registers R0 -> R7 */
    DWORD R[8];
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
    DWORD PC;
    /* Stack Pointer */
    DWORD SP;
} REGISTERSS, *PREGISTERSS;


#ifdef VM_TEST
    enum class VCpuFlag {OK = 0, ERROR, UNDERFLOW, OVERFLOW};
#endif // VM_TEST

class VMCPU {
    private:
        PADDRESS_SPACE AS;
        PREGISTERSS REGS;

    private:
        void vmPrint(BYTE s);
        void vmPrintN(BYTE s);
        //void vmScan();

    public:
        VMCPU();
        ~VMCPU();
        void run();
        bool loadCode(BYTE *, int, BYTE *, int);

    #ifdef VM_TEST
    public:
        static const bool bIsOnTest = true;
        VCpuFlag vcpuFlag;

        PADDRESS_SPACE getAS() { return AS; }
        PREGISTERSS getREGS() { return REGS; }
    #endif // VM_TEST
};

#endif //_VM_CPU_HPP