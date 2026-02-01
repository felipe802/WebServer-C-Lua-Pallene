# From now, we have to use the way we downloaded before, lua-internals

# Run everything with "make" and "make clean"
CC = clang
CFLAGS = -I/usr/local/include -Wall # Using core's API
LDFLAGS = -L/usr/local/lib -llua -lm -Wl,-E # Linker search for liblua.a
# I couldn't find any free and complete API as I'd like before, so 
# let's move on and intall Pallene
TARGET = main

.PHONY: all clean

all: method.so $(TARGET)

# Compile Pallene into a shared library
method.so: method.pln
	pallenec method.pln

$(TARGET): main.c
	$(CC) main.c -o $(TARGET) $(CFLAGS) $(LDFLAGS)

# All necessary code is created in C before method.so
clean:
	rm -f $(TARGET) method.so method.c 
	clear

# Run using LD_LIBRARY_PATH=/usr/local/lib ./main