CC = gcc
FLAGS = -std=c99
OBJXOR= xorerFunct.o cut_main.o misc.o

misc.o: misc.c misc.h
	$(CC) $(FLAGS) -c misc.c

xorerFunct.o: xorerFunct.c xorerFunct.h misc.o
	$(CC) $(FLAGS) -c xorerFunct.c 

joinerFunct.o: joinerFunct.c joinerFunct.h misc.o
	$(CC) $(FLAGS) -c joinerFunct.c

cut_main.o: cut_main.c xorerFunct.o misc.o
	$(CC) $(FLAGS) -c 

xorer: $(OBJXOR)
	$(CC) xorerFunct.o cut_main.o -o CUT


