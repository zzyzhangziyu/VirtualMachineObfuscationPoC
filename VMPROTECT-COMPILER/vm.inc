[org 0x0]

; Registers.
%define r0 0
%define r1 1
%define r2 2
%define r3 3
%define r4 4
%define r5 5
%define r6 6
%define r7 7

%macro nop
db 0x00
%endmacro

%macro ee
db 0xee
%endmacro

%macro mov 2
db 0x01, %1, %2
%endmacro

%macro movmb 2
db 0x02, %1 
dd %2
%endmacro

%macro movmw 2
db 0x03, %1 
dd %2
%endmacro

%macro movb 2
db 0x04, %1 
db %2
%endmacro

%macro movw 2
db 0x05, %1 
dw %2
%endmacro