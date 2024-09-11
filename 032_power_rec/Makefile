.PHONY: clean
TARGET=power
CFLAGS=-std=gnu99 -Wall -Werror -pedantic

$(TARGET) : test-power.o power.o
	gcc -o $@ $(CFLAGS) $^

%.o : %.c
	gcc -o $@ $(CFLAGS) -c $<

clean :
	rm -f ./*.o $(TARGET)

