#
#	MAKEFILE FOR PROM68
#
# HISTORY
#  3-Oct-83  Rafael Bracho (rxb) at Carnegie-Mellon University
#	Created.
#
#
CFLAGS = -O

SOURCES = prom68.c

OBJECTS = prom68.o

LIBRARIES = -lbbnnet -lbbnhdb -lbbn -lbbnstr

prom68:	$(OBJECTS)
	cc -o prom68 $(OBJECTS) $(LIBRARIES)

print: .print
.print: $(SOURCES)
	yapp $?
	utime .print
