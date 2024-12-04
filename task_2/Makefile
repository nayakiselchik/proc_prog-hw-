CC = gcc
CFLAGS = -Wall -Werror -O2 -g

all: c_list.o test_c_list

c_list.o: c_list.c c_list.h
	$(CC) $(CFLAGS) -c c_list.c

test_c_list: c_list.o test_c_list.c
	$(CC) $(CFLAGS) -o test_c_list c_list.o test_c_list.c

clean:
	rm -f *.o test_c_list

valgrind: test_c_list
	valgrind --leak-check=full --track-origins=yes ./test_c_list
