all: app

app: main.o functions.o
	gcc -o app main.o functions.o

main.o: main.c functions.h
	gcc -c -o main.o main.c

functions.o: functions.c
	gcc -c -o functions.o functions.c

clean:
	rm -f app main.o functions.o
