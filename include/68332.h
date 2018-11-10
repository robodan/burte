/* 68332.h contains defines for the registers in the 68332 */
/* rev 0.1 Nov 18, 1991                                    */

/* the first define reflects the fact that the internal registers and       */
/* memory of the 332 can be mapped to two different address spaces          */
/* 0x00F00000 is the default power-up mapping, 0x00700000 can be programmed */

#define Y      0x0F00000      /* Module Memory Mapping */

#define PORT_BASE    (Y | 0x00FFF00)

#define  TMCR  (Y | 0x00FFE00)   /* TPU Module Configuration Register */
#define  TTCR  (Y | 0x00FFE02)
#define  DSCR  (Y | 0x00FFE04)
#define  DSSR  (Y | 0x00FFE06)
#define  TICR  (Y | 0x00FFE08)   /* TPU Interrupt Configuration Register */
#define  CIER  (Y | 0x00FFE0A)   /* Channel Interrupt Enable Register */
#define  CFSR0 (Y | 0x00FFE0C)   /* Channel Function Select Registers */
#define  CFSR1 (Y | 0x00FFE0E)
#define  CFSR2 (Y | 0x00FFE10)
#define  CFSR3 (Y | 0x00FFE12)
#define  HSQR0 (Y | 0x00FFE14)   
#define  HSQR1 (Y | 0x00FFE16)
#define  HSRR0 (Y | 0x00FFE18)   /* Host Service Request Registers */
#define  HSRR1 (Y | 0x00FFE1A)
#define  CPR0  (Y | 0x00FFE1C)   /* Channel Priority Registers */
#define  CPR1  (Y | 0x00FFE1E)   
#define  CISR  (Y | 0x00FFE20)   /* Channel Interrupt Status Register */

/* System Integration Module memory map, page 4-2 of MC68332 User's Manual */

#define MCR     (Y | 0x00ffa00) /* module configuration */
#define SIMTR   (Y | 0x00ffa02) /* module test          */
#define SYNCR   (Y | 0x00ffa04) /* clock synthesizer control */
#define RSR     (Y | 0x00ffa06) /* reset status reg     */
#define SIMTRE  (Y | 0x00ffa08) /* module test E        */

#define PORTE1  (Y | 0x00ffa10) /* port E data          */
#define PORTE0  (Y | 0x00ffa12) /* port E data          */
#define DDRE    (Y | 0x00ffa14) /* port E data direction*/
#define PEPAR   (Y | 0x00ffa16) /* port E pin assignment*/
#define PORTF1  (Y | 0x00ffa18) /* port F data          */
#define PORTF0  (Y | 0x00ffa1a) /* port F data          */
#define DDRF    (Y | 0x00ffa1c) /* port F data direction*/
#define PFPAR   (Y | 0x00ffa1e) /* port F pin assignment*/

#define SYPCR   (Y | 0x00ffa20) /* system protection control */
#define PICR    (Y | 0x00ffa22) /* periodic interrupt control */
#define PITR    (Y | 0x00ffa24) /* periodic interrupt timing  */
#define SWSR    (Y | 0x00ffa26) /* software  service    */

#define CSPDR   (Y | 0x00ffa40) /* port C data          */

#define CSPAR0  (Y | 0x00ffa44) /* chip-select pin assignment */
#define CSPAR1  (Y | 0x00ffa46) /* chip-select pin assignment */
#define CSBARBT (Y | 0x00ffa48) /* chip-select base boot      */
#define CSORBT  (Y | 0x00ffa4a) /* chip-select option boot    */
#define CSBAR0  (Y | 0x00ffa4c) /* chip-select base address 0 */
#define CSOR0   (Y | 0x00ffa4e) /* chip-select option 0       */
#define CSBAR1  (Y | 0x00ffa50) /* chip-select base address 1 */
#define CSOR1   (Y | 0x00ffa52) /* chip-select option 1       */
#define CSBAR2  (Y | 0x00ffa54) /* chip-select base address 2 */
#define CSOR2   (Y | 0x00ffa56) /* chip-select option 2       */
#define CSBAR3  (Y | 0x00ffa58) /* chip-select base address 3 */
#define CSOR3   (Y | 0x00ffa5a) /* chip-select option 3       */
#define CSBAR4  (Y | 0x00ffa5c) /* chip-select base address 4 */
#define CSOR4   (Y | 0x00ffa5e) /* chip-select option 4       */
#define CSBAR5  (Y | 0x00ffa60) /* chip-select base address 5 */
#define CSOR5   (Y | 0x00ffa62) /* chip-select option 5       */
#define CSBAR6  (Y | 0x00ffa64) /* chip-select base address 6 */
#define CSOR6   (Y | 0x00ffa66) /* chip-select option 6       */
#define CSBAR7  (Y | 0x00ffa68) /* chip-select base address 7 */
#define CSOR7   (Y | 0x00ffa6a) /* chip-select option 7       */
#define CSBAR8  (Y | 0x00ffa6c) /* chip-select base address 8 */
#define CSOR8   (Y | 0x00ffa6e) /* chip-select option 8       */
#define CSBAR9  (Y | 0x00ffa70) /* chip-select base address 9 */
#define CSOR9   (Y | 0x00ffa72) /* chip-select option 9       */
#define CSBAR10 (Y | 0x00ffa74) /* chip-select base address 10*/
#define CSOR10  (Y | 0x00ffa76) /* chip-select option 10      */

#define CSBAR_MSK 0xfff8   /* separate address from block size in */
                           /* Base Address Regs */

#define CS10MSK 0x0300       /* see page 4-34 MC68332 User's Guide */
#define CS09MSK 0x00c0
#define CS08MSK 0x0030
#define CS07MSK 0x000c
#define CS06MSK 0x0003
#define CS05MSK 0x3000
#define CS04MSK 0x0c00
#define CS03MSK 0x0300
#define CS02MSK 0x00c0
#define CS01MSK 0x0030

/* Serial Communications Interface */
#define SCCR0  (Y | 0x00ffc08)   /* control reg 0, baud rate */
#define SCCR1  (Y | 0x00ffc0a)   /* control reg 1            */
#define SCSR   (Y | 0x00ffc0c)   /* status                   */
#define SCDR   (Y | 0x00ffc0e)   /* serial data register     */

#define TE_RE_MSK 0x0c           /* xmit enable, rcv enable in SCCR1 */
#define TDRE_MSK  0x100          /* xmit data reg empty flag */
#define TC_MSK    0x080          /* xmit complete flag       */



                          /*  SCCR1 definitions.     */
#define SER_RESET 0x8000
#define SER_LOOPS 0x4000
#define SER_WORMS 0x2000
#define SER_ILT   0x1000
#define SER_PT    0x0800
#define SER_PE    0x0400
#define SER_M     0x0200
#define SER_WAKE  0x0100
#define SER_TIE   0x0080
#define SER_TCIE  0x0040
#define SER_REI   0x0020
#define SER_ILIE  0x0010
#define SER_TE    0x0008
#define SER_RE    0x0004
#define SER_RWU   0x0002
#define SER_SBK   0x0001

                          /*  SCCR2 definitions.    */
#define SER_TDRE  0x0100
#define SER_TC    0x0080
#define SER_RDRF  0x0040
#define SER_RAF   0x0020
#define SER_IDLE  0x0010
#define SER_OR    0x0008
#define SER_NF    0x0004
#define SER_FE    0x0002
#define SER_PF    0x0001

#define QMCR ((volatile unsigned short *) (Y | 0x00ffc00))   /*  QSM configuration  */
#define QILR ((volatile unsigned short *) (Y | 0x00ffc04))   /*  QSM configuration  */

#undef PITR
#define PITR    ((volatile unsigned short *) (Y | 0x00ffa24)) /* periodic interrupt timing  */
#undef PICR
#define PICR    ((volatile unsigned short *) (Y | 0x00ffa22)) /* periodic interrupt control */


#define  TPU_TMCR ((volatile unsigned short *) (Y | 0x00FFE00))  /* TPU Module Configuration Register */
#define  TPU_TTCR  ((volatile unsigned short *) (Y | 0x00FFE02))
#define  TPU_DSCR  ((volatile unsigned short *) (Y | 0x00FFE04))
#define  TPU_DSSR  ((volatile unsigned short *) (Y | 0x00FFE06))
#define  TPU_TICR  ((volatile unsigned short *) (Y | 0x00FFE08))   /* TPU Interrupt Configuration Register */
#define  TPU_CIER  ((volatile unsigned short *) (Y | 0x00FFE0A))   /* Channel Interrupt Enable Register */
#define  TPU_CFSR0 ((volatile unsigned short *) (Y | 0x00FFE0C))   /* Channel Function Select Registers */
#define  TPU_CFSR1 ((volatile unsigned short *) (Y | 0x00FFE0E))
#define  TPU_CFSR2 ((volatile unsigned short *) (Y | 0x00FFE10))
#define  TPU_CFSR3 ((volatile unsigned short *) (Y | 0x00FFE12))
#define  TPU_HSQR0 ((volatile unsigned short *) (Y | 0x00FFE14))  
#define  TPU_HSQR1 ((volatile unsigned short *) (Y | 0x00FFE16))
#define  TPU_HSRR0 ((volatile unsigned short *) (Y | 0x00FFE18))   /* Host Service Request Registers */
#define  TPU_HSRR1 ((volatile unsigned short *) (Y | 0x00FFE1A))
#define  TPU_CPR0  ((volatile unsigned short *) (Y | 0x00FFE1C))   /* Channel Priority Registers */
#define  TPU_CPR1  ((volatile unsigned short *) (Y | 0x00FFE1E))   
#define  TPU_CISR  ((volatile unsigned short *) (Y | 0x00FFE20))   /* Channel Interrupt Status Register */


				/* redefinitions */
#undef PFPAR
#undef PEPAR
#define PFPAR   ((volatile unsigned short *)(Y | 0x00ffa1e)) /* port F pin assignment*/
#define PEPAR   ((volatile unsigned short *)(Y | 0x00ffa16)) /* port E pin assignment*/



				/* Chip Select Definitions */

#define CS00MSK_16BIT 0x000C
#define CS01MSK_16BIT 0x0030
#define CS02MSK_16BIT 0x00C0
#define CS03MSK_16BIT 0x0300

#define CS04MSK_16BIT 0x0C00
#define CS05MSK_16BIT 0x3000
#define CS06MSK_16BIT 0x0003
#define CS07MSK_16BIT 0x000c
#define CS08MSK_16BIT 0x0030

#define CS09MSK_16BIT 0x00C0
#define CS10MSK_16BIT 0x0300

#define CS00MSK_8BIT 0x0008
#define CS01MSK_8BIT 0x0020
#define CS02MSK_8BIT 0x0080
#define CS03MSK_8BIT 0x0200
#define CS04MSK_8BIT 0x0800
#define CS05MSK_8BIT 0x2000

#define CS06MSK_8BIT 0x0002
#define CS07MSK_8BIT 0x0008
#define CS08MSK_8BIT 0x0020
#define CS09MSK_8BIT 0x0080
#define CS10MSK_8BIT 0x0200

#define CSBARBT (Y | 0x00ffa48) /* chip-select base boot      */
#define CSBAR0  (Y | 0x00ffa4c) /* chip-select base address 0 */
#define CSBAR1  (Y | 0x00ffa50) /* chip-select base address 1 */
#define CSBAR2  (Y | 0x00ffa54) /* chip-select base address 2 */
#define CSBAR3  (Y | 0x00ffa58) /* chip-select base address 3 */
#define CSBAR4  (Y | 0x00ffa5c) /* chip-select base address 4 */
#define CSBAR5  (Y | 0x00ffa60) /* chip-select base address 5 */
#define CSBAR6  (Y | 0x00ffa64) /* chip-select base address 6 */
#define CSBAR7  (Y | 0x00ffa68) /* chip-select base address 7 */
#define CSBAR8  (Y | 0x00ffa6c) /* chip-select base address 8 */
#define CSBAR9  (Y | 0x00ffa70) /* chip-select base address 9 */
#define CSBAR10 (Y | 0x00ffa74) /* chip-select base address 10*/
#define CSBAR_MSK 0xfff8   /* separate address from block size in */



#define RAM_2K    0x00
#define RAM_8K    0x01
#define RAM_16K    0x02
#define RAM_64K    0x03
#define RAM_128K    0x04
#define RAM_256K    0x05
#define RAM_512K    0x06
#define RAM_1M    0x07

#define CSBAR_MSK 0xfff8  /* what is this??? */

				/* QSPI Definitions */
#define  QPDR  (Y | 0x00FFC15)
#define  QPAR  (Y | 0x00FFC16)   /* Host Service Request Registers */
#define  QDDR  (Y | 0x00FFC17)
#define  SPCR0 (Y | 0x00FFC18)   /* Channel Function Select Registers */
#define  SPCR1 ((volatile unsigned short *) (Y | 0x00FFC1A))
#define  SPCR2 (Y | 0x00FFC1C)
#define  SPCR3 (Y | 0x00FFC1E)
#define  SPSR  (Y | 0x00FFC1F)   

#define  RECRAM ((unsigned short*) (Y | 0x00FFD00))
#define  TXDRAM ((unsigned short*) (Y | 0x00FFD20))   
#define  CMDRAM ((unsigned short*) (Y | 0x00FFD40))  


				/* Timers for clock speed*/
#define SET_16_MHZ 0x7c00    /* see page 4-26 MC68332 User's Manual */

#define BAUD_9600  52        /* value for SCBR when 15.991 MHz clock used */
#define BAUD_19200 26
#define BAUD_9600  52        /* value for SCBR when 15.991 MHz clock used */
#define BAUD_19200 26
