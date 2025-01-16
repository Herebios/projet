CC= gcc
CFLAGS= -Wall -Wextra

EXE= projet.exe

BINDIR= bin
SRCDIR= src
OBJDIR= obj

G=

all: $(BINDIR)/$(EXE)

debug: G= -g
debug: projet

$(BINDIR)/$(EXE) : $(OBJDIR)/main.o
	$(CC) $(CFLAGS) $(G) -o $@ $^

$(OBJDIR)/main.o : $(SRCDIR)/main.c
	$(CC) $(CFLAGS) $(G) -c $^ -o $@

clean_obj:
	rm $(OBJDIR)/*.o
clean_exe:
	rm $(BINDIR)/$(EXE)
clean: clean_obj clean_exe

