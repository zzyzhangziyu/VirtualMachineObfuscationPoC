#include "../include/vmcpu.hpp"

void VMCPU::vmPrint(VBYTE s) { std::cout << s; }

void VMCPU::vmPrintHX(VDWORD hx) { std::cout << std::hex << hx; }

void VMCPU::vmPrintN(VBYTE s) { std::cout << s << std::endl; }

void VMCPU::vmPrintHXN(VDWORD hx) { std::cout << std::hex << hx << std::endl; }