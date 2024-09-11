.PHONY: clean
TARGET=maxSeq
CFLAGS=-std=gnu99 -Wall -Werror -pedantic

$(TARGET) : maxSeq.o test-subseq.o
	gcc -o $@ $(CFLAGS) $^

%.o : %.c
	gcc -o $@ $(CFLAGS) -c $<

clean :
	rm -f ./*.o $(TARGET)

