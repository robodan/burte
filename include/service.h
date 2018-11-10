/* ===============INTERUPT SERVICE CALLS ON THE 68000==============

	3/21/92		Andrew H. Fagg		Updated for new version of gcc

This package permits the use of the expression
	i_service(fun)
in place of the usual way to begin a function definition, namely
	fun()

Invoking i_service(fun) generates a self-contained function named
'fun' which handles all the register and state save necessary to 
interface to BURTE.

Example usage:

i_service(KbdServ) {
    qput (&_file[0].data, *TERMDAT);
}

There are NEVER any arguments passed in and a value is NEVER returned.
================================================================= */

#define i_service(fun) i_service_(fun, .globl _##fun, _##fun##:, jsr __##fun, _##fun)

#define i_service_(fun, dfun, lfun, jcfun, fcall)\
asm(" .text ");\
asm(#dfun);\
asm(#lfun);\
asm(" btst  #5,sp@        | supervisor bit is bit 13 ");\
asm(" bne   9f           | bit was set: supervisor mode  ");\
asm(" tstl  _burte_state");\
asm(" beq   9f");\
asm(" jsr _r_save           | save user state.");\
asm(#jcfun);\
asm(" bra     run_a_proc    |restart user ");\
asm("9:   moveml #0xc0c0,sp@-  |push d0,d1,a0,a1 ");\
asm(#jcfun);\
asm(" moveml  sp@+,#0x0303  |restore d0,d1,a0,a1 ");\
asm(" rte ");\
int fun();\
fcall()

/* =============REENTRANT CALLS===============

Reentrant calls are just like i_service calls, except a function declared
reentrant never calls the scheduler.  This means that reentrant rountines 
must not make any system calls or change any system state.

Example usage:

reentrant(servo) {
	*OUT1 = Kp * Perr + Kd * Verr;
}

There are NEVER any arguments passed in and a value is NEVER returned.
================================================================= */


#define reentrant(fun) reentrant_(fun, .globl _##fun, _##fun##:, jsr __##fun, _##fun)

#define reentrant_(fun, dfun, lfun, jcfun, fcall)\
asm(" .text");\
asm(" .even");\
asm(#dfun );\
asm(#lfun);\
asm("	moveml	#0xc0c0,sp@-");\
asm(#jcfun);\
asm("	moveml	sp@+,#0x0303");\
asm("	rte");\
int fun();\
fcall()

/* Macros that evaluate to a pointer to the 68K system vector table */
#define INT_VECT(n)  ((long *)(4* (24 + (n))))

/* NOTE: Code with i_service, reentrant, or trap_service declarations 
MAY BE OPTIMIZED since the assembly code forms a seperate routine.

	Inline assemble which is inside a C routine cannot usually 
be optimized.
*/
