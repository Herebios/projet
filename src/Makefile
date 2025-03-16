sdl_include=-I/C/SDL/include
sdl_lib=-L/C/SDL/lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

all : serv cli

serv : serv.o serv_socket.o serv_jeu.o serv_commun.o file.o perso.o objet.o
	gcc $^ -o serv -lpthread -lws2_32 $(sdl_lib)
serv.o : serv.c serv_socket.h serv_jeu.h
	gcc $< -c $(sdl_include)
serv_socket.o : serv_socket.c
	gcc $< -c
serv_jeu.o : serv_jeu.c
	gcc $< -c $(sdl_include)
serv_commun.o : serv_commun.c
	gcc $< -c


cli : cli.o file.o perso.o objet.o
	gcc $^ -o cli -lpthread -lws2_32 $(sdl_lib)
cli.o : cli.c perso_cli.h
	gcc $< -c $(sdl_include)

perso.o : perso.c perso.h objet.h
	gcc $< -c

objet.o : objet.c objet.h
	gcc $< -c

file.o : ../datastruct/file.c
	gcc $< -c

clean :
	rm serv.o cli.o serv_socket.o file.o
