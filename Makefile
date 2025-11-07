CC=g++

CFLAGS=-c -Wall
objects = calculator.o
target = calc

target: $(objects)
	$(CC) $(objects) -o $(target)

%.o: %.cpp
	$(CC) $(CFLAGS) $<

clean:
	rm -rf *.o $(target)