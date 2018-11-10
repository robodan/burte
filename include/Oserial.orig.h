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

/*
#define	MRESET	0x13		/* Master Reset, Disable all interrupts. */
#define	ENAINT	0xB5		/* Enable all interrupts. RTS disabled.
				   Divide by 16. 8 bits, 1 stop, no parity */
#define	DISINT	0x15		/* Same as above except no interrupts
				   are enabled */

/* control register definitions */
#define	RENA		0x80	/* Receive Interrupt enable bit */
#define TENA		0x20	/* Transmit Interupt enable bit (0x40 low) */

/* status register definitions */
#define	RDRF		0x01	/* Receive Data Register Full	*/
#define	TDRE		0x02	/* Transmit Data Register Empty	*/
#define	FRERR		0x10	/* Framing Error (break)	*/
#define IREQ		0x80	/* Interupt requested */

#define TMTERR		0x08	/* Transmit error (CTS) (not wanted)	*/
#define RCVERR		0x64	/* Receive error (not wanted)	*/

/*
 *	For the CPU status register.
 */

#define SLPRIO	5		/* Interrupt level of dart == 5 */

/*
 *	ACIA Register Addresses
 */

#define TERMDAT	((volatile char *)0xFFFF03) /* ACIA 0 Data Reg */
#define TERMCTL	((volatile unsigned char *)0xFFFF01) /* ACIA 0 Control Reg */
#define HOSTDAT	((volatile char *)0xFFFF23) /* ACIA 1 Data Reg */
#define HOSTCTL	((volatile unsigned char *)0xFFFF21) /* ACIA 1 Control Reg */

#define SLBAUD	((volatile char *)0xFFFF10) /* Hardware address of baud rate */
*/

#define DISINT 0
#define TMTERR 0
#define RCVERR (SER_PF | SER_FE | SER_NF | SER_OR)

#define TERMDAT ((short *) SCDR)
#define TERMCTL ((short *) SCCR1)

#define SER_CONFIG (short 0x0081)    /* QMCR  */
#define SER_INT_CONFIG (short 0x0240)
