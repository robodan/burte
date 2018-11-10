

/*  Definitions of system service routines for BURTE */
/*  Dan Christian 4-9-87 */

/*
 *
 *  Author             Date         Description
 *  --------------     --------     -----------------------------------------
 *  Andrew H. Fagg     11/05/93     Fixed wallclock reference so that it is
 *                                    its own variable.
 *
 *
 */

#ifndef BURTE_READ
#define BURTE_READ 1

#define NUM_SERVICE	25		/* service traps */
#define INIT       0 
#define FPUT       1 
#define FGET       2 
#define POST       3 
#define PEND       4 
#define CREATE     5 
#define START      6 
#define KILL       7 
#define SUICIDE    8 
#define WAIT       9 
#define SUSPEND    10 
#define RESUME     11
#define PRIORITY   12
#define STATE      13
#define WHO_AM_I   14
#define FREEZE     15
#define THAW       16
#define MSLEEP     17
#define SUPER_OUTP 18
#define SUPER_INP  19
#define SET_SCHEDULE_INTERVAL 20
#define NEXT_INTERVAL 21
#define SUPERVISOR 22
#define SUPER_OUTB 23
#define SUPER_INB  24

#define NO_PROC	0		/* process status */
#define STOPPED	0x1
#define PAUSED	0x2
#define WAITING	0x4
#define READY	0x10

#define P_EQUAL 0x1
#define P_SET	0x2
#define P_CHECK	0x4
#define P_TAS	0x8

typedef int (*PFI)();		/* pointer to function returning int */

extern int burte_state, sys_error, update_state; /* krn_vars variables */
extern short main_proc, current_proc, num_proc;
extern volatile long wall_clock;
extern volatile long wallclock;

/* #define wallclock ((unsigned long) wall_clock) */
#define LARGE (((unsigned long) 1) <<31)

extern PFI t2_proc, t3_proc;

#define krn_vars  ((int *)0x100) /* overwrite vectored interupts */
#define krn_table ((PFI *)0x140) /* room for 16 krn_vars */

#endif

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif
