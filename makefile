main: main.o index_motor.o menu.o search_motor.o
	gcc -o main main.o index_motor.o menu.o search_motor.o

main.o: main.c index_motor.h menu.h search_motor.h
	gcc -c main.c

index_motor.o: index_motor.c index_motor.h
	gcc -c index_motor.c

menu.o: menu.c menu.h
	gcc -c menu.c

search_motor.o: search_motor.c search_motor.h
	gcc -c search_motor.c