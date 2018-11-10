/*
 *	Program to send the time to a 68000
 *
 * HISTORY
 * 12-Apr-83  Rafael Bracho (rxb) at Carnegie-Mellon University
 *	SYN added to achieve proper synchronization with the 68K.
 *	Also, it waits a second for the command echo.
 *
 * 27-Oct-82  John Schlag (jfs) at Carnegie-Mellon University
 *	Created.
 *
 *
 */

#define SYN '\026'		/* to start synchronization */

main()
    {
	long time();
	long l = time(0);

	while (l == time(0));	/* wait a second for things to settle */
	printf("%c%ld\n", SYN, time (0));
    }
