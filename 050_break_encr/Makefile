.PHONY:clean
TARGET=breaker
CFLAGS=-Wall -Werror -pedantic -std=gnu99

$(TARGET) : breaker.c
	gcc -o $(TARGET) $(CFLAGS) breaker.c

clean :
	rm -f $(TARGET)
