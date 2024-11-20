all: build run clean clear

build:
	g++ main.cpp -lraylib

run:
	./a.out

clean:
	rm ./a.out

clear:
	clear