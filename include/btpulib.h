#define inp(address) (*((volatile unsigned short *) (address)))
#define outp(address, value) ((*((volatile unsigned short *) (address))) = ((unsigned short) (value)))

#define inb(address) (*((volatile unsigned char *)  (address)))
#define outb(address, value) ((*((volatile unsigned char *) (address))) = ((unsigned char) (value)))

#define HIGH 0x03 
#define MEDIUM 0x02
#define LOW 0x01
#define ENABLE 0x01
#define DISABLE 0x00

/* ITC TBS options */
#define ITC_TCR1 0x00
#define ITC_TCR2 0x40

/* ITC PAC options */
#define ITC_NOTRANS 0x00
#define ITC_RISING 0x04
#define ITC_FALLING 0x08
#define ITC_EITHER 0x0C
#define ITC_NOCHANGE 0x10

/* ITC Host Sequence Code options */
#define ITC_NOLINK_SINGLE 0x00
#define ITC_NOLINK_CONT 0x01
#define ITC_LINK_SINGLE 0x02
#define ITC_LINK_CONT 0x03

/* DIO TBS options */
#define DIO_TCR1 0x00
#define DIO_TCR1_TCR2 0x20
#define DIO_TCR2_TCR1 0x40
#define DIO_TCR2 0x60
#define DIO_NOCHANGE_TBS 0x100

/* DIO PAC options */
#define DIO_NOTRANS 0x00
#define DIO_RISING 0x04
#define DIO_FALLING 0x08
#define DIO_EITHER 0x0C
#define DIO_NOCHANGE_PAC 0x10

/* DIO Host Sequence Code options */
#define DIO_TRANSMODE 0x00
#define DIO_MATCHMODE 0x01
#define DIO_RECORD_HSR11 0x02

/* PWM TBS options */
#define PWM_TCR1 0x80
#define PWM_TCR2 0xE0
#define PWM_NOCHANGE_TBS 0x180

/* PWM PSC options */
#define PWM_FORCE_BY_LATCHES 0x00
#define PWM_FORCE_HIGH 0x01
#define PWM_FORCE_LOW 0x02
#define PWM_NOFORCE 0x03

/* PPWA TBS options */
#define PPWA_TCR1 0x00
#define PPWA_TCR1_TCR2 0x20
#define PPWA_TCR2_TCR1 0x40
#define PPWA_TCR2 0x60
#define PPWA_NOCHANGE_TBS 0x100

/* PPWA PAC options */
#define PPWA_RISING 0x04
#define PPWA_FALLING 0x08

/* PPWA Host Sequence Code options */
#define PPWA_24_BIT 0x00
#define PPWA_16_BIT_LINK 0x01
#define PPWA_24_BIT_PW 0x02
#define PPWA_16_BIT_PW_LINK 0x03

/* SPWM TBS options */
#define SPWM_TCR1 0x80
#define SPWM_TCR2 0xE0
#define SPWM_NOCHANGE_TBS 0x180

/* SPWM PSC options */
#define SPWM_FORCE_BY_LATCHES 0x00
#define SPWM_FORCE_HIGH 0x01
#define SPWM_FORCE_LOW 0x02
#define SPWM_NOFORCE 0x03

/* SPWM Host Sequence Code options */
#define SPWM_MODE0 0x00
#define SPWM_MODE1 0x01
#define SPWM_MODE2 0x02
