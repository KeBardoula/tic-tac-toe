# Makefile pour le projet Tic-Tac-Toe

CC = gcc
CFLAGS = -Wall -Wextra -g

# Fichiers objets
OBJ = main.o

# Fichier exécutable
EXEC = tic-tac-toe

#compilation
$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $(EXEC) $(OBJ)

# Compilation du fichier source
main.o: main.c tic-tac-toe.h
	$(CC) $(CFLAGS) -c main.c
	
# Nettoyage
clean:
	rm -f $(OBJ) $(EXEC)
