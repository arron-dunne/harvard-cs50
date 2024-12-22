CC = gcc
CFLAGS = -Wall -Werror -std=c11

all: hello mario credit scrabble readability substitution plurality tideman volume filter recover inheritance dictionary

hello: problems/week1/hello.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week1/hello problems/week1/hello.c lib/cs50.c
	@echo problems/week1/hello

mario: problems/week1/mario.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week1/mario problems/week1/mario.c lib/cs50.c
	@echo problems/week1/mario

credit: problems/week1/credit.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week1/credit problems/week1/credit.c lib/cs50.c
	@echo problems/week1/credit

scrabble: labs/week2/scrabble.c lib/cs50.c
	@$(CC) $(CFLAGS) -o labs/week2/scrabble labs/week2/scrabble.c lib/cs50.c
	@echo labs/week2/scrabble

readability: problems/week2/readability.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week2/readability problems/week2/readability.c lib/cs50.c
	@echo problems/week2/readability

substitution: problems/week2/substitution.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week2/substitution problems/week2/substitution.c lib/cs50.c
	@echo problems/week2/substitution

plurality: problems/week3/plurality.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week3/plurality problems/week3/plurality.c lib/cs50.c
	@echo problems/week3/plurality

tideman: problems/week3/tideman.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week3/tideman problems/week3/tideman.c lib/cs50.c
	@echo problems/week3/tideman

volume: labs/week4/volume.c lib/cs50.c
	@$(CC) $(CFLAGS) -o labs/week4/volume labs/week4/volume.c lib/cs50.c
	@echo labs/week4/volume

filter: problems/week4/filter/filter.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week4/filter/filter problems/week4/filter/filter.c problems/week4/filter/helpers.c lib/cs50.c
	@echo problems/week4/filter/filter

recover: problems/week4/recover.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week4/recover problems/week4/recover.c lib/cs50.c
	@echo problems/week4/recover

inheritance: labs/week5/inheritance.c lib/cs50.c
	@$(CC) $(CFLAGS) -o labs/week5/inheritance labs/week5/inheritance.c lib/cs50.c
	@echo labs/week5/inheritance

speller: problems/week5/speller/speller.c lib/cs50.c
	@$(CC) $(CFLAGS) -o problems/week5/speller/speller problems/week5/speller/speller.c problems/week5/speller/dictionary.c lib/cs50.c
	@echo problems/week5/dictionary


clean:
	@rm -f problems/week1/hello  problems/week1/mario problems/week1/credit
	@rm -f labs/week2/scrabble
	@rm -f problems/week2/readability problems/week2/substitution
	@rm -f problems/week3/plurality 
	@rm -f labs/week3/volume
	@rm -f problems/week4/filter/filter problems/week4/recover
	@rm -f labs/week5/inheritance
	@rm -f problems/week5/dictionary

