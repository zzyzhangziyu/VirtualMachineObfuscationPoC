#include "../include/vmcpu.hpp"

#ifdef _WIN32_DEV_ENVIRONMENT
    #include <string>
#endif

//#define V_DEBUG
//#include <bitset>

VMCPU::VMCPU()
{
    AS = (PADDRESS_SPACE) new ADDRESS_SPACE;
    REGS = (PREGISTERSS) new REGISTERSS;

    memset(AS->codeData, 0, sizeof(AS->codeData));

    REGS->PC = 0;
    REGS->SP = sizeof(AS->stack) / sizeof(VDWORD);
}

VMCPU::~VMCPU()
{
    delete AS;
    delete REGS;
}

bool VMCPU::loadCode(VBYTE *mcode, int mcsize)
{
    memset(AS->codeData, 0, CODE_DATA_SIZE*sizeof(*(AS->codeData)));
    memset(AS->stack, 0, STACK_SIZE*sizeof(*(AS->stack)));
    memset(AS->dataBuffer, 0, INPUT_BUFFER_SIZE*sizeof(*(AS->dataBuffer)));
    if((unsigned) (mcsize) > (sizeof(AS->codeData) / sizeof(AS->codeData[0]))) 
    {
        std::cout << "[ERROR 101001] TOO BIG A CODE TO EXECUTE!\n";
        return false;
    }
    memcpy(AS->codeData, mcode, mcsize);
    for(int i = 0; i < 8; i++)
    {
        REGS->R[i] = (VDWORD) 0;
    }
    REGS->CF = 0;
    REGS->ZF = 0;
    return true;
}

void VMCPU::vmPrint(VBYTE s)
{
    std::cout << s;
}

void VMCPU::vmPrintHX(VDWORD hx)
{
    std::cout << std::hex << hx;
}

void VMCPU::vmPrintN(VBYTE s)
{
    std::cout << s << std::endl;
}

void VMCPU::vmPrintHXN(VDWORD hx)
{
    std::cout << std::hex << hx << std::endl;
}

void VMCPU::run()
{
    bool exit = false;
    VBYTE opcode;

    while(!exit)
    {
        opcode = AS->codeData[REGS->PC++];
        exit = executer(opcode);
    }
    return;
}