
# Répertoires
SRC_DIR = src
BIN_DIR = bin

# Compilation
CC = gcc
CFLAGS = -c $(SDL_INCLUDE)
LDFLAGS = -lpthread $(SDL_LIB)

# SDL
SDL_INCLUDE = -I/C/SDL/include
SDL_LIB = -L/C/SDL/lib -lSDL2main -lSDL2 -lSDL2_image

# Bibliothèques supplémentaires pour menu et client
SDL_EXTRA = -lSDL2_ttf -lSDL2_mixer

# Fichiers objets client
OBJS_CLIENT = \
	$(BIN_DIR)/menu.o \
	$(BIN_DIR)/cli.o \
	$(BIN_DIR)/cli_jeu.o \
	$(BIN_DIR)/jeu.o \
	$(BIN_DIR)/liste.o \
	$(BIN_DIR)/file.o \
	$(BIN_DIR)/perso.o \
	$(BIN_DIR)/objet.o \
	$(BIN_DIR)/inventaire.o

# Fichiers objets serveur
OBJS_SERV = \
	$(BIN_DIR)/serv.o \
	$(BIN_DIR)/serv_socket.o \
	$(BIN_DIR)/serv_jeu.o \
	$(BIN_DIR)/jeu.o \
	$(BIN_DIR)/liste.o \
	$(BIN_DIR)/serv_commun.o \
	$(BIN_DIR)/file.o \
	$(BIN_DIR)/perso.o \
	$(BIN_DIR)/objet.o

# Cibles
.PHONY build: all clean

all: client serv

client: $(OBJS_CLIENT) src/Main.c
	$(CC) $^ -o $(BIN_DIR)/VoidBorn $(LDFLAGS) $(SDL_EXTRA)

serv: $(OBJS_SERV)
	$(CC) $^ -o $(BIN_DIR)/serv $(LDFLAGS)

doc: Doxyfile
	doxygen Doxyfile

# Règles de compilation des fichiers serveur
$(BIN_DIR)/serv.o: $(SRC_DIR)/serv.c $(SRC_DIR)/serv_socket.h $(SRC_DIR)/serv_jeu.h
	$(CC) $(SRC_DIR)/serv.c -o $@ $(CFLAGS)

$(BIN_DIR)/serv_socket.o: $(SRC_DIR)/serv_socket.c
	$(CC) $(SRC_DIR)/serv_socket.c -o $@ -c

$(BIN_DIR)/serv_jeu.o: $(SRC_DIR)/serv_jeu.c
	$(CC) $(SRC_DIR)/serv_jeu.c -o $@ $(CFLAGS)

$(BIN_DIR)/serv_commun.o: $(SRC_DIR)/serv_commun.c
	$(CC) $(SRC_DIR)/serv_commun.c -o $@ -c

# Règles de compilation des fichiers client
cli: $(BIN_DIR)/cli.o $(BIN_DIR)/cli_jeu.o $(BIN_DIR)/jeu.o $(BIN_DIR)/liste.o $(BIN_DIR)/file.o $(BIN_DIR)/perso.o $(BIN_DIR)/objet.o $(BIN_DIR)/inventaire.o
	$(CC) $^ -o $(BIN_DIR)/cli $(LDFLAGS)

$(BIN_DIR)/cli.o: $(SRC_DIR)/cli.c
	$(CC) $(SRC_DIR)/cli.c -o $@ $(CFLAGS)

$(BIN_DIR)/cli_jeu.o: $(SRC_DIR)/cli_jeu.c
	$(CC) $(SRC_DIR)/cli_jeu.c -o $@ -c

$(BIN_DIR)/jeu.o: $(SRC_DIR)/jeu.c $(SRC_DIR)/jeu.h
	$(CC) $(SRC_DIR)/jeu.c -o $@ -c

$(BIN_DIR)/perso.o: $(SRC_DIR)/perso.c $(SRC_DIR)/perso.h $(SRC_DIR)/objet.h
	$(CC) $(SRC_DIR)/perso.c -o $@ -c

$(BIN_DIR)/objet.o: $(SRC_DIR)/objet.c $(SRC_DIR)/objet.h
	$(CC) $(SRC_DIR)/objet.c -o $@ -c

$(BIN_DIR)/liste.o: $(SRC_DIR)/liste.c
	$(CC) $(SRC_DIR)/liste.c -o $@ -c

$(BIN_DIR)/file.o: $(SRC_DIR)/file.c
	$(CC) $(SRC_DIR)/file.c -o $@ -c

$(BIN_DIR)/inventaire.o: $(SRC_DIR)/inventaire.c $(SRC_DIR)/inventaire.h
	$(CC) $(SRC_DIR)/inventaire.c -o $@ -c

$(BIN_DIR)/menu.o: $(SRC_DIR)/menu.c $(SRC_DIR)/menu.h
	$(CC) $(SRC_DIR)/menu.c -o $@ -c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

# Nettoyage
clean:
	rm -f $(BIN_DIR)/*.o $(BIN_DIR)/VoidBorn $(BIN_DIR)/serv $(BIN_DIR)/cli
.PHONY: all build clean client serv
