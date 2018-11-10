/*=============TRAP SERVICE CALLS============

This allows a trap service routines to be decalared as follows:

	trap_service(r_trap) (trap_action, arg)
	long trap_action, *arg;
	{...}
This inserts inline assemble which saves the state of the calling process,
calls your trap handler with the trap_action passed to trap() (in trap.c)
and a pointer to the rest of the arguments passed to trap().  It then checks
burte_state to see if it should return directly or if it should run
the scheduler.

*/
/*
| trap number in d0
	
|	arguments	usp@(8)
|	trap ID		usp@(4)
|	system return	usp@

|	trap return	sp@(2)
|	trap status reg	sp
	.globl	_trap_service
_trap_service:
	jsr	_r_save
	movl	usp,a0
	pea	a0@(8)		|push address of arguments
	movl	a0@(4),sp@-	|push trap number
	jsr	_r_trap		|c trap handler

	addq	#8,sp
	cmpl	#ACTIVE,_burte_state
	beqs	clear_trap	| if active, run scheduler
	rte			| else, return normally     
*/

#define trap_service(fun) trap_service_(fun, .globl _##fun, _##fun##:, jsr __##fun, _##fun)

#define trap_service_(fun, dfun, lfun, jcfun, fcall)\
asm(" .text");\
asm(#dfun );\
asm(#lfun );\
asm(" jsr     _r_save");\
asm(" movl    usp,a0 ");\
asm(" pea     a0@(8)         |push address of arguments ");\
asm(" movl    a0@(4),sp@-    |push trap number ");\
asm(#jcfun);\
asm(" addql    #8,sp"); \
asm(" cmpl    #1,_burte_state  |check ACTIVE ");\
asm(" beq     clear_trap     | if active, run scheduler ");\
asm(" rte                    | else, return normally ");\
int fun();\
fcall 

/* a useful structure for setting up a trap  table. */
typedef struct  {		/* sturcture for arrays of trap args */
    signed char rtn;		/* =1 if a value is to be returned */
    signed char arg_cnt;	/* argument count */
    PFI funct;			/* function to call */
} TRAP_CALL;

/* Macros that evaluate to a pointer to the 68K system vector table */
#define TRAP_VECT(n) ((long *)(4* (32 + (n))))
