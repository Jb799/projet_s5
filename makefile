main: main.o index_motor.o
	gcc -o main main.o index_motor.o

main.o: main.c index_motor.h
	gcc -c main.c

index_motor.o: index_motor.c index_motor.h
	gcc -c index_motor.c