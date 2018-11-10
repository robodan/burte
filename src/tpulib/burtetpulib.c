/*
 *   68332 TPU Support Library
 *   Authors:  Dan Spitzley and Parag Batavia
 *   Version 1.0  -  Consolidated initilization and support functions for
 *                   DIO, ITC, PWM, SPWM, and PPWA. - 1/27/93
 *
 */





#include <stdlib.h>
#include <stdio.h>
#include "burte.h"
#include "68332.h"
#include <btpulib.h>


/**********************************************
 *
 *  TPU Initialization Functions
 *
 **********************************************/


tpu_dio(channel, priority, TBS, PAC, host_sequence, int_status)
     int channel, priority, TBS, PAC, host_sequence, int_status;
{
  unsigned int chan_cntrl,temp;
  chan_cntrl = TBS+PAC+0x3;
  outp(PORT_BASE+(channel<<4), chan_cntrl);

  /* Channel Function Select Register Init */
   if ((channel >= 0) && (channel <= 3)) {
    temp = super_inp(CFSR3);
    temp &= ~((unsigned short)(0xf<<(channel*4)));
    temp |= 0x8<<(channel*4);
    super_outp(CFSR3, temp);
  }
  else if ((channel >=4) && (channel <= 7)) {
    temp = super_inp(CFSR2);
    temp &= ~((unsigned short)(0xf<<(channel-4)*4));
    temp |= 0x8<<((channel-4)*4);
    super_outp(CFSR2, temp);
  }
  else if ((channel >= 8) && (channel <= 11)){
    temp = super_inp(CFSR1);
    temp &= ~((unsigned short)(0xf<<(channel-8)*4));
    temp |= 0x8<<((channel-8)*4);
    super_outp(CFSR1, temp);
  }
  else if ((channel >=12) && (channel <= 15)){
    temp = super_inp(CFSR0);
    temp &= ~((unsigned short)(0xf<<(channel-12)*4));
    temp |= 0x8<<((channel-12)*4);
    super_outp(CFSR0, temp);
  }
  else
    return NULL;
  
  /* Set up Channel Priority Register */
  if ((channel>=8) && (channel <= 15)){
    temp = super_inp(CPR0);
    temp |= priority<<((channel-8)*2);
    super_outp(CPR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=super_inp(CPR1);
    temp |= priority<<(channel*2);
    super_outp(CPR1, temp);
  }
  else 
    return NULL;

  /* Set up Host Sequence Register */
  if ((channel>=8) && (channel <= 15)){
    temp=inp(HSQR0);
    temp |= host_sequence<<((channel-8)*2);
    outp(HSQR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=inp(HSQR1);
    temp |= host_sequence<<(channel)*2;
    outp(HSQR1, temp);
  }

  /* Set up Channel Interrupt Enable Register */
  if ((channel >=0) && (channel <=15)) {
    temp = super_inp(CIER);
    temp |= int_status<<(channel);
    super_outp(CIER, temp);
  }

  /* Set up Host Request to initialize */
  if ((channel>=8) && (channel <= 15)){
    temp= inp(HSRR0);
    temp |= 0x03<<((channel-8)*2);
    outp(HSRR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=inp(HSRR1);
    temp |= 0x03<<(channel*2);
    outp(HSRR1, temp);
  }
  else 
    return NULL;

    return (1);
}


tpu_pwm(channel, priority, TBS, PSC, int_status)
int channel, priority, TBS, PSC, int_status;
{
  unsigned int chan_cntrl, temp;

  chan_cntrl = TBS+0x10+PSC;
  outp(PORT_BASE+(channel<<4), chan_cntrl);

  /* Channel Function Select Register Init */
   if ((channel >= 0) && (channel <= 3)) {
    temp = super_inp(CFSR3);
    temp &= ~((unsigned short)(0xf<<channel*4));
    temp |= 0x9<<(channel*4);
    super_outp(CFSR3, temp);
  }
  else if ((channel >=4) && (channel <= 7)) {
    temp = super_inp(CFSR2);
    temp &= ~((unsigned short)(0xf<<(channel-4)*4));
    temp |= 0x9<<((channel-4)*4);
    super_outp(CFSR2, temp);
  }
  else if ((channel >= 8) && (channel <= 11)){
    temp = super_inp(CFSR1);
    temp &= ~((unsigned short)(0xf<<(channel-8)*4));
    temp |= 0x9<<((channel-8)*4);
    super_outp(CFSR1, temp);
  }
  else if ((channel >=12) && (channel <= 15)){
    temp = super_inp(CFSR0);
    temp &= ~((unsigned short)(0xf<<(channel-12)*4));
    temp |= 0x9<<((channel-12)*4);
    super_outp(CFSR0, temp);
  }
  else
    return NULL;

  /* Set up Channel Priority Register */
  if ((channel>=8) && (channel <= 15)){
    temp = super_inp(CPR0);
    temp |= priority<<((channel-8)*2);
    super_outp(CPR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=super_inp(CPR1);
    temp |= priority<<(channel*2);
    super_outp(CPR1, temp);
  }
  else 
    return NULL;

  /* Set up Channel Interrupt Enable Register */
  if ((channel >=0) && (channel <=15)) {
    temp = super_inp(CIER);
    temp |= int_status<<(channel);
    super_outp(CIER, temp);
  }


  /* Set up Host Request to initialize */
  if ((channel>=8) && (channel <= 15)){
    temp= inp(HSRR0);
    temp |= 0x02<<((channel-8)*2);
    outp(HSRR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=inp(HSRR1);
    temp |= 0x02<<(channel*2);
    outp(HSRR1, temp);
  }
  else 
    return NULL;


  /* Set up Host Request to initialize */
/*  if ((channel>=8) && (channel <= 15))
    outp(HSRR0, 0x02<<((channel-8)*2));
  else if ((channel >=0) && (channel <= 7))
    outp(HSRR1, 0x02<<(channel*2));
  else 
    return NULL; */

  return (1);
}


tpu_itc(channel, priority, TBS, PAC, host_sequence, int_status)
int channel, priority, TBS, PAC, host_sequence, int_status;
{
  unsigned int chan_cntrl, temp;
  
  chan_cntrl = TBS+PAC+3;

  outp(PORT_BASE+(channel<<4), chan_cntrl);

  /* Channel Function Select Register Init */
   if ((channel >= 0) && (channel <= 3)) {
    temp = super_inp(CFSR3);
    temp &= ~((unsigned short)(0xf<<(channel*4)));
    temp |= 0xa<<(channel*4);
    super_outp(CFSR3, temp);
  }
  else if ((channel >=4) && (channel <= 7)) {
    temp = super_inp(CFSR2);
    temp &= ~((unsigned short)(0xf<<(channel-4)*4));
    temp |= 0xa<<((channel-4)*4);
    super_outp(CFSR2, temp);
  }
  else if ((channel >= 8) && (channel <= 11)){
    temp = super_inp(CFSR1);
    temp &= ~((unsigned short)(0xf<<(channel-8)*4));
    temp |= 0xa<<((channel-8)*4);
    super_outp(CFSR1, temp);
  }
  else if ((channel >=12) && (channel <= 15)){
    temp = super_inp(CFSR0);
    temp &= ~((unsigned short)(0xf<<(channel-12)*4));
    temp |= 0xa<<((channel-12)*4);
    super_outp(CFSR0, temp);
  }
  else
    return NULL;

  /* Set up Channel Priority Register */
  if ((channel>=8) && (channel <= 15)){
    temp = super_inp(CPR0);
    temp |= priority<<((channel-8)*2);
    super_outp(CPR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=super_inp(CPR1);
    temp |= priority<<(channel*2);
    super_outp(CPR1, temp);
  }
  else 
    return NULL;

  /* Set up Host Sequence Register */
  if ((channel>=8) && (channel <= 15)){
    temp=inp(HSQR0);
    temp |= host_sequence<<((channel-8)*2);
    outp(HSQR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=inp(HSQR1);
    temp |= host_sequence<<(channel)*2;
    outp(HSQR1, temp);
  }
  else 
    return NULL;

  /* Set up Channel Interrupt Enable Register */
  if ((channel >=0) && (channel <=15)) {
    temp = super_inp(CIER);
    temp |= int_status<<(channel);
    super_outp(CIER, temp);
  }

  /* Set up Host Request to initialize */
  if ((channel>=8) && (channel <= 15))
    outp(HSRR0, 0x01<<((channel-8)*2));
  else if ((channel >=0) && (channel <= 7))
    outp(HSRR1, 0x01<<(channel*2));
  else 
    return NULL;

  return (1);
}


tpu_ppwa(channel, priority, TBS, PAC, host_sequence, int_status)
int channel, priority, TBS, PAC, host_sequence, int_status;
{
  unsigned int chan_cntrl, temp;

  chan_cntrl = TBS+PAC+3;

  outp(PORT_BASE+(channel<<4), chan_cntrl);
  
  /* Channel Function Select Register Init */
   if ((channel >= 0) && (channel <= 3)) {
    temp = super_inp(CFSR3);
    temp &= ~((unsigned short)(0xf<<channel*4));
    temp |= 0xf<<(channel*4);
    super_outp(CFSR3, temp);
  }
  else if ((channel >=4) && (channel <= 7)) {
    temp = super_inp(CFSR2);
    temp &= ~((unsigned short)(0xf<<(channel-4)*4));
    temp |= 0xf<<((channel-4)*4);
    super_outp(CFSR2, temp);
  }
  else if ((channel >= 8) && (channel <= 11)){
    temp = super_inp(CFSR1);
    temp &= ~((unsigned short)(0xf<<(channel-8)*4));
    temp |= 0xf<<((channel-8)*4);
    super_outp(CFSR1, temp);
  }
  else if ((channel >=12) && (channel <= 15)){
    temp = super_inp(CFSR0);
    temp &= ~((unsigned short)(0xf<<(channel-12)*4));
    temp |= 0xf<<((channel-12)*4);
    super_outp(CFSR0, temp);
  }
  else
    return NULL;

  /* Set up Channel Priority Register */
  if ((channel>=8) && (channel <= 15)){
    temp = super_inp(CPR0);
    temp |= priority<<((channel-8)*2);
    super_outp(CPR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=super_inp(CPR1);
    temp |= priority<<(channel*2);
    super_outp(CPR1, temp);
  }
  else 
    return NULL;

  /* Set up Host Sequence Register */
  if ((channel>=8) && (channel <= 15)){
    temp=inp(HSQR0);
    temp |= host_sequence<<((channel-8)*2);
    outp(HSQR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=inp(HSQR1);
    temp |= host_sequence<<(channel)*2;
    outp(HSQR1, temp);
  }
  else 
    return NULL;

  /* Set up Channel Interrupt Enable Register */
  if ((channel >=0) && (channel <=15)) {
    temp = super_inp(CIER);
    temp |= int_status<<(channel);
    super_outp(CIER, temp);
  }

  /* Set up Host Request to initialize */
  if ((channel>=8) && (channel <= 15))
    outp(HSRR0, 0x02<<((channel-8)*2));
  else if ((channel >=0) && (channel <= 7))
    outp(HSRR1, 0x02<<(channel*2));
  else 
    return NULL;

  return (1);
}
 

tpu_spwm(channel, priority, TBS, PSC, host_sequence, int_status)
int channel, priority, TBS, PSC, host_sequence, int_status;
{
  unsigned int chan_cntrl, temp;

  chan_cntrl = TBS+16+PSC;

  outp(PORT_BASE+(channel<<4),chan_cntrl);

  /* Channel Function Select Register Init */
   if ((channel >= 0) && (channel <= 3)) {
    temp = super_inp(CFSR3);
    temp &= ~((unsigned short)(0xf<<channel*4));
    temp |= 0x7<<(channel*4);
    super_outp(CFSR3, temp);
  }
  else if ((channel >=4) && (channel <= 7)) {
    temp = super_inp(CFSR2);
    temp &= ~((unsigned short)(0xf<<(channel-4)*4));
    temp |= 0x7<<((channel-4)*4);
    super_outp(CFSR2, temp);
  }
  else if ((channel >= 8) && (channel <= 11)){
    temp = super_inp(CFSR1);
    temp &= ~((unsigned short)(0xf<<(channel-8)*4));
    temp |= 0x7<<((channel-8)*4);
    super_outp(CFSR1, temp);
  }
  else if ((channel >=12) && (channel <= 15)){
    temp = super_inp(CFSR0);
    temp &= ~((unsigned short)(0xf<<(channel-12)*4));
    temp |= 0x7<<((channel-12)*4);
    super_outp(CFSR0, temp);
  }
  else
    return NULL;

  /* Set up Channel Priority Register */
  if ((channel>=8) && (channel <= 15)){
    temp = super_inp(CPR0);
    temp |= priority<<((channel-8)*2);
    super_outp(CPR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=super_inp(CPR1);
    temp |= priority<<(channel*2);
    super_outp(CPR1, temp);
  }
  else 
    return NULL;

  /* Set up Host Sequence Register */
  if ((channel>=8) && (channel <= 15)){
    temp=inp(HSQR0);
    temp |= host_sequence<<((channel-8)*2);
    outp(HSQR0, temp);
  }
  else if ((channel >=0) && (channel <= 7)){
    temp=inp(HSQR1);
    temp |= host_sequence<<(channel)*2;
    outp(HSQR1, temp);
  }
  else 
    return NULL;

  /* Set up Channel Interrupt Enable Register */
  if ((channel >=0) && (channel <=15)) {
    temp = super_inp(CIER);
    temp |= int_status<<(channel);
    super_outp(CIER, temp);
  }

  /* Set up Host Request to initialize */
  if ((channel>=8) && (channel <= 15))
    outp(HSRR0, 0x02<<((channel-8)*2));
  else if ((channel >=0) && (channel <= 7))
    outp(HSRR1, 0x02<<(channel*2));
  else 
    return NULL;

  return (1);
}



/***************************************
 *
 *    DIO Support Functions
 *
 ***************************************/

void DIO_set_match_rate(channel, rate)
     int channel;
     int rate;
{
  outp(PORT_BASE + (channel<<4) + 4, (short) rate);
}

short DIO_read_channel(channel)
     int channel;
{
  unsigned short x, y;
  
  x = inp(PORT_BASE + (channel<<4) + 2);
  y = x >> 15;

  return((short)y);

}

void DIO_force_high(channel)
     int channel;
{
  if (channel > 7) 
    outp(HSRR0, 0x1<<((channel-8)*2));
  else 
    outp(HSRR1, 0x1<<(channel*2));
}

void DIO_force_low(channel)
     int channel;
{
  if (channel > 7) 
    outp(HSRR0, 0x2<<((channel-8)*2)); 
  else 
    outp(HSRR1, 0x2<<(channel*2));
} 

void DIO_read_req(channel)
     int channel;
{
  if (channel > 7) 
    outp(HSRR0, 0x3<<((channel-8)*2)); 
  else 
    outp(HSRR1, 0x3<<(channel*2));
}


/***************************************
 *
 *    ITC Support Functions
 *
 ***************************************/
void ITC_set_max_cnt(channel, maxcnt)
     int channel;
     int maxcnt;
{
  outp(PORT_BASE + 4 + (channel<<4), maxcnt);
}  


/***************************************
 *
 *    PWM Support Functions
 *
 ***************************************/

void PWM_update_channel(channel,pwmhi)
     int channel;
     short pwmhi;
{
  outp(PORT_BASE + 4 + (channel<<4),pwmhi);	/* Set PWMHI for channel */
  if (channel > 7)
    {
      outp(HSRR0, 0x01<<(channel*2));	/* Initiate HSR */
    }
  else
    outp(HSRR1, 0x01<<((channel-8)*2));
}


void PWM_update_pwmper(channel,pwmper)
     int channel;
     int pwmper;
{
  outp(PORT_BASE + (channel<<4) + 6, pwmper);
  if (channel > 7)
    {
      outp(HSRR0, 0x01<<(channel*2));	/* Initiate HSR */
    }
  else
    outp(HSRR1, 0x01<<((channel-8)*2));
}
 


/***************************************
 *
 *    SPWM Support Functions
 *
 ***************************************/


void SPWM_set_hightime(channel, high)
     int channel;
     short high;
{
  outp(PORT_BASE + 0x4 + (channel<<4), high);	
}

void SPWM_set_period(channel, high)
     int channel;
     short high;
{
  outp(PORT_BASE + 0x6 + (channel<<4), high);	
}

void SPWM_set_ref_parms(channel, addr1, addr2)
     int channel;
     short addr1;
     short addr2;
{
  outp(PORT_BASE + 0x8 + (channel<<4), (short) (addr1<<8 | addr2));	
}

void SPWM_set_delay(channel, delay)
     int channel;
     short delay;
{
  outp(PORT_BASE + 0xa + (channel<<4), delay);	
}




/*****************************************
 * 
 *     PPWA Support Functions
 *
 *****************************************/

void PPWA_set_accum_rate(channel, value)
     int channel;
     int value;
{
  outp(PORT_BASE + (channel<<4) + 8, (((char) value) << 8));
}


void PPWA_set_max_cnt(channel, cnt)
     int channel;
     int cnt;
{
  outp(PORT_BASE + (channel<<4) + 2, (((char) cnt) << 8));
}

unsigned PPWA_get_pulse(channel)
     int channel;
{
  return(inp(PORT_BASE + (channel<<4) +0xA));
}




/****************************************
 *
 *     332 General I/O Functions 
 *
 ****************************************/

/* outp(address,value)
     long address;
     short value;
{
   short *a;
   a = (short *) address;
   *a = value;
}


*/
