SERIAL = serial.c

all : dlpnew 
#dlp dlp2

dlp : dlp.c
	cc -o dlpa dlp.c
	cc -o dlpb -DTTYB dlp.c

dlp2 : dlp2.c $(SERIAL)
	cc -o dlp2a dlp2.c $(SERIAL)
	cc -o dlp2b -DTTYB dlp2.c $(SERIAL)

dlpnew : dlpnew.c $(SERIAL)
	cc -o dlpnew dlpnew.c $(SERIAL)
	
clean :
	rm -f *~
	rm -f *.o
	rm -f dlpa dlpb dlp2a dlp2b dlpnew


install : 
	cp dlpnew /home/mensa/handsys/bin
#	cp dlpa /home/mensa/handsys/bin
#	cp dlpb /home/mensa/handsys/bin
#	cp dlp2a /home/mensa/handsys/bin
#	cp dlp2b /home/mensa/handsys/bin

