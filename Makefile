CC = gcc
CFLAGS = -Wall -Werror -std=c11

all: hello mario credit

hello: problems/week1/hello.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/hello problems/week1/hello.c lib/cs50.c

mario: problems/week1/mario.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/mario problems/week1/mario.c lib/cs50.c

credit: problems/week1/credit.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/credit problems/week1/credit.c lib/cs50.c


clean:
	rm -f problems/week1/hello  problems/week1/mario problems/week1/credit

