#include <stdio.h>
#include <sys/types.h>
#include <sys/time.h>

#define NUM_PER_SKIP 2


send_buf(buf, fp)

     char *buf;
     FILE *fp;

{
  int width;
  fd_set fds;
  struct timeval timeout;
  int c;

  timeout.tv_sec = 0;
  timeout.tv_usec = 0;
  width = getdtablesize();
  
  for(;*buf != '\0'; ++buf)
    {
      putc(*buf, fp);
      FD_ZERO(&fds);
      FD_SET(fp->_file, &fds);
      if(select(width, &fds, NULL, NULL, &timeout) > 0)
	{
	  c = fgetc(fp);
	  printf("Return : %d\n", c);
	}
    }
}


main(argc, argv)
     int argc;
     char **argv;

{
  FILE *in;
  FILE *out;
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
    outname = "/dev/ttyb";
  if((out = fopen(outname, "wr")) == NULL)
    {
      perror("fopen for dev");
      exit(0);
    }
  printf("files : %d %d\n", in->_file, out->_file);
  for(num = 0; fgets(buf, 1000, in) != 0; num = (num+1)%NUM_PER_SKIP)
    {
      send_buf(buf, out);
      printf("%s\n", buf);
/*      if(!num)
	sleep(1); */
    }
  
}
