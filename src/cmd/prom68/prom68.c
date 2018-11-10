/*--------------------------------------------------------------------------
 *
 * TITLE
 *	PROM68 ()- Create a macsbug formatted file and send it to the
 *		standard output. Optionally append an IP address.
 *
 * USAGE
 *	prom68 [-i <IP address>] [-a <address>] {-h,-l} <file>
 *
 * DESCRIPTION
 *	prom68 will split a VERSABUG formatted file (S2-S8) and output
 *	to the standard output either the high or the low bytes, depending
 *	on whether the -h or the -l flag is specified (defaults to -h).
 *
 *	If the -i flag is specified, the defined IP address will be added
 *	as a record starting at the address defined by the -a flag (the
 *	default is 0xFE7FFC).
 *
 * ENVIRONMENT
 *	DLPATH		where to look for the .dl files.
 *
 * HISTORY
 *  3-Oct-83  Rafael Bracho (rxb) at Carnegie-Mellon University
 *	Finally got it! A number of bugs were found, mostly related to
 *	details (i.e., there was no real design problem). The only real
 *	difference between the output of this program and that of sld68
 *	is that the addresses are offset to start at zero. Sld68 didn't
 *	do this and I assume it was working because the prom blaster
 *	didn't care (or because the addresses always had zeroes in the
 *	last four bytes).
 *
 *  2-Oct-83  Rafael Bracho (rxb) at Carnegie-Mellon University
 *	Created so we can go from S2/S8 records to highbyte/lowbyte
 *	output at burn time. Also the -i/-a flags help in burning
 *	special versions for each host.
 *
 *----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <bbnnet/netlib.h>

#define	TRUE	1
#define	FALSE	0

extern char *index ();
extern char *getenv ();
extern FILE *fopenp ();

netaddr IPaddress;		/* to hold the IP address */
int Maddress = 0xFE7FFC;	/* address to put the IP address */
enum Byte {
    highbyte, lowbyte
} byte = highbyte;		/* byte to output */

FILE *dlfile = NULL;		/* file to be converted */
char dlfilename [100];		/* for the absolute pathname */
char *dlpath;			/* to have the DLPATH environment variable */

int putIP = 0;			/* set if the IP address should be added */

char *Usage = "usage: prom68 [-i <IPaddr>] [-a <addr>] [-h] [-l] <file>";

main (argcount, arglist)
    int argcount;
    char *arglist [];
{
    /* CHECK PROPER CALLING SEQUENCE, PRINT USAGE MESSAGE */

    if (argcount == 1) {	/* print usage message if necessary */
	puts (Usage);
	exit (0);
    }

    /* GET DLPATH VARIABLE, GIVE A DEFAULT IF NECESSARY */

    if ( (dlpath = getenv ("DLPATH")) == NULL )
	dlpath = ":/usr/p68/downld";

    /* GET THE FLAGS AND OPEN THE FILE */

    getargs (argcount - 1, &arglist [1]);
    if ( dlfile == NULL )
	quit (1, "prom68: Must specify the file\n");

    /* DO THE WORK OF SPLITTING THE FILE */

    split (dlfile);		/* do the work on the file */

    exit (0);
}

/*
 *	getargs () will get the appropriate arguments.
 */

getargs (argcount, arglist)
    int argcount;
    char *arglist [];
{
    register int i;
    char buffer [100];		/* to hold the filename temporarily */

    for (i = 0; argcount--; i++)
    {
	if ( *arglist [i] == '-' )	/* it is a flag */
	{
	    switch ( *(arglist [i] + 1) )
	    {
		case 'l':
		    byte = lowbyte;
		    break;

		case 'h':
		    byte = highbyte;
		    break;

		case 'i':
		    IPaddress = gethost (arglist [++i]);
		    argcount--;
		    putIP = TRUE;
		    break;

		case 'a':
		    Maddress = atoh (arglist [++i]);
		    argcount--;
		    break;

		default:
		    printf ("prom68: unknown option: %s, ignored\n",
			    arglist [i]);
		    break;
	    }			/* end of flags switch */
	}
	else			/* not a flag, must be a file */
	{
	    if ( dlfile )
		printf ("prom68: Another file encountered, %s ignored\n",
			arglist [i]);
	    else
	    {
		char *dot = index (arglist [i], '.');
		if ( dot && (dot != arglist [i]) )
		    sprintf (buffer, arglist [i]);
		else
		    sprintf (buffer, "%s.dl", arglist [i]);
		if ( (dlfile = fopenp (dlpath, buffer, dlfilename, "r"))
		      == NULL )
		    quit (1, "prom68: Can't open file %s\n", dlfilename);
	    }
	}
    }				/* end of 'for' loop */
}

/*
 *	split () will take apart the .dl file and output one half.
 */

split (fp)
    register FILE *fp;
{
    register int i;		/* general purpose */
    char *p;

    long address;		/* address of the current record */
    long firstaddress;		/* used as offset for all records */
    int nbytes;			/* number of bytes in current record */
    int checksum;		/* where to compute the checksum */
    int firstime = TRUE;	/* to load firstaddress only once */
    char line [100];		/* to get a line from .dl file */

    char *DefaultHeader = "S00600004844521B\n";	/* file = tst (?) */
    char *DefaultTrailer = "S904000000FC\n";	/* too many zeroes? */

    unsigned hexin ();		/* a static, see below */

    if ( fgets (line, 100, fp) == NULL )
	quit (1, "prom68: Premature end of file %s\n", dlfilename);
    else if ( line [0] != 'S' || line [1] != '0' )
	quit (1, "prom68: File %s is not a download file\n", dlfilename);

    printf (DefaultHeader);	/* print a header */

    while ( (p = fgets (line, 100, fp)) != NULL )
    {
	if (*p++ != 'S')
	    quit (1, "prom68: No 'S' record in file %s\n", dlfilename);
	else
	{
	    switch (*p++)
	    {
		case '0':	/* ignore imbedded S0 records */
		    break;

		case '8':	/* end of .dl file */
		    if (putIP)
		    {
			register unsigned char *up;
			int cksum;
			long lastaddr;

			printf ("S105");

			lastaddr = (Maddress - firstaddress) >> 1;
			cksum = ((lastaddr & 0xFF00) >> 8) +
				(lastaddr & 0xFF) + 5;
			puthex (lastaddr, 4);

			up = (unsigned char *) &IPaddress;
			if (byte == lowbyte) up++;
			puthex (*up, 2);
			cksum += *up;
			up += 2;
			puthex (*up, 2);
			cksum += *up;

			puthex (~cksum, 2);
			puts ("");
		    }
		    printf (DefaultTrailer);
		    return;

		case '2':	/* normal data record */
		    printf ("S1");
				/* get number of odd or even bytes */
		    nbytes = ((hexin (&p, 2) - 4) / 2) + 3;
		    puthex (nbytes, 2);
		    address = hexin (&p, 6);
		    if (firstime) {
			firstaddress = address;
			address = 0;
			firstime = FALSE;
		    }
		    else {
			address -= firstaddress;
			address >>= 1;
		    }
		    puthex (address, 4);
		    checksum = ((address & 0xFF00) >> 8) +
				(address & 0xFF) + nbytes;

		    nbytes -= 3;	/* compensate */
		    if ( byte == lowbyte ) p += 2;

		    for (i = nbytes; i; i--)
		    {
			unsigned char temp = hexin (&p, 2);
			p += 2;		/* skip the other byte */
			checksum += temp;
			puthex (temp, 2);
		    }

		    puthex (~checksum, 2);
		    puts ("");
		    break;

		default:
		    quit (1, "prom68: Bad record in file %s\n", dlfilename);
	    }			/* end of switch statement */
	}
    }				/* end of while statement */

    quit (1, "prom68: No end record in file %s\n", dlfilename);
}

/*
 *	static routines to input and output hex characters.
 */

#define	hex(c)		((c) > 9) ? ((c) - 10 + 'A') : ((c) + '0')
#define	unhex(h)	((h) >= 'A') ? ((h) - 'A' + 10) : ((h) - '0')

static unsigned
hexin (buffer, nibbles)
    register char **buffer;
    int nibbles;
{
    register int i;
    register unsigned answer = 0;

    for (i = nibbles; i; i--)
    {
	answer <<= 4;
	answer += unhex (**buffer);
	(*buffer)++;
    }

    return answer;
}


static
puthex (number, nibbles)
    unsigned long number;
    int nibbles;
{
    unsigned char smallbuf [8];	/* maximum number of nibbles in a long */
    register int i;

    for (i = 0; i < nibbles; i++, number >>= 4)
	smallbuf [i] = (number & 0xFL);

    for (i = nibbles; i; i--)
	putchar (hex (smallbuf [i - 1]));
}

