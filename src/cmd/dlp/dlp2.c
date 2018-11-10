#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

#define NUM_PER_SKIP 8



send(fd, buf)

     int fd;
     char *buf;
{
  char buf2[1000];

  printf("sending : %s\n", buf);
  write(fd, buf, strlen(buf));
/*  sleep(1);  */
  read(fd, buf2, 1000);
  printf("%s\n", buf2);
  read(fd, buf2, 1000);
  printf("%s\n", buf2);
  while(getchar() !='\n');
}


send_buf(buf, fd)

     char *buf;
     int fd;

{
  int width;
  fd_set fds;
  struct timeval timeout;
  char c;

  write(fd, buf, strlen(buf));
/*
  printf("%d\n", strlen(buf));
*/
/*  c = '\n';
  write(fd, &c, 1); */
/*
  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  width = getdtablesize();
  
  for(;*buf != '\0'; ++buf)
    {
      write(fd, buf, 1);
      FD_ZERO(&fds);
      FD_SET(fd, &fds);
      if(select(width, &fds, NULL, NULL, &timeout) > 0)
	{
	  read(fd, &c, 1);
	  printf("Return : %d %c\n", c, c);
	  while(getchar() != '\n');
	}
    }
    */
}


main(argc, argv)
     int argc;
     char **argv;

{
  FILE *in;
  int out;
  char *outname;
  int num;
  char buf[1000];

  if(argc < 2)
    {
      printf("Usage : dlp <fname> [<output>]\n");
      exit(0);
    }
  if((in = fopen(argv[1], "r")) == NULL)
    {
      printf("Error opening %s\n", argv[1]);
      exit(0);
    }
  if(argc > 2)
    {
      outname = argv[2];
    }
  else
#ifdef TTYB
    outname = "/dev/ttyb";
#else
    outname = "/dev/ttya";
#endif
  if((out = ser_init_connection(outname)) ==  -1)
    {
      perror("open for dev");
      exit(0);
    }
  
     /*  Write out buad rate change.  */
/*
  send(out, "pf 0\n");
  send(out, "4800\n");
  send(out, ".\n");
  send(out, "y\n");
*/
  ser_reconfig(out, 1200);
/*  
  sprintf(buf, "lo\n");
  printf("%s", buf);
  write(out, buf, strlen(buf));
*/
  for(num = 0; fgets(buf, 1000, in) != 0; num = (num+1)%NUM_PER_SKIP)
    {
      send_buf(buf, out);
/*
      printf("%s\n", buf);
      if(!num)
	sleep(1); 
*/
    }
/*
  send(out, "\n\n");
  send(out, "pf 0\n");
  send(out, "9600\n");
  send(out, ".\n");
  send(out, "y\n");
*/
  printf("done\n");
  while(getchar() != '\n');
  ser_reconfig(out, 9600);
  close(out);
  fclose(in);
}
