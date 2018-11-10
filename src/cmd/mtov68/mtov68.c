/*--------------------------------------------------------------------
 *
 *  Abstract:
 *	mtov68 - Convert MACSBUG format to VERSABUG format.
 *
 *  Parameters:
 *	A MACSBUG file that can be specified in the command
 *	string or piped in through standard input.
 *
 *  Results:
 *	Returns TRUE iff operation was successful.
 *
 *  Side Effects:
 *	Specified file is transformed to VERSABUG format.
 *	Input file is over written.
 *
 *  Environment:
 *
 *    Imports:
 *	'Standard I/O'
 *
 *    Exports:
 *	main ()
 *	MtoV ()
 *
 *  Errors:
 *	None known.
 *
 *  Design:
 *	Leave S0, S2, and S9 records alone.
 *	Convert S1 records to S2 records.
 *	Change the format of S8 records to agree with the standard.
 *
 * HISTORY
 * 14-Dec-82  John Schlag (jfs) at Carnegie-Mellon University
 *	Put in a hack to change the format of S8 records. I believe
 *	the S8 records being manufactured by the Whitesmiths' utility
 *	hex(1) are erroneous. The execution address should be in the
 *	address field, not the data field.
 *
 * 08-Oct-82  Jim McQuade (jpm) at Carnegie-Mellon University
 *	Fixed bug in incrementing byte count; ASCII(9) + 1 != ASCII(A)
 *
 * 31-Mar-82  Jim McQuade (jpm) at Carnegie-Mellon University
 *	Created.
 *
 *--------------------------------------------------------------------
 */

#include <stdio.h>
#include <signal.h>

#define START_CHAR	'S'
#define NEWLINE		'\n'
#define BUFSIZE		100
#define HEX(c)		(c > 9 ? c + 0x37 : c + '0')

FILE *fopen ();
static char buffer [BUFSIZE];

int MtoV (ifp, ofp)
FILE *ifp, *ofp;
{
    int i;

    do {
	/* read next record from ifp into buffer */
	inbuf (buffer, ifp);

	switch (*(buffer+1)) {
	    case '0':
	    case '2':
		/* copy buffer to ofp */
		outbuf (buffer, ofp);
		break;

	    case '8':
		/* change the format of the record to standard (?) */
		buffer[3] = '4';		/* change from 6 bytes to 4 */
		strcpy (buffer+4, buffer+8);	/* move the rest to the left */
		outbuf (buffer, ofp);		/* write it out */
		return;

	    case '9':
		/* copy buffer to ofp and finish */
		outbuf (buffer, ofp);
		return;

	    case '1':
		/* Pad address field with 2 leading zeroes */
		i = 0;
		while (*(buffer + i) != NEWLINE) i++;

		do {
		    *(buffer + i + 2) = *(buffer + i);
		} while (i-- > 4);
		*(buffer + 4) = '0';
		*(buffer + 5) = '0';

		/* Add 1 to byte count */
		if ((*(buffer + 3) += 1) == 'G') {
		    *(buffer + 3) = '0';
		    *(buffer + 2) += 1;
		}
		else if (*(buffer + 3) == ':')
		    *(buffer + 3) = 'A';

		/* Change to S2 */
		*(buffer + 1) = '2';

		/* recompute check sum */
		ccks (buffer);

		/* copy buffer to ofp */
		outbuf (buffer, ofp);
		break;

	}
    } while (1);
}

outbuf (buf, fp)
char *buf;
FILE *fp;
{
    do {
	putc (*buf, fp);
    } while (*buf++ != NEWLINE);
}

inbuf (buf, fp)
char *buf;
FILE *fp;
{
    do {
	*buf = getc (fp);
    } while (*buf++ != NEWLINE);
}

ccks (cp)	/* Compute check sum of an ASCII stream */
register char *cp;
{
    unsigned char i, data, cnt, sum;

    cp += 2;
    sscanf (cp, "%2x", &cnt);
    sum = cnt;

    cnt -= 1;
    while (cnt--) {
	cp += 2;
	sscanf (cp, "%2x", &data);
	sum += data;
    }
    cp += 2;
    sum = ~sum;
    data = (sum & 0xF0) >> 4;
    *cp++ = HEX (data);
    data = sum & 0xF;
    *cp++ = HEX (data);
    *cp   = '\n';
}

char *template = "/tmp/mtovxxxxxx";

main (argc, argv)
int argc;
char *argv [];
{
    FILE *ifp, *ofp;
    extern rmts ();

    if (signal (SIGINT, SIG_IGN) != SIG_IGN)
	signal (SIGINT, rmts);
    if (signal (SIGTERM, SIG_IGN) != SIG_IGN)
	signal (SIGTERM, rmts);

    if (argc == 2) {
	if ((ifp = fopen (*(argv + 1), "r")) == NULL) {
	    printf ("Could not open %s\n", *(argv + 1));
	    exit (1);
	}

	sprintf (template, "/tmp/mtov%d", getpid ());
	if ((ofp = fopen (template, "w")) == NULL) {
	    printf ("Could not open scratch file %s\n", template);
	    exit (2);
	}
    }
    else if (argc != 1) {
	printf ("Usage: mtov68 <file>\n");
	exit (3);
    }
    else {
	ifp = stdin;
	ofp = stdout;
    }

    MtoV (ifp, ofp);

    if (argc == 2) {
	fclose (ifp);
	fclose (ofp);
	strcpy (buffer, "mv ");
	strcat (buffer, template);
	strcat (buffer, " ");
	strcat (buffer, *(argv + 1));
	system (buffer);
    }
    rmts ();
    exit (0);
}

rmts () {
    unlink (template);
}
