/*
There are NEVER any arguments passed in and a value is NEVER returned.
================================================================= */

#define i_service2(fun) i_service2_(fun, .globl _##fun, _##fun##:, jsr __##fun, _##fun)

#define i_service2_(fun, dfun, lfun, jcfun, fcall)\
asm(" .text ");\
asm(#dfun);\
asm(#lfun);\
asm("moveml #0xc0c0,sp@-  |push d0,d1,a0,a1 ");\
asm(#jcfun);\
asm(" moveml  sp@+,#0x0303  |restore d0,d1,a0,a1 ");\
asm(" rte ");\
int fun();\
fcall()

