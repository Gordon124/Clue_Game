SRC = adventure.c characters.c rooms.c items.c 
OBJ = adventure.o characters.o rooms.o items.o
PROG = clue

$(PROG): $(OBJ)
	gcc -std=c99 $(OBJ) -o $(PROG)

$(OBJ): $(SRC)
