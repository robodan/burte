
#ifndef INPUT_LENGTH
#define INPUT_LENGTH 80
#endif

#ifndef BUFF_RING_SIZE
#define BUFF_RING_SIZE 8
#endif

#define NO_CLEAR	0x01	/* don't clear the line to be used */
#define NO_NEXT		0x02	/* don't get the next buffer available */
#define REDO		0x03	/* convienent way to re-edit a line */

extern char *read_line();
