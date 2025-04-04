sdl_include=-I/C/SDL/include
sdl_lib=-L/C/SDL/lib -lSDL2main -lSDL2 -lSDL2_image

build: all clean
all: client serv

client: Main.c menu.o cli.o cli_jeu.o jeu.o liste.o file.o perso.o objet.o inventaire.o
	gcc $^ -o VoidBorn -lpthread $(sdl_lib) -lSDL2_ttf -lSDL2_mixer

serv : serv.o serv_socket.o serv_jeu.o jeu.o liste.o serv_commun.o file.o perso.o objet.o
	gcc $^ -o serv -lpthread $(sdl_lib)
serv.o : serv.c serv_socket.h serv_jeu.h
	gcc $< -c $(sdl_include)
serv_socket.o : serv_socket.c
	gcc $< -c
serv_jeu.o : serv_jeu.c
	gcc $< -c $(sdl_include)
serv_commun.o : serv_commun.c
	gcc $< -c

cli : cli.o cli_jeu.o jeu.o liste.o file.o perso.o objet.o inventaire.o
	gcc $^ -o cli -lpthread $(sdl_lib)

cli.o : cli.c
	gcc $< -c $(sdl_include)

cli_jeu.o : cli_jeu.c
	gcc $< -c

jeu.o : jeu.c jeu.h
	gcc $< -c

perso.o : perso.c perso.h objet.h
	gcc $< -c

objet.o : objet.c objet.h
	gcc $< -c

liste.o : liste.c
	gcc $< -c

file.o : file.c
	gcc $< -c

inventaire.o : inventaire.c inventaire.h
	gcc $< -c

menu.o: menu.c menu.h
	gcc menu.c -c -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

clean :
	rm *.o
