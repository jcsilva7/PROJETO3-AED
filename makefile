CC = gcc
CFLAGS = -Wall -Wextra -O3 -march=native -flto -funroll-loops -fno-omit-frame-pointer
DEPS = insertion.h heap_sort.h quick_sort.h swap.h
OBJ = program.o insertion.o heap_sort.o quick_sort.o swap.o
TARGET = program

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: clean

clean:
	rm -f *.o $(TARGET)
