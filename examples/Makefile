# makefile for real-time executive aplications that
# work with the popeye kernel

BURTE = ..
LIBS = -L$(BURTE)/lib -lburte
INCLUDE = -I$(BURTE)/include

CFLAGS= $(INCLUDE) -O
LNK = -N -Ttext d000 $(BURTE)/lib/userstart.o #../../lib/crt068.o
LNK2 = -N -Ttext d000 $(BURTE)/lib/userstart.o #../../lib/crt068.o
CC = gcc

.SUFFIXES: .o .c .s
.c.o: ; $(CC) -target sun3 -msoft-float $(CFLAGS) -c $*.c
.s.o: ; $(CC) -target sun3 -msoft-float $(CFLAGS) -c $*.s

all : sleeptest.dl sleeptest2.dl timetest.dl hello.dl

sleeptest.dl:	sleeptest.o
	gld -target sun3 -o sleeptest $(LNK) sleeptest.o $(LIBS)
	dl68 -o $@ sleeptest

sleeptest2.dl:	sleeptest2.o
	gld -target sun3 -o sleeptest2 $(LNK) sleeptest2.o $(LIBS)
	dl68 -o $@ sleeptest2

timetest.dl:	timetest.o
	gld -target sun3 -o timetest $(LNK) timetest.o $(LIBS)
	dl68 -o $@ timetest

hello.dl:	hello.o
	gld -target sun3 -o hello $(LNK2) hello.o $(LIBS)
	dl68 -o $@ hello

lint:
	lint $(INCLUDE) $(BSRC) shell.c break.c

depend:
	cp Makefile Makefile.bak
	makedepend -s "# DO NOT DELETE" $(CFLAGS) $(SOURCES) sleeptest.c \
		sleeptest2.c timetest.c hello.c

clean:
	rm -f *.o a.out core pophi hi

backup:
	cp *.c bak
	cp *.h bak
	cp *.s bak
	cp Makefile bak

# DO NOT DELETE THIS LINE IT IS USED BY MAKEDEPEND

sleeptest.o: ../include/stdio.h ../include/burte.h ../include/burteio.h
sleeptest.o: ../include/romcalls.h
sleeptest2.o: ../include/stdio.h ../include/burte.h ../include/burteio.h
sleeptest2.o: ../include/romcalls.h
timetest.o: ../include/stdio.h ../include/burte.h ../include/burteio.h
timetest.o: ../include/romcalls.h
hello.o: ../include/stdio.h ../include/burte.h ../include/burteio.h
hello.o: ../include/romcalls.h
