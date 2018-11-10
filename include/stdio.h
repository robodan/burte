/*
 *	Standard header for BURTE file IO.
 *
 * HISTORY
 *	10-28-87 Dan Christian created for BURTE.
 */

#ifndef STDIO_READ
#define STDIO_READ

#include <burte.h>
#include <burteio.h>
#include <romcalls.h>

/*-------------BURTE system calls---------- */
extern long system();		/* BURTE kernel call (fast trap 9) */
#define create(f,p,s)	system(CREATE,(f),(p),(s))
 #define start(x)	system(START,(x))
#define kill(x)		system(KILL,(x))
#define suicide()	system(SUICIDE)
#define	suspend(x)	system(SUSPEND, (x))
#define resume(x)	system(RESUME,(x))
#define wait(n)		system(WAIT, (n))
#define priority(x,y)	system(PRIORITY,(x),(y))
#define proc_state(n)	system(STATE)
#define whoami()	system(WHO_AM_I)
#define msleep(x)       system(MSLEEP,(x))
#define sleep(x)        msleep(1000*(x))
#define super_outp(x,y) system(SUPER_OUTP, (x), (y))
#define super_inp(x)  ((unsigned short) system(SUPER_INP, (x)))
#define set_schedule_interval(x)  system(SET_SCHEDULE_INTERVAL, (x))
#define next_interval() system(NEXT_INTERVAL)
#define supervisor(x,y)  system(SUPERVISOR, (x),(y))
#define super_outb(x,y) system(SUPER_OUTB, (x), (y))
#define super_inb(x)  ((unsigned char) system(SUPER_INB, (x)))

#define post(x,y)	system(POST,(x),(y))
#define pend(x,y,e)	system(PEND,(x),(y),(e))
#define check(x)	(*(x))
#define putc(c,fb)	system(FPUT,(fb),(c))
#define getc(fb)	system(FGET,(fb),0)
#define fput(fq,v)	system(FPUT,(fq),(v))
#define fget(fq,f)	system(FGET,(fq),(f))

    /*---------------direct rom calls------------ */
#define malloc(n)	(krn_table[B_MALLOC])((n))
#define free(p)		(krn_table[B_FREE])((p))
#define realloc(p,n)	(krn_table[B_REALLOC])((p),(n))
#define tell_free()	(krn_table[B_TELL_FREE])()
#define is_mem(p)	(krn_table[B_IS_MEM])((p))
#define set_baud(p,r)	(krn_table[B_SET_BAUD])((p), (r))
#define download(f)	(krn_table[B_DOWNLOAD])((f))
#define f_print(s)	(krn_table[B_FORCE_PRINT])((s))
#define f_char(c)	(krn_table[B_FORCE_CHAR])((c))
#define f_hex(n)	(krn_table[B_FORCE_HEX])((n))
#define f_hexf(n)	(krn_table[B_FORCE_HEXF])((n))
#define f_flush()	(krn_table[B_FORCE_FLUSH])()
#define f_outs(s,f)	(krn_table[B_OUTS])((s),(f))
#define time_read(t)	(krn_table[B_TM_READ])((t))
#define time_set(s,t,c)	(krn_table[B_TM_SET])((s),(t),(c))
#define time_scale(u,p)	(krn_table[B_TM_SCALE])((u),(p))

/* stdin, stdout, and stderr are set up by the startup process. */
/*  In many cases, these will equal termin, termout, and termout. */
extern FILE *stdin, *stdout, *stderr;

#define feof(p)		((p)->status & FILE_EOF)
#define ferror(p)	((p)->status & FILE_ERR)
#define clearerr(p)	((p)->status &= ~(FILE_ERR|FILE_EOF|BREAK))
#define clearbreak(p)	((p)->status &= ~BREAK)

  ;				/* comma just to clean up formatting */
extern int fputs (char *, FILE *);
extern int fputc (int, FILE *);	/* should be char */
extern int fgetc (FILE *);
extern int fgets (char *, int, FILE *, FILE *);
extern int fputcn (FILE *);
extern int fputi(), fputsi(), fputx(), fputsx();
/* Im not ready to deal with strong type checking on these yet */
/*extern int fputi (int, FILE *);
extern int fputsi (int, int, FILE *);
extern int fputx (int, FILE *);
extern int fputsx (int, int, FILE *);*/
extern char *sputi(), *sputsi(), *sputx(), *sputsx(), *sputs();

extern char *sprintf(); 
extern int printf(), fprintf();	/* in fprintf.c */

/*-----------------Convienence macros------------*/
#define gets(b,n)	fgets((b), (n), stdin, stdout)
#define getchar()	getc (stdin)
#define peekc(f)	(*((f)->tail))
#define putchar(c)	putc ((c), stdout)
#define puts(s)		fputs ((s), stdout)
#define putx(x)		fputx ((x), stdout)
#define putsx(x,n)	fputsx ((x),(n),stdout)
#define puti(n)		fputi ((n), stdout)
#define putsi(n,d)	fputi ((n), (d), stdout)
#define putcn()		fputcn (stdout)
#define ioctl(fb,r,a)	((fb->service)((fb),(r),(a)))
#define fflush(fb)	pend ((fb), 0, P_EQUAL)
#define CTRL(n)		((n)&0x1f)

#define TRUE  1
#define FALSE 0

/*--------Other library calls.  Some of these should be split off */
extern char *nxtarg ();		/* in nxtarg.c */
extern char *strarg ();		/* in strarg.c */
extern char *getstr ();		/* in getstr.c */
extern char *getline ();	/* in getline.c */

extern char *strcpy ();		/* in strcpy.c */
extern char *strncpy ();	/* in strncpy.c */
extern char *strcat ();		/* in strcat.c */
extern char *strncat ();	/* in strncat.c */
extern char *index ();		/* in index.c */
extern char *rindex ();		/* in rindex.c */
extern char *skipto ();
extern char *skipover ();	/* in skipto.c */
extern char *skipwords (char *, int); /* in skipover.c */

extern double doublearg ();	/* in doublearg.c */
extern double getdouble ();	/* in getdouble.c */
extern double atof ();		/* in atof.c */

extern int tas (int *);
#endif



