CC = gcc
FILES = *.c */*.c
FLAGS = -Wall -Werror -Wconversion -std=c99

clear:
	clear

pokemon: $(FILES)
	$(CC) $(FILES) $(FLAGS) -o pokemon

run: pokemon
	./pokemon

zip:
	zip A2_TP2.zip *.c */*.c *.h */*.h *.pdf *.md makefile

check: pokemon
	valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./pokemon
