OBJ=main.o sort.o time.o
OS := $(shell uname)

ifeq ($(OS),Darwin)
LDFLAGS=-lpthread -lc -lm
else
LDFLAGS=-lpthread -lc -lm -lrt
endif

all:sort

sort:$(OBJ)
	gcc -o $@ $^ $(LDFLAGS)


%.o: %.c header.h
	gcc -o $@ -c $<

clean:
	rm -rf *.o sort
