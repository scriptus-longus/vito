CC = g++
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
FLAGS = -Wall -std=c++17

all: build/main.o build/event.o build/math.o build/object.o build/entity.o build/camera.o build/scene.o
	$(CC) build/main.o build/event.o build/math.o build/object.o build/entity.o build/camera.o build/scene.o -o vito $(LIBS)	 $(FLAGS)

build/main.o: main.cpp
	$(CC) -c main.cpp -o build/main.o $(FLAGS) #$(LIBS) $(FLAGS)

build/event.o: event.cpp event.hpp
	$(CC) -c event.cpp -o build/event.o $(FLAGS) # $(LIBS) $(FLAGS)

build/math.o: math.cpp math.hpp
	$(CC) -c math.cpp -o build/math.o $(FLAGS) # $(LIBS) $(FLAGS)

build/object.o: object.cpp object.hpp
	$(CC) -c object.cpp -o build/object.o $(FLAGS) #$(LIBS) $(FLAGS)

build/camera.o: camera.cpp camera.hpp
	$(CC) -c camera.cpp -o build/camera.o $(FLAGS)

build/entity.o: scene.cpp scene.hpp
	$(CC) -c entity.cpp -o build/entity.o $(FLAGS)

build/scene.o: scene.cpp scene.hpp
	$(CC) -c scene.cpp -o build/scene.o $(FLAGS)
