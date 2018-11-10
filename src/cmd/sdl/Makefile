CFLAGS = -O

TARGET = sdl
GROUPBIN = /usr/dac/bin

OBJECTS = sdl.o rd_dlbytes.o

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(OBJECTS)

install:	$(TARGET)
	cp $(TARGET) $(GROUPBIN)

clean:
	rm $(TARGET) $(OBJECTS)
