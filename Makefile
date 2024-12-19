CC = gcc
CFLAGS = -Wall -Werror -std=c11

hello: problems/week1/hello.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/hello problems/week1/hello.c lib/cs50.c

clean:
	rm -f problems/week1/hello

