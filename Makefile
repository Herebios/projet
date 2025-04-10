
# Répertoires
SRC_DIR = src
BIN_DIR = bin
OBJ_DIR = obj

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
	$(OBJ_DIR)/menu.o \
	$(OBJ_DIR)/cli.o \
	$(OBJ_DIR)/cli_jeu.o \
	$(OBJ_DIR)/jeu.o \
	$(OBJ_DIR)/liste.o \
	$(OBJ_DIR)/file.o \
	$(OBJ_DIR)/perso.o \
	$(OBJ_DIR)/objet.o \
	$(OBJ_DIR)/inventaire.o

# Fichiers objets serveur
OBJS_SERV = \
	$(OBJ_DIR)/serv.o \
	$(OBJ_DIR)/serv_socket.o \
	$(OBJ_DIR)/serv_jeu.o \
	$(OBJ_DIR)/jeu.o \
	$(OBJ_DIR)/liste.o \
	$(OBJ_DIR)/serv_commun.o \
	$(OBJ_DIR)/file.o \
	$(OBJ_DIR)/perso.o \
	$(OBJ_DIR)/objet.o

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
$(OBJ_DIR)/serv.o: $(SRC_DIR)/serv.c $(SRC_DIR)/serv_socket.h $(SRC_DIR)/serv_jeu.h
	$(CC) $(SRC_DIR)/serv.c -o $@ $(CFLAGS)

$(OBJ_DIR)/serv_socket.o: $(SRC_DIR)/serv_socket.c
	$(CC) $(SRC_DIR)/serv_socket.c -o $@ -c

$(OBJ_DIR)/serv_jeu.o: $(SRC_DIR)/serv_jeu.c
	$(CC) $(SRC_DIR)/serv_jeu.c -o $@ $(CFLAGS)

$(OBJ_DIR)/serv_commun.o: $(SRC_DIR)/serv_commun.c
	$(CC) $(SRC_DIR)/serv_commun.c -o $@ -c

# Règles de compilation des fichiers client
$(OBJ_DIR)/cli.o: $(SRC_DIR)/cli.c
	$(CC) $(SRC_DIR)/cli.c -o $@ $(CFLAGS)

$(OBJ_DIR)/cli_jeu.o: $(SRC_DIR)/cli_jeu.c
	$(CC) $(SRC_DIR)/cli_jeu.c -o $@ -c

$(OBJ_DIR)/jeu.o: $(SRC_DIR)/jeu.c $(SRC_DIR)/jeu.h
	$(CC) $(SRC_DIR)/jeu.c -o $@ -c

$(OBJ_DIR)/perso.o: $(SRC_DIR)/perso.c $(SRC_DIR)/perso.h $(SRC_DIR)/objet.h
	$(CC) $(SRC_DIR)/perso.c -o $@ -c

$(OBJ_DIR)/objet.o: $(SRC_DIR)/objet.c $(SRC_DIR)/objet.h
	$(CC) $(SRC_DIR)/objet.c -o $@ -c

$(OBJ_DIR)/liste.o: $(SRC_DIR)/liste.c
	$(CC) $(SRC_DIR)/liste.c -o $@ -c

$(OBJ_DIR)/file.o: $(SRC_DIR)/file.c
	$(CC) $(SRC_DIR)/file.c -o $@ -c

$(OBJ_DIR)/inventaire.o: $(SRC_DIR)/inventaire.c $(SRC_DIR)/inventaire.h
	$(CC) $(SRC_DIR)/inventaire.c -o $@ -c

$(OBJ_DIR)/menu.o: $(SRC_DIR)/menu.c $(SRC_DIR)/menu.h
	$(CC) $(SRC_DIR)/menu.c -o $@ -c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

mrproprer: clean
	rm $(BIN_DIR)/VoidBorn $(BIN_DIR)/serv $(BIN_DIR)/cli

# Nettoyage
clean:
	rm -f $(OBJ_DIR)/*.o


.PHONY: all build clean client serv
