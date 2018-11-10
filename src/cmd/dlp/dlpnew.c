/*
 *  file : dlpnew.c
 *
 *  Generic program for downloading S-record files to the 332.
 *
 *  Usage : dlp <fname> [<output>] [<baud rate>] [<BURTE_flag>]
 *
 *
 *  Andrew H. Fagg      5/19/93      Original
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

#define NUM_PER_SKIP 8



/*
 * send_buf(buf, fd, wait)
 *
 *  Send a buffer full of data to <fd>.  If <wait> is TRUE, then
 * echo characters from the 332, otherwise print a '.' after
 * buffer is sent.
 *
 */

send_buf(buf, fd, wait)

     char *buf;
     int fd;
     int wait;

{
  int width;
  fd_set fds;
  struct timeval timeout; 
  char c;
  char buf2[1000];
  int num;

  write(fd, buf, strlen(buf));	/* Write data. */
  if(wait)
    {
				/* Check to see if anything has been output */
      timeout.tv_sec = 0;
      timeout.tv_usec = 2;
      width = getdtablesize();
  
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      if(select(width, &fds, NULL, NULL, &timeout) > 0)
	{
				/* Yes: print it. */
	  num = read(fd, buf2, 999);
	  buf2[num] = 0;
	  printf("%s", buf2);
	}
    }
  else
    printf(".");
				/* Flush all output to stdout. */
  fflush(stdout);
}


/*
 * main(argc, argv)
 *
 *  Parse arguments, read data (one line at a time), send it to the
 * output port, then echo back additional chars from the port.
 *
 */

main(argc, argv)
     int argc;
     char **argv;

{
  FILE *in;
  int out;
  char *outname;
  int num;
  char buf[1000];
  int baud;
  int wait;
  int width;
  fd_set fds;
  struct timeval timeout;

				/* Check number of args. */
  if(argc < 2 || argc > 5)
    {
      printf("Usage : dlp <fname> [<output>] [<baud rate>] [<BURTE_flag>]\n");
      exit(0);
    }
				/* Open input file. */
  
  if((in = fopen(argv[1], "r")) == NULL)
    {
      printf("Error opening %s\n", argv[1]);
      exit(0);
    }
				/* Set output port. */
  if(argc > 2)
    {
      outname = argv[2];
    }
  else
    outname = "/dev/ttya";
				/* Set baud rate. */
  if(argc > 3)
    {
      sscanf(argv[3], "%d", &baud);
    }
  else
    baud = 9600;
				/* Set BURTE flag. */
  if(argc > 4)
    {
      sscanf(argv[4], "%d", &wait);
    }
  else
    wait = 0;

				/* Open output port.  */
  if((out = ser_init_connection(outname)) ==  -1)
    {
      perror("open for dev");
      printf("%s\n", outname);
      exit(0);
    }
  
				/*  Write out baud rate change.  */

  ser_reconfig(out, baud);
				/* Read data. */
  for(num = 0; fgets(buf, 1000, in) != 0; num = (num+1)%NUM_PER_SKIP)
    {
				/* Send data out. */
      send_buf(buf, out, wait);
    }
				/* If in BURTE mode, wait for additional. */
				/*   characters to come back. */
  if(wait)
    {
      do
	{
	  timeout.tv_sec = 1;
	  timeout.tv_usec = 0;
	  width = getdtablesize();
      
	  FD_ZERO(&fds);
	  FD_SET(out, &fds);
	  if(select(width, &fds, NULL, NULL, &timeout) > 0)
	    {
				/* Characters to be read- read them. */
	      num = read(out, buf, 999);
	      buf[num] = 0;
	      printf("%s", buf);
	    }
	  else
	    num = 0;
	}
				/* Do this until there are no more chars. */
      while(num);
    }
				/* Reconfigure output port.  */
  ser_reconfig(out, 9600);
  close(out);			/* Close everything down. */
  fclose(in);
  
  printf("\n");
}
