CC = g++
CC_FLAGS = -w
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

SnakeGame: Main.cpp
	$(CC) Main.cpp $(CC_FLAGS) $(LFLAGS) -o SnakeGame
