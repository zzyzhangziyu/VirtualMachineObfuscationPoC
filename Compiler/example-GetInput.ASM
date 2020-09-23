%include "vm.inc"

start:
    dw 0xccea
; PRINT "PASS"
    movd r1, data1
    mov r2, r1
    advrd r2, 0x1
    movd r3, 0x0
    movd r4, 0x0
GETIN1:
    mov r3, r1
    push r3
    poc
    advrd r1, 0x1
    advrd r2, 0x1
    movmrb r3, r2
    cmp r3, r4
    jz GETIN2
    jnz GETIN1
GETIN2:
    tib
    ee

data1:
    db "WRITE TEXT: ", 0