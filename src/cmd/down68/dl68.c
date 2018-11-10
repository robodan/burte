/*----------------------------------------------------------------------------
 *
 * NAME
 *	down68  - .o -> .dl, object to S record converter.
 *
 * USAGE
 *	down68 [-m] [-o <file.dl>] [-T <addr>] <file.b>
 *
 * PROCEDURE
 *	* Check the argument count and print a usage message if necessary.
 *	* Set the default parameters and parse the command line arguments.
 *		- The -m option causes the program to produce S1 rather than
 *		  S2 records for data transmission, and default headers are
 *		  used.
 *		- The -o option sends the output to a file rather than to
 *		  the standard output.
 *		- Anything else is assumed to represent the input file name.
 *	* Open the input and output files. Exit if unsuccessful.
 *	* Use the info in a.out.h to get the header from the input file.
 *	* Check the magic number in the header and bomb if it's not right.
 *	* Use the execution address as the base loading address.
 *	* Convert the file from binary to hexadecimal ascii.
 *		- The header record: S0 and the name of the file in ascii.
 *		- The text segment: S1 or S2 records.
 *		- The data segment: S1 or S2 records.
 *		- The trailer record: S8 and the execution address or S9.
 * 
 * HISTORY
 * 7-10-87 Dan Chritian (dac) at Carnegie-Mellon University
 *    Modified from down68.c for Sun a.out files and threw away all the
 *    old history.
 *    Starting address option -T has been removed.  Specify this to the linker.
 *
 * BUGS
 *	Always uses zero (0) as the first address of an S1 record.
 *
 *      The start point and entry point are the same.
 *
 *----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <a.out.h>

#define STARTADDR 1000	/* Default starting address. */
#define RCDSIZE 32	/* Record size: 32 bytes -> 64 characters. */

enum format
{
    macsbug,	/* 16 bit format: S1 records used for data. */
    versabug	/* 24 bit format: S2 records used for data. */
  };


main (argc, argv, envp)
  int argc;
  char *argv[], *envp[];
{
    int	i;
    int	Taddr,		/* Starting/execution address (text). */
    Daddr,				/* Data address. */
    out_option;			/* Flag for -o option. */
    char	filename[80],			/* Input file name. */
    dlfile[80];			/* Output file name. */
    enum	format	dl_format;		/* Output format. */
    struct	exec	filhdr;	/* header structure */
    FILE	*bfp,				/* Pointer to a.out file. */
    *dfp;				/* Pointer to .dl file. */
    
    char	*Usage = "[-m] [-o <file.dl>] <file>";
    
    /* Check usage. */
    
    if (argc == 1)
      {
	  fprintf(stderr, "Usage: %s %s\n", argv[0], Usage);
	  exit (1);
      }
    
    /* Parse the command line. */
    
    dl_format = versabug;			/* Set default format. */
    out_option = 0;				/* Set default output. */
    
    for (i = 1 ; i < argc ; i++)
      if (argv[i][0] == '-')		/* A switch. */
	switch(argv[i][1])
	  {
	    case 'm':		/* Set macsbug format. */
	      dl_format = macsbug;
	      break;
	      
	    case 'o':		/* Output to a file. */
	      sprintf(dlfile, argv[++i]);
	      out_option = 1;
	      break;
	      
	    default:		/* Unknown switch. */
	      fprintf(stderr,
		      "%s: Unknown switch: %s\n",
		      argv[0],
		      argv[i]
		      );
	      exit(2);
	      break;
	  }
      else				/* Not a switch. */
	sprintf(filename, "%s", argv[i]);
    
    /*  Read and process file */
    if ( (bfp = fopen (filename, "r")) == NULL ) { /* Open object file. */
	fprintf(stderr,
		"%s: Can't open input file %s\n",
		argv[0], filename);
	exit (3);
    }
    
    if (out_option) {	/* Open the output file. */
	if ( (dfp = fopen (dlfile, "w")) == NULL )
	  {
	      fprintf(stderr,
		      "%s: Can't open output file %s\n",
		      argv[0], dlfile);
	      exit (4);
	  }
    }
    else					/* Output to stdout. */
      {
	  dfp = stdout;
	  sprintf(dlfile, "<standard output>");
      }
    
    /* Get the header information. */
    
    if (fread (&filhdr, sizeof(struct exec), 1, bfp) != 1) {
	fprintf(stderr, "%s: Could not read input file header %s\n",
		argv[0], filename );
	exit (5);
    }
    
    /* Check  the magic number. */
    if (filhdr.a_magic != OMAGIC) {
	fprintf(stderr,
		"%s: Bad or invalid magic number in input file %s %d\n",
		argv[0], filename, filhdr.a_magic );
	fprintf (stderr,
		 "Programs must be linked with option -N.\n");
	exit (6);
    }
    
    Taddr = filhdr.a_entry;	/* Record the base loading address. */
    
    /* Output the records. */
    put_header(dfp, dl_format, filename);		/* Header record. */
    outbin (bfp,dfp,Taddr,filhdr.a_text,dl_format);	/* Text segment. */
    /***	fseek(bfp, N_TXTOFF(filhdr) + filhdr.a_text, 0); /* Seek to data. */
    /*** should already be at the data ***/
    outbin (bfp,dfp, Taddr + filhdr.a_text,
	    filhdr.a_data, dl_format); /* Data segment. */
    put_trailer(dfp, dl_format, Taddr);		/* Trailer record. */
    
    exit (0);
}

/* Procedure that puts out records for a particular segment. */

outbin(bfp, dfp, addr, size, dl_format)
  FILE *bfp, *dfp;
  int addr, size;
  enum format dl_format;
{
    register int i;
    int	count;		/* counts total number of bytes processed */
    int	Dcount;		/* number of bytes in current record */
    int 	checksum;	/* checksum each record */
    int	lswitch;	/* set when address exceeds 24 bits */
    char	buffer[RCDSIZE];/* buffer for data */
    
    for (count = 0; count < size; count += RCDSIZE)
      {
	  Dcount = ( (size-count) < RCDSIZE) ? (size-count) : RCDSIZE;
	  if (fread(buffer, Dcount, 1, bfp) != 1)
	    {
		fprintf(stderr, "Read error.\n");
		exit(9);
	    }
	  
	  switch (dl_format)
	    {
	      case macsbug:		/* Write S1 records. */
		fprintf (dfp, "S1");
		puthex (dfp, (char) Dcount+3);
		puthex (dfp, (char) (addr>>8));
		puthex (dfp, (char) addr);
		checksum = (char) Dcount + 3 + (char) addr +
		  (char) (addr >> 8);
		break;
		
	      case versabug: /* write S2 or S3 records */
		lswitch = ((unsigned) addr) > 0xFFFFFF;
		if (lswitch) {
		    fprintf (dfp, "S3");
		    puthex (dfp, (char) Dcount+5);
		    puthex (dfp, (char) (addr>>24));
		}
		else {
		    fprintf (dfp, "S2");
		    puthex (dfp, (char) Dcount+4);
		}

		puthex (dfp, (char) (addr>>16));
		puthex (dfp, (char) (addr>>8));
		puthex (dfp, (char) addr);
		checksum = (char) Dcount + 4 + (char) addr +
		  (char)(addr >> 8) + (char)(addr >> 16);
		if (lswitch)
		  checksum += (char) (addr >> 24) + 1;
	    }
	  
	  for (i = 0; i < Dcount; i++)
	    {
		puthex (dfp, buffer[i]);
		checksum += buffer[i];
	    }
	  
	  puthex (dfp, ~checksum);
	  fputc ('\n', dfp);
	  addr += Dcount;
      }
}

/* Print an S0 header to start the download file. */

put_header(fp, dl_format, filename)
  FILE *fp;
  enum format dl_format;
  char *filename;
{
    int	count, checksum;
    char	*p;
    char	*DefaultHeader = "S00600004844521B\n";
    
    switch (dl_format)
      {
	case macsbug:
	  fprintf(fp, DefaultHeader);
	  break;
	  
	case versabug:
	  fprintf(fp, "S0");
	  count = strlen (filename) + 3;
	  checksum = count;
	  puthex (fp, (char) count);
	  fprintf(fp, "0000");
	  for (p = filename ; *p ; p++)
	    {
		puthex (fp, (char) *p);
		checksum += *p;
	    }
	  puthex (fp, (char) ~checksum);
	  fputc ('\n', fp);
	  break;
      }
}

/* Print an S8 or S9 record to end the download file. */

put_trailer(fp, dl_format, address)
  FILE *fp;
  enum format dl_format;
  unsigned int address;
{
    int	checksum;
    char	*DefaultTrailer = "S904000000FC\n";
    
    switch (dl_format)
      {
	case macsbug:
	  fprintf(fp, DefaultTrailer);
	  break;
	  
	case versabug:
	  fprintf(fp, "S804");		/* Byte count. */
	  puthex(fp, (char)(address >> 16));	/* Execution addr. */
	  puthex(fp, (char)(address >> 8));
	  puthex(fp, (char) address);
	  checksum = 4 + (char)(address >> 16) +
	    (char)(address >> 8) + (char) address;
	  puthex(fp, ~checksum);
	  fputc('\n', fp);
	  break;
      }
}

#define hex(c) c>9 ? c+0X37 : c+0X30  /* Macro for hex conversion. */
  
  /* Print a byte as two hex chars. */
  
  puthex(fp, b)
FILE *fp;
register char b;
{
    register char c1, c2;
    
    c1 = (b >> 4) & 0XF;
    c2 = b & 0XF;
    c1 = hex (c1);
    c2 = hex (c2);
    fprintf (fp, "%c%c", c1, c2);
}
