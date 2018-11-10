all : burtetpulib.o libburte 

BURTE = /home/mensa/handsys/332new/burte
LIBS = -L$(BURTE)/lib  -lburte
INCLUDE = -I$(BURTE)/include 
CFLAGS= -O $(INCLUDE)
CRT = userstart.o
#$(BURTE)/lib/userstart.o

LNK = -target sun3 -N -T 3000 $(CRT)

#crt068.o

CC = gcc

.SUFFIXES: .o .c .s
.c.o: ; $(CC) -target sun3 -m68000 -msoft-float $(CFLAGS) -S $*.c; $(CC) -target sun3 -m68000 -msoft-float $(CFLAGS) -c $*.s
.s.o: ; $(CC) -m68000 -msoft-float $(CFLAGS) -c $*.s


libburte : burtetpulib.o
	ar vur libburtetpu.a burtetpulib.o
	ranlib libburtetpu.a

install :
	mv libburtetpu.a $(BURTE)/lib
	chmod oug+r $(BURTE)/lib/libburtetpu.a

clean:
	rm -f *.o *~
