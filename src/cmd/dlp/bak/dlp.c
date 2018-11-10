#include <stdio.h>
#define NUM_PER_SKIP 2

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
  for(num = 0; fgets(buf, 1000, in) != 0; num = (num+1)%NUM_PER_SKIP)
    {
      fputs(buf, out);
      fputs("\n", out);
      printf("%s\n", buf);
      if(!num)
	sleep(1);
    }
  
}
