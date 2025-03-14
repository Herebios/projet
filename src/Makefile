all: serv cli

serv : serv.o servHandler.o servHandler.h file.o
	gcc serv.o servHandler.o file.o -o serv -lpthread
serv.o : serv.c servHandler.h
	gcc -c serv.c
servHandler.o : servHandler.c servHandler.h
	gcc $< -c

cli : cli.o file.o
	gcc cli.o file.o -o cli -lpthread
cli.o : cli.c
	gcc cli.c -c

file.o : ../datastruct/file.c
	gcc $< -c

clean :
	rm serv.o cli.o servHandler.o file.o
	rm cli serv
