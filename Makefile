all: build run clean clear

build:
	g++ main.cpp -lraylib -o main

run:
	./main

clean:
	rm ./main

clear:
	clear