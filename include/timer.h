/* timer support definitions */

/* these are wrong for the omnibyte: FIX IT */

#define TM_cntrl ((char *) 0x10021)
#define TIME_INTOFF 0xa0		/* periodic, no-interupt, clk source */
#define TIME_INTON 0xa1
