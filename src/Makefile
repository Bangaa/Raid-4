CC = gcc
FLAGS = -std=c99
OBJXOR= xorerFunct.o cut_main.o misc.o
OBJJOIN= joinerFunct.o join_main.o xorerFunct.o misc.o

# Creacion del codigo objeto

misc.o: misc.c misc.h
	$(CC) $(FLAGS) -c misc.c

xorerFunct.o: xorerFunct.c xorerFunct.h misc.h
	$(CC) $(FLAGS) -c xorerFunct.c 

joinerFunct.o: joinerFunct.c joinerFunct.h misc.h xorerFunct.h
	$(CC) $(FLAGS) -c joinerFunct.c

join_main.o: join_main.c joinerFunct.h xorerFunct.h misc.h
	$(CC) $(FLAGS) -c join_main.c

cut_main.o: cut_main.c xorerFunct.h misc.h
	$(CC) $(FLAGS) -c cut_main.c


# Creacion del XORer

xorer: $(OBJXOR)
	$(CC) $(OBJXOR) -o CUT

# Creacion del JOINer

joiner: $(OBJJOIN)
	$(CC) $(OBJJOIN) -o JOIN



