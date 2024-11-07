CC = gcc
CFLAGS = -Wall -Wextra

home_task_7: c_list.o main.o
	$(CC) -o home_task_7 c_list.o main.o

c_list.o: c_list.c c_list.h
	$(CC) $(CFLAGS) -c c_list.c

main.o: main.c c_list.h
	$(CC) $(CFLAGS) -c main.c

clean:
	rm -f *.o home_task_7
