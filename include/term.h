/* header file for term.c */
extern char *cs_str, *cl_str;
extern redisplay(), init_term();

#define clear_screen(fl) fputs (cs_str, fl)
#define clear_line(fl) fputs (cl_str, fl)
