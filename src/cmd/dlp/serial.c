#include <stdio.h>
#include <fcntl.h>
#include <sys/termio.h>
#include <sys/termios.h>
/*#include <sys/ioctl.h>*/
#include <sys/ttold.h>

ser_init_connection(dev)

char *dev;

{
  int fd;
  char c;
  char buf[10];
  struct termios data;
  struct sgttyb temp;
  int ret;
  
  if((fd = open(dev, O_RDWR)) == -1)
    {
      perror("ser_init_connection.fopen");
      return(-1);
    }
  return(fd);
}


int ser_read_ascii_buf(fd, buf, len)

     int fd;
     char *buf;
     int len;
     
{
  return(read(fd, buf, len));
}


int ser_write_ascii_buf(fd, buf, len)

     int fd;
     char *buf;
     int len;

{
  return(write(fd, buf, len));
}


ctoa(buf, ascii)

     char buf;
     char ascii[2];

{
  unsigned char temp;
  unsigned char buf2;

  buf2 = (unsigned char) buf;
  temp = buf2 & 0xf;
  if(temp < 10)
    ascii[1] = temp + '0';
  else
    ascii[1] = temp - 10 + 'A';
  temp = buf2 >> 4;
  if(temp < 10)
    ascii[0] = temp + '0';
  else
    ascii[0] = temp - 10 + 'A';
}


int ser_write_buf(fd, buf, len)

     int fd;
     char *buf;
     int len;

{
  int i;
  char ascii[2];
  int ret;
  char last = 10;
  
  for(i = 0; i < len; ++i, ++buf)
    {
      ctoa(*buf, ascii);
      if((ret = write(fd, ascii, 2)) != 2)
	return(ret);
    }
  return(write(fd, &last, 1));
}


atoc(buf, ascii)

     char *buf;
     char ascii[2];

{
  if(ascii[0] >= '0' && ascii[0] <= '9')
    *buf = ascii[0] - '0';
  else
    {
      if(ascii[0] >= 'A' && ascii[0] <= 'F')
	*buf = ascii[0] - 'A' + 10;
      else
	{
	  printf("atoc : bad character received : %d\n", ascii[0]);
	  exit(0);
	}
    }
  (*buf) <<= 4;
  if(ascii[1] >= '0' && ascii[1] <= '9')
    *buf |= ascii[1] - '0';
  else
    {
      if(ascii[1] >= 'A' && ascii[1] <= 'F')
	*buf |= ascii[1] - 'A' + 10;
      else
	{
	  printf("atoc : bad character received : %d\n", ascii[1]);
	  exit(0);
	}
    }
}



int ser_read_buf(fd, buf, len)

     int fd;
     char *buf;
     int len;

{
  int i;
  char ascii[2];
  int ret;

  for(i = 0; i < len; ++i, ++buf)
    {
      do
	{
	  if((ret = read(fd, &(ascii[0]), 1)) != 1)
	    return(ret);
	}
      while (ascii[0] == 10);
      do
	{
	  if((ret = read(fd, &(ascii[1]), 1)) != 1)
	    return(ret);
	}
      while (ascii[1] == 10);
      atoc(buf, ascii);
    }
}




ser_reconfig(fd, speed)

     int fd;
     int speed;
{
  int ret;
  struct termios data;
  int i;
  unsigned int output_speed;

  switch (speed)
    {
    case 300 :
      output_speed = B300;
      break;
    case 1200 :
      output_speed = B1200;
      break;
    case 2400 :
      output_speed = B2400;
      break;
    case 4800 :
      output_speed = B4800;
      break;
    case 9600 :
      output_speed = B9600;
      break;
    case 19200 :
      output_speed = B19200;
      break;
    default :
      printf("bogus speed specified.\n");
      exit(0);
    }

  if((ret = ioctl(fd, TCGETS, &data)) == -1)
    {
      perror("ioctl");
      exit(0);
    }
/*  printf("%d\n", ret);

  printf("%o %o %o %o\n", data.c_iflag, data.c_oflag, data.c_cflag & CBAUD, data.c_lflag);
*/
  data.c_cflag &= ~CBAUD;
  data.c_cflag |= output_speed;

  data.c_cflag &= ~CSIZE;
  data.c_cflag |= CS8;
  data.c_cflag &= ~PARENB;
  data.c_cflag |= CSTOPB;

  data.c_lflag = 0;

/*
  data.c_lflag &= ~ICANON;
  data.c_lflag &= ~ISIG;
  data.c_lflag &= ~ECHO;
  data.c_lflag &= ~ECHOCTL;
*/

  data.c_iflag = 0;
  data.c_oflag = 0;
/*  
  if(data.c_cflag & ICANON)
    printf("Canonical mode is set");
*/
  if((ret = ioctl(fd, TCSETS, &data)) == -1)
    {
      perror("ioctl : TCSETS");
      exit(0);
    }
/*
  if(data.c_cflag & ICANON)
    printf("Canonical mode is set");
*/
  if((ret = ioctl(fd, TCGETS, &data)) == -1)
    {
      perror("ioctl");
      exit(0);
    }
/*
  printf("%d\n", ret);

  printf("%o %o %o %o\n", data.c_iflag, data.c_oflag, data.c_cflag & CBAUD, data.c_lflag);
*/
}


/*
main()

{
  int fd;
  int i;
  char buf;
  
  if((fd = ser_init_connection("/dev/ttya")) < 0)
    {
      exit(0);
    }
  while(1)
    {


      ser_read_buf(fd, &i, sizeof(int));
      printf("received : %x\n", i);

      if(scanf("%x", &i) == 1)
	ser_write_buf(fd, &i, sizeof(int));

      if(ser_read_ascii_buf(fd, &buf, 1))
	printf("%c", buf);
    }
}




*/


