CC = gcc
CFLAGS = -Wall -Wpointer-arith -Wstrict-prototypes -std=gnu89 -fPIC -MMD -MP -lpthread

all: test-mergesort test-base-case

#This builds an executable for the parallel merge sort
test-mergesort: test-mergesort.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $?

.PHONY: clean
clean:
	/bin/rm -f *.o *.d test-mergesort test-base-case

#This builds an executable for the base case testing (serial-mergesort)
test-base-case: test-base-case.o mergesort.o
	$(CC) $(CFLAGS) -o $@ $?