#ifndef _MAIN_HPP
#define _MAIN_HPP

#include <iostream>

typedef uint8_t VBYTE;
typedef uint16_t VWORD;
typedef uint32_t VDWORD;

#define MAGIC_NUMBER (uint16_t)0x566d
#define MODE_DEBUG "debug"
#define MODE_EXEC "exec"

VBYTE* loadProtectedCode(int &, std::string, bool&, int&, int*);
int checkOpcodeSize(VBYTE);

#endif //_MAIN_HPP