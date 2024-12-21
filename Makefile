CC = gcc
CFLAGS = -Wall -Werror -std=c11

all: hello mario credit scrabble readability substitution plurality tideman volume filter recover

hello: problems/week1/hello.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/hello problems/week1/hello.c lib/cs50.c

mario: problems/week1/mario.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/mario problems/week1/mario.c lib/cs50.c

credit: problems/week1/credit.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week1/credit problems/week1/credit.c lib/cs50.c

scrabble: labs/week2/scrabble.c lib/cs50.c
	$(CC) $(CFLAGS) -o labs/week2/scrabble labs/week2/scrabble.c lib/cs50.c

readability: problems/week2/readability.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week2/readability problems/week2/readability.c lib/cs50.c

substitution: problems/week2/substitution.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week2/substitution problems/week2/substitution.c lib/cs50.c

plurality: problems/week3/plurality.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week3/plurality problems/week3/plurality.c lib/cs50.c

tideman: problems/week3/tideman.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week3/tideman problems/week3/tideman.c lib/cs50.c

volume: labs/week4/volume.c lib/cs50.c
	$(CC) $(CFLAGS) -o labs/week4/volume labs/week4/volume.c lib/cs50.c

filter: problems/week4/filter/filter.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week4/filter/filter problems/week4/filter/filter.c problems/week4/filter/helpers.c lib/cs50.c

recover: problems/week4/recover.c lib/cs50.c
	$(CC) $(CFLAGS) -o problems/week4/recover problems/week4/recover.c lib/cs50.c

clean:
	rm -f problems/week1/hello  problems/week1/mario problems/week1/credit
	rm -f labs/week2/scrabble
	rm -f problems/week2/readability problems/week2/substitution
	rm -f problems/week3/plurality 
	rm -f labs/week3/volume
	rm -f problems/week4/filter/filter problems/week4/recover

