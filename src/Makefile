CC=clang -Wall
# to be replaced by your own file
TARGET=life

all: ${TARGET}

${TARGET}: ${TARGET}.o inout.o

inout.o: inout.c

clean:
	rm -f *.o *~ ${TARGET}
