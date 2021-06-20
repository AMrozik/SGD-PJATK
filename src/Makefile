LIBS=-lSDL2 -lSDL2_ttf
FLAGS=-Wall -std=c++11
EXEC := pong

all: $(EXEC)

run: $(EXEC)
	 ./$(EXEC)

Vector2f.o: Vector2f.cpp
	 	g++ -c Vector2f.cpp -o Vector2f.o $(LIBS) $(FLAGS)

Pallete.o: Pallete.cpp
		 g++ -c Pallete.cpp -o Pallete.o $(LIBS) $(FLAGS)

Ball.o: Ball.cpp
		 g++ -c Ball.cpp -o Ball.o $(LIBS) $(FLAGS)

main.o: main.cpp
		 g++ -c main.cpp -o main.o $(LIBS) $(FLAGS)

pong: main.o Pallete.o Ball.o Vector2f.o
		 g++ -o $(EXEC) main.o Pallete.o Ball.o Vector2f.o $(LIBS) $(FLAGS)

clean:
		 rm pong
		 rm  *.o
