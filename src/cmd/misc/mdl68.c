/*--------------------------------------------------------------------------
 *
 * ABSTRACT
 *	mdl68  - Download multiple files to a 68000 system.
 *
 * USAGE
 *	mdl68 <files>
 *
 * EXPLICIT INPUTS
 *	The filenames on the command line. No .dl extension necessary.
 *
 * IMPLICIT INPUTS
 *	DLPATH variable in the environment.
 *
 * EXPLICIT OUTPUTS
 *	Download files are dumped to the standard output. Diagnostics.
 *
 * IMPLICIT OUTPUTS
 *	Terminal transmission mode is changed during the use of the bk(4)
 *	protocol.
 *
 * PROCEDURE
 *	* Look for the DLPATH variable in the user's environment.
 *	* Search the resultant path (possibly a default) for the file names
 *	  given on the command line, one by one.
 *	* Try to open the file. If unsuccesful, print an S0 record with an
 *	  error message in it. Store an S8 record with a null execution
 *	  address in case none of the openings is successful.
 *	* Download each file (using bk(4)). 
 *	  Print only the last S8 or S9 record.
 *
 * HISTORY
 * 12-Dec-87  Dan Christian (dac) ac CMU
 *	Killed a bug that caused core dumps whenever a bad file was
 *	encountered.  It now exits.  Killed the include code.  It
 *	was never used.
 *
 * 09-Sep-83  Rafael Bracho (rxb) at Carnegie-Mellon University
 *	Modified so it prints the error messages ASCII coded.
 *	(It was about time!)
 *
 * 25-Jun-82  John Schlag (jfs) at Carnegie-Mellon University
 *	Changed to work with the new down68 and the new downloader. All S0
 *	records are forwarded, but only the last S8 or S9.
 *
 * 22-Jun-82  John Schlag (jfs) at Carnegie-Mellon University
 *	Created.
 *
 *----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <sgtty.h>

#define	upper(x)	((x) < 'a' ? (x) : (x) - 'a' + 'A')
  
#define RCD_SIZE	512			/* No particular reason. */
#define END_RECORD	"S804000000FB\n"	/* Dummy ending record. */
  
  char *progname;		/* The name of this program, as invoked. */

main(argcount, arglist, envlist)
  int argcount;
  char *arglist[], *envlist[];
{
    int i, ldisc, fildes;
    char *dlpath, *getenv();
    char last_record[RCD_SIZE];
    
    /* SAVE THE PROGRAM NAME. */
    
    progname = arglist[0];
    
    /* CHECK THE USAGE AND PRINT A MESSAGE IF NECESSARY. */
    
    if (argcount == 1) {
	puterror ("Must specify the files\n");
	printf(END_RECORD);
	exit (-1);
    }
    
    /* LOOK FOR THE 'DLPATH' ENVIRONMENT VARIABLE. */
    
    if ( (dlpath = getenv("DLPATH")) == NULL )
      dlpath = ":/usrthm0/rclub/downld:/usrthm0/dac/burte/downld";
    
    /* ENTER DOWNLOAD MODE. */
    
    ldisc = NETLDISC;
    ioctl(fildes, TIOCSETD, &ldisc);
    
    sprintf (last_record, END_RECORD);
    /* SEND THE FILES. */
    
    for (i = 1 ; i < argcount ; i++)
      if (download(arglist[i], dlpath, last_record) < 0) {
	  printf(last_record);
	  exit (-1);
      }
    printf(last_record);
    
    /* EXIT DOWNLOAD MODE. */
    
    ldisc = NTTYDISC;
    ioctl(fildes, TIOCSETD, &ldisc);
}

/* DOWNLOAD A FILE. */

download(file, dlpath, buffer)
  char *file,			/* Filename, possibly w/o extension. */
    *dlpath,		/* Path to search for the file. */
    *buffer;		/* A place to store the trailer records. */
{
    char	*p,
    filename[80],	/* Filename with guaranteed .dl extension. */
    dlfile[80],	/* Absolute path name of the above file. */
    errbuffer [100],/* For error messages */
    record[RCD_SIZE],/* Record buffer for download information. */
    buf[RCD_SIZE];	/* End record storage for recursive calls. */
    FILE	*dfp,		/* Pointer to the .dl file. */
    *fopenp();	/* Library function. */
    int lastwait = 0;
    
    /* FORCE .dl EXTENSION. */
    
    if (index(file, '.'))
      sprintf(filename, file);
    else
      sprintf(filename, "%s.dl", file);
    
    /* OPEN THE FILE. */
    
    if ( (dfp = fopenp(dlpath, filename, dlfile, "r")) == NULL ) {
	sprintf(errbuffer, "%s: Can't find %s", progname, filename);
	puterror (errbuffer);
	return -1;
    }
    
    /* DUMP IT TO THE TERMINAL LINE. */
    
    while (fgets(record, RCD_SIZE, dfp) != NULL) {
	/* Binary data record. */
	switch (*(record+1)) {
	  case '8':	/* Save trailer records. */
	  case '9':
	    sprintf(buffer, record);
	    break;
	    
	  default:	/* Print unmolested. */
	    if (++lastwait > 32 ) { sleep (2); lastwait = 0;}
	    printf(record);
	    break;
	}
    }
    fclose(dfp);
}

/* Output an error message, ASCII coded */

puterror (message)
  char *message;
{
    char *p;
    char smallbuf [3];
    
    printf ("S0");
    sprintf (smallbuf, "%02x", strlen (message) + 3);
    printf ("%c%c0000", upper (smallbuf[0]), upper (smallbuf[1]));
    for (p = message; *p; p++)
      {
	  sprintf (smallbuf, "%02x", *p);
	  putchar (upper (smallbuf[0]));
	  putchar (upper (smallbuf[1]));
      }
    puts ("");
}
