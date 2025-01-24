CC= gcc
CFLAGS= -Wall -Wextra

EXE= projet

BINDIR= bin
SRCDIR= src
OBJDIR= obj

SDL_LIB_DIR=~/SDL2/lib/
SDL_INC_DIR=~/SDL2/include/

LIBS=-L$(SDL_LIB_DIR) -lSDL2 -lSDL2main -lSDL2_image -lSDL2_ttf
INCS=-I$(SDL_INC_DIR)
G=

all: $(BINDIR)/$(EXE)

debug: G=-g
debug: $(BINDIR)/$(EXE)

$(BINDIR)/$(EXE) : $(OBJDIR)/main.o
	$(CC) $(CFLAGS) $(G) -o $@ $^ $(INCS) $(LIBS)

$(OBJDIR)/main.o : $(SRCDIR)/main.c
	$(CC) $(CFLAGS) $(G) -c $^ -o $@ $(INCS)

clean_obj:
	rm $(OBJDIR)/*.o
clean_exe:
	rm $(BINDIR)/$(EXE)
clean: clean_obj clean_exe

