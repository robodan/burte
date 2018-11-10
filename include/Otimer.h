/*
 *	Include file for Motorola's M6840 counter/timer.
 */


/*
 *	Addresses used in the Omnibyte OB68K1A board.
 */


#define	TM_CR2	 ((volatile unsigned char *)0xFFFF63) /* Control reg 2 */
#define	TM_CR1	 ((volatile unsigned char *)0xFFFF61) /* Control reg 1
				 	   (when TM_CR2-0 = 1) */
#define	TM_CR3	 ((volatile unsigned char *)0xFFFF61) /* Control reg 3
					   (when TM_CR2-0 = 0) */
#define	TM_STA	 ((volatile unsigned char *)0xFFFF63) /* Status reg */

#define	TM_MSB	 ((volatile unsigned char *)0xFFFF65) /* Wr MSB Buffer reg */
#define	TM_LA1	 ((volatile unsigned char *)0xFFFF67) /* Wr T1 Latch (LSB) */
#define	TM_LA2	 ((volatile unsigned char *)0xFFFF6B) /* Wr T2 Latch (LSB) */
#define	TM_LA3	 ((volatile unsigned char *)0xFFFF6F) /* Wr T3 Latch (LSB) */
#define	TM_CT1	 ((volatile unsigned char *)0xFFFF65) /* Rd T1 Counter (MSB) */
#define	TM_CT2	 ((volatile unsigned char *)0xFFFF69) /* Rd T2 Counter (MSB) */
#define	TM_CT3	 ((volatile unsigned char *)0xFFFF6D) /* Rd T3 Counter (MSB) */
#define	TM_LSB	 ((volatile unsigned char *)0xFFFF67) /* Rd LSB Buffer reg */

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

#define	TM_INT1	0x01
#define	TM_INT2	0x02
#define	TM_INT3	0x04

/*
 * usage:
 *   Control registers are write only.  The status register is read only.
 *   The Counters are set by writing High byte to TM_MSB and then low byte
 *   to the appropriate register.
 *
 *   Counters are read by reading the high byte from the appropriate register
 *   and then reading the low byte from TM_LSB.
 */
