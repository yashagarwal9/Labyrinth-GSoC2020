CC=g++ -std=c++11
all: labyrinth
	./labyrinth input.txt output.txt
labyrinth:
	$(CC) labyrinth.cpp -o labyrinth
clean:
	rm labyrinth