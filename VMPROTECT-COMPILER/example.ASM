; Usr input (addr) saved in R0

%include "vm.inc"

main:
    mov r1, r0
    movw r3, 0x3
    movw r2, 0x0
    movw r4, 0x0
    movw r5, 0x0
    advr r3, 0x2

JLL9:
    movmrb r2, r1
    adrr r4, r2
    advr r4, 0x5
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz JLL8

    adrr r4, r2
    advr r4, 0xa
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz JLL8

    adrr r4, r2
    subvr r4, 0x6
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz JLL8

    adrr r4, r2
    subvr r4, 0xc
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz JLL8

    adrr r4, r2
    advr r4, 0xf
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz JLL8

    jnz JLL9

JLL8:    
    advr r3, 0x5
    movw r5, 0x980
    xor r4, r5
    cmp r4, r3
    jz JLL6
    jnz JLL7

JLL6:
; PRINT "PASS"
    jmp JLL5

JLL7:
; PRINT "FAILED"
    jmp JLL4

JLL5:
    movw r1, data1
    jmp JLL3

JLL4:
    movw r1, data2
    jmp JLL3

JLL3:
    mov r2, r1
    advr r2, 0x1
    movw r3, 0x0
    movw r4, 0x0

JLL1:
    movmrb r3, r1
    push r3
    poc
    advr r1, 0x1
    advr r2, 0x1
    movmrb r3, r2
    cmp r3, r4
    jz JLL2
    jnz JLL1

JLL2:
    movmrb r3, r1
    push r3
    pocn
    ee

data1:
    db "PASS", 0 
data2:
    db "FAILED", 0