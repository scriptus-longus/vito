CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -Wall

all: build/main.o build/event.o build/math.o
	$(CC) build/main.o build/event.o build/math.o -o vito $(LIBS)	

build/main.o: main.cpp
	$(CC) -c main.cpp -o build/main.o $(LIBS) $(FLAGS)

build/event.o: event.cpp event.hpp
	$(CC) -c event.cpp -o build/event.o $(LIBS) $(FLAGS)

build/math.o: math.cpp math.hpp
	$(CC) -c math.cpp -o build/math.o $(LIBS) $(FLAGS)
