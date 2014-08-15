CC=gcc
CFLAGS=-g -O3 -Wall -Werror
PHONY := clean

mini: minicsv-test.o minicsv.o
	${CC} minicsv-test.o minicsv.o -o $@

minicsv-test.o: minicsv-test.c
	${CC} $< ${FLAGS} -c

minicsv.o: minicsv.c
	${CC} $< ${FLAGS} -c

clean:
	@rm mini
	@rm -rf *.o

PHONY: $(PHONY)
