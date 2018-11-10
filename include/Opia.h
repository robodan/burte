/* Motarola 6821 PIA chip macros (for Omnibyte) */

#define PIA1_PRA        ((volatile unsigned char *) 0xffff41)
#define PIA1_PRB        ((volatile unsigned char *) 0xffff43)
#define PIA1_CRA        ((volatile unsigned char *) 0xffff45)
#define PIA1_CRB        ((volatile unsigned char *) 0xffff47)
#define PIA2_PRA        ((volatile unsigned char *) 0xffff40)
#define PIA2_PRB        ((volatile unsigned char *) 0xffff42)
#define PIA2_CRA        ((volatile unsigned char *) 0xffff44)
#define PIA2_CRB        ((volatile unsigned char *) 0xffff46)

#define DSTRB	0x2c		/* data strobe on b */
#define DIOD	0x04		/* data io direction reg */
