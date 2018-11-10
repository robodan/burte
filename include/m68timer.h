/*
 *	Include file for Motorola's M6840 counter/timer.
 *
 * HISTORY
 * 22-Sep-83  Rafael Bracho (rxb) at Carnegie-Mellon University
 *	Status bits added.
 *
 *  2-Aug-83  Paul McAvinney (pmc) at Carnegie-Mellon University
 *	Created.
 *
 */


/*
 *	Addresses used in the Omnibyte OB68K1A board.
 */


#define	TMR_CR1	 (volatile unsigned char *)0xFFFF61 /* Wr TControl reg 1
				 	   (when TMR_CR2-0 = 1) */
#define	TMR_CR2	 (volatile unsigned char *)0xFFFF63 /* Wr TControl reg 2 */
#define	TMR_CR3	 (volatile unsigned char *)0xFFFF61 /* Wr TControl reg 3
					   (when TMR_CR2-0 = 0) */
#define	TMR_MSB	 (volatile unsigned char *)0xFFFF65 /* Wr MSB Buffer reg */
#define	TMR_LA1	 (volatile unsigned char *)0xFFFF67 /* Wr T1 Latch (LSB's) */
#define	TMR_LA2	 (volatile unsigned char *)0xFFFF6B /* Wr T2 Latch (LSB's) */
#define	TMR_LA3	 (volatile unsigned char *)0xFFFF6F /* Wr T3 Latch (LSB's) */
#define	TMR_STA	 (volatile unsigned char *)0xFFFF63 /* Rd TStatus reg */
#define	TMR_CT1	 (volatile unsigned char *)0xFFFF65 /* Rd T1 Counter (MSB's) */
#define	TMR_CT2	 (volatile unsigned char *)0xFFFF69 /* Rd T2 Counter (MSB's) */
#define	TMR_CT3	 (volatile unsigned char *)0xFFFF6D /* Rd T3 Counter (MSB's) */
#define	TMR_LSB	 (volatile unsigned char *)0xFFFF67 /* Rd LSB Buffer reg */

/*
 *	Timer Commands
 */

#define	WR_CR3	0x82			/* Select Control Reg. 3	  */
#define	WR_CR1	0x83			/* Select Control Reg. 1	  */
#define	ENA_CL1	0xC0			/* Enable Clock 1 Ints.		  */
#define	ENA_CL2	0xC0			/* Enable Clock 2 Ints.		  */
#define	ENA_CL3	0xC3			/* Enable Clock 3 Ints.		  */
#define	DIS_ALL	0x83			/* Stop All Clocks
					   (when written to CR1)	  */
#define	DIS_CL1	0x82			/* Disable Clock 1 Ints.	  */
#define	DIS_CL2	0x82			/* Disable Clock 2 Ints.	  */
#define	DIS_CL3	0x83			/* Disable Clock 3 Ints.	  */

/*
 *	Timer Status bits (interrupt flags)
 */

#define	INT1	0x01
#define	INT2	0x02
#define	INT3	0x04
