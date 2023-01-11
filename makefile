main: main.o index_motor.o menu.o
	gcc -o main main.o index_motor.o menu.o

main.o: main.c index_motor.h menu.h
	gcc -c main.c

index_motor.o: index_motor.c index_motor.h
	gcc -c index_motor.c

menu.o: menu.c menu.h
	gcc -c menu.c