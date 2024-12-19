CC = gcc
CFLAGS = -Wall -Werror -std=c11

hello: problems/week1/hello.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/hello problems/week1/hello.c lib/cs50.c

mario: problems/week1/mario.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/mario problems/week1/mario.c lib/cs50.c

all: hello mario

clean:
	rm -f problems/week1/hello  problems/week1/mario

