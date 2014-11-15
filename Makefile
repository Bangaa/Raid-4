CC = gcc
CFLAGS = -std=c99 

OBJDIR = build/obj

OBJXOR= $(addprefix $(OBJDIR)/, xorerFunct.o cut_main.o misc.o)
OBJJOIN= $(addprefix $(OBJDIR)/, joinerFunct.o join_main.o xorerFunct.o misc.o)

EXE = raid4

VPATH = src/:build/obj/

# Creacion del codigo objeto
ALL: $(OBJDIR)/main.o xorer joiner | $(OBJDIR)
	$(CC) $< -o build/$(EXE)

$(OBJDIR)/misc.o: misc.c misc.h  | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/xorerFunct.o: xorerFunct.c xorerFunct.h misc.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/joinerFunct.o: joinerFunct.c joinerFunct.h misc.h xorerFunct.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/join_main.o: join_main.c joinerFunct.h xorerFunct.h misc.h | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/cut_main.o: cut_main.c xorerFunct.h misc.h | $(OBJXOR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR)/main.o: main.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Creacion del directorio de salida en caso que no existiera

$(OBJDIR):
	mkdir -p build/obj

# Creacion del XORer

xorer: $(OBJXOR)
	$(CC) $(CFLAGS) $^ -o build/CUT

# Creacion del JOINer

joiner: $(OBJJOIN)
	$(CC) $(CFLAGS) $^ -o build/JOIN

# Limpiar los objetos antiguos para empezar denuevo
clean:
	rm -f build/obj/*.o
	rm -f build/CUT build/JOIN
	rm -f *.o


