; Usr input (addr) saved in R0

; Enter 
    mov r1, r0
    movw r3, 0x3
    movw r2, 0x0
    movw r4, 0x0
    movw r5, 0x0
    advr r3, 0x2

9JLL:
    movmrb r2, r1
    adrr r4, R2
    advr r4, 0x5
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz 8JLL

    adrr r4, r2
    advr r4, 0xa
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz 8JLL

    adrr r4, r2
    subvr r4, 0x6
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz 8JLL

    drr r4, r2
    subvr r4, 0xc
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz 8JLL

    adrr r4, r2
    advr r4, 0xf
    advr r1, 0x1
    movmrb r2, r1
    cmp r2, r5
    jz 8JLL

    jnz 9JLL

8JLL:    
    advr r3, 0x5
    movw r5, 0x980
    xor r4, r5
    cmp r4, r3
    jz 6JLL
    jnz 7JLL

6JLL:
; PRINT "PASS"
    jmp 5JLL

7JLL:
; PRINT "FAILED"
    jmp 4JLL

5JLL:
    movw r1, 1DL
    jmp 3JLL

4JLL:
    movw r1, 2DL
    jmp 3JLL

3JLL:
    mov r2, r1
    advr r2, 0x1
    movw r3, 0x0
    movw r4, 0x0

1JLL:
    movmrb r3, r1
    push r3
    poc
    advr r1, 0x1
    advr r2, 0x1
    movmrb r3, r2
    cmp r3, r4
    jz 2JLL
    jnz 1JLL

2JLL:
    movmrb r3, r1
    push r3
    pocn
    ee

1DL:
    db "PASS", 0 
2DL:
    db "FAILED", 0