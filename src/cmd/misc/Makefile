GROUPBIN = /afs/andrew.cmu.edu/usr0/rc99/bin/@sys
CFLAGS = -g
LIB = -L/afs/andrew.cmu.edu/usr0/rc99/lib/@sys -lcs

mdl68:	mdl68.o
	cc -o mdl68 mdl68.o $(LIB)

time68:	time68.o
	cc -o time68 time68.o

install:	mdl68 time68
	cp mdl68 time68 $(GROUPBIN)

clean:
	rm -f *.o core a.out

