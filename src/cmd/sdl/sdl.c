/*----------------------------------------------------------------------------
 *
 * read in a .dl file and split it into hibyte lowbyte
 *
 * rd_dlfile(fp, buffer, wordcount) - Read in a .dl file in Motorola S format.
 *
 * Arguments:
 * fp:		pointer to the .dl file.
 * buffer:	pointer to a returned pointer buffer of
 *                       unsigned short integers for the code.
 * wordcount:	pointer to an integer where we return the wordcount.
 *
 * HISTORY
 * 16-Mar-88  Dan Christian
 *	Added checksum checking and missing address detection.
 *
 * 14-Sept-87 Dan Christian (dac) at Carnegie-Mellon U.
 *      Added dynamic memory allocation and improve error messages.
 *
 * 11-Jun-82  John Schlag (jfs) at Carnegie-Mellon University
 *	Separated this routine from disdl(1) and added interpretation
 *	of S2 records.
 *----------------------------------------------------------------------------
 */

#include <stdio.h>

main (argc, argv)
  int argc;
  char **argv;
{
    short i;
    char *in_name, *lo_name, *hi_name;
    FILE *fin, *fhi, *flo;
    
    in_name = 0;
    lo_name = "lobyte";
    hi_name = "hibyte";
    
    for (i=1; i< argc; i++) {
	if (argv[i][0] != '-') {
	    in_name = argv[i];
	} else {
	    switch (argv[i][1]) {
	      case 'l':
		lo_name = argv[++i];
		break;
		
	      case 'h':
		hi_name = argv[++i];
		break;
		
	      default:
		fprintf (stderr, "Unknow switch given <%s>\n", argv[i]);
	    }
	}
    }
    
    if (in_name == 0){
	fin = stdin;
    } else {
	fin = fopen (in_name, "r");
	if ( ! fin) {
	    fprintf (stderr, "Coulden\'t open input file <%s>\n", in_name);
	    exit (-1);
	}
    }
    fhi = fopen (hi_name, "w");
    if (! fhi) {
	fprintf (stderr, "Coulden\'t open output file <%s>\n", hi_name);
	exit (-1);
    }
    flo = fopen (lo_name, "w");
    if (! flo) {
	fprintf (stderr, "Coulden\'t open output file <%s>\n", lo_name);
	exit (-1);
    }
    sdl (fin, fhi, flo);    
}

sdl(fp, fhi, flo)
  FILE *fp, *fhi, *flo;
{
    unsigned char c, data;
    int i, nbytes, nwords = 0, done = 0, even = 1;
    int totalbytes = 0, checksum;
    unsigned int start_addr = ~0, addr_cnt = 0, addr;
    
    while (!done) {
	addr = 0;
	while (((c = fgetc (fp)) & 0x7F) != 'S'); /* Move to next record. */
	
	c = fgetc(fp);
	nbytes = (unsigned char)byte2(fp);
	switch (c)
	  {
	    case '0':			/* Header record with name. */
	      byte2 (fp);		/* Skip the address. */
	      byte2 (fp);
	      nbytes -= 3;		/* Account. */
	      while (nbytes--)	/* Translate into ascii. */
		putc (byte2 (fp), stdout);
	      putc ('\n', stdout);
	      continue;
	      
	    case '1':
	      addr   = (unsigned char)byte2 (fp);
	      data   = (unsigned char)byte2 (fp);
	      checksum = nbytes + addr + data;
	      
	      addr <<= 8;
	      addr |= data;
	      
	      nbytes -= 3;
	      totalbytes += nbytes;
	      break;
	      
	    case '2':			/* Data record. */
	      addr   = (unsigned char)byte2 (fp);
	      data   = (unsigned char)byte2 (fp);
	      checksum = nbytes + addr + data;
	      
	      addr <<= 8;
	      addr |= data;
	      checksum += (data = (unsigned char)byte2 (fp));
	      addr <<= 8;
	      addr |= data;
	      
	      nbytes -= 4;
	      totalbytes += nbytes;
	      break;
	      
	    case '9':
	      addr = ((unsigned char)byte2 (fp) & 0xFF) << 8;
	      addr |= ((unsigned char)byte2 (fp) & 0xFF);
	      byte2 (fp);	/* Skip checksum. */
	      printf ("\nExecution address: %x  First address %x\n",
		      addr, start_addr);
	      printf ("%d bytes\n", totalbytes);
	      done = 1;
	      continue;
	      
	    case '8':		/* Trailer record. */
	      addr = ((unsigned char)byte2 (fp) & 0xFF) << 16;
	      addr |= ((unsigned char)byte2 (fp) & 0xFF) << 8;
	      addr |= ((unsigned char)byte2 (fp) & 0xFF);
	      byte2 (fp);	/* Skip checksum. */
	      printf ("\nExecution address: %x  First address %x\n",
		      addr, start_addr);
	      printf ("%d bytes\n", totalbytes);
	      done = 1;
	      continue;
	      
	    case -1:
	      printf ("EOF found.  First address %x.  %d bytes\n",
		      start_addr, totalbytes);
	      done = 1;
	      continue;

	    default:		/* error */
	      fprintf(stdout,
		      "Unknown record type: S%c in .dl file.\n", c);
	      continue;
	  }
	
	nwords += nbytes / 2;
	if (start_addr == ~0) {
	    start_addr = addr;
	    addr_cnt = addr;
	} else if (addr_cnt != addr) {
	    fprintf (stdout, "\nAddress is: %x expected %x\n",
		     addr, addr_cnt);
	}
	
	for (i=0; i< nbytes;) { /* move bytes */
	    checksum += (data = (unsigned char)byte2 (fp));
	    addr_cnt++;
	    if (even) {
		putc (data, fhi);
		i++;
		even = 0;
	    } else {
		putc (data, flo);
		i++;
		even = 1;
	    }
	}
	if ((unsigned char)byte2 (fp) == (~checksum & 0xff)) {
	    putc ('.', stdout);
	} else {
	    putc ('?', stdout);
	}
    }
    
    return(nwords);		/* return the starting address */
}
