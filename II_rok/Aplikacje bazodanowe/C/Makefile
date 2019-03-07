INC=/usr/include/postgresql
LIB=/usr/lib
CFLAGS=-I$(INC)
LDLIBS=-L$(LIB) -lpq
CC=gcc
ALL=main
connect: main.c
	$(CC) $(CFLAGS) -o main main.c $(LDLIBS)
clean:
	@rm -f *.o *~ $(ALL)
all: main
