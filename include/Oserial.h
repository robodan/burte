/*
 *	Definitions and constants for the Motorola 6850 ACIA.
 *	used in the Omnibyte OB68K1A board.
 *
 */

/*
 *	ACIA Commands
 */

#include <68332.h>
#include <68332new.h>


#define DISINT (SER_TE | SER_RE)
#define TMTERR 0
#define RCVERR (SER_PF | SER_FE | SER_NF | SER_OR)

#define TERMDAT ((volatile unsigned short *) SCDR)
#define TERMCTL ((volatile unsigned short *) SCCR1)
#define TERMCTL2 ((volatile unsigned short *) SCSR)

#define SER_CONFIG ((short) 0x0081)    /* QMCR  */
#define SER_INT_CONFIG ((short) 0x0240)


         /*  Definitions added for typing reasons.  */

#define SER_SCSR ((volatile short *) SCSR)
#define SER_SCCR0 ((volatile short *) SCCR0)
