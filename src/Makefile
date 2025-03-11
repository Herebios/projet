serv : serv.o servHandler.o servHandler.h file.o
	gcc serv.o servHandler.o file.o -o serv -lpthread -lws2_32
serv.o : serv.c servHandler.h
	gcc -c serv.c -lws2_32
servHandler.o : servHandler.c servHandler.h
	gcc $< -c

cli : cli.o file.o
	gcc cli.o file.o -o cli -lpthread -lws2_32
cli.o : cli.c
	gcc cli.c -c -lws2_32

file.o : ../datastruct/file.c
	gcc $< -c

clean :
	rm serv.o cli.o servHandler.o file.o
