projet : obj/main.o
	gcc obj/main.o -o bin/projet
obj/main.o : src/main.c
	gcc -c src/main.c -o obj/main.o
