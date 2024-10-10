CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

all: main.cpp	
	$(CC) main.cpp -o main $(LIBS)	
