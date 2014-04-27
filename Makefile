CC = gcc
FLAGS = -std=c99
OBJXOR= xorerFunct.o cut_main.o misc.o
OBJJOIN= joinerFunct.o join_main.o xorerFunct.o misc.o
VPATH = src:build/obj

# Creacion del codigo objeto
ALL: xorer joiner 

misc.o: misc.c misc.h
	$(CC) -c $(FLAGS) $< -o build/obj/$@

xorerFunct.o: xorerFunct.c xorerFunct.h misc.h
	$(CC) -c $(FLAGS) $< -o build/obj/$@

joinerFunct.o: joinerFunct.c joinerFunct.h misc.h xorerFunct.h
	$(CC) -c $(FLAGS) $< -o build/obj/$@

join_main.o: join_main.c joinerFunct.h xorerFunct.h misc.h
	$(CC) -c $(FLAGS) $< -o build/obj/$@

cut_main.o: cut_main.c xorerFunct.h misc.h
	$(CC) -c $(FLAGS) $< -o build/obj/$@

# Creacion del XORer

xorer: $(OBJXOR)
	$(CC) $^ -o build/CUT

# Creacion del JOINer

joiner: $(OBJJOIN)
	$(CC) $^ -o build/JOIN

clean:
	rm -f build/obj/*.o
	rm -f build/CUT build/JOIN


