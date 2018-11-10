all : dl68 mkbin

GROUPBIN = /home/mensa/handsys/bin


CFLAGS = -O
LIB =

dl68:	dl68.o
	gcc -o dl68 dl68.o $(LIB)

mkbin:	mkbin.o
	gcc -o mkbin mkbin.o $(LIB)

down68: down68.o
	cc -o down68 down68.o $(LIB)

install:
	cp dl68 $(GROUPBIN)
	cp mkbin $(GROUPBIN)

clean:
	rm -f down68 down68.o dl68 dl68.o core a.out

