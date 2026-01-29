CC = clang
CFLAGS = -I/usr/include/lua5.4
LDFLAGS = -llua5.4 - lcurl
TARGET = main

.PHONY: all clean

all: $(TARGET)

$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
	clear