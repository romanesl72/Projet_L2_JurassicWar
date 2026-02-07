# Chemin racine de la bibliothèque SDL2
SDL_DIR = "C:\Users\roman\Documents\Developpement\Librairies\SDL2-2.32.10\x86_64-w64-mingw32"

# Dossiers d'inclusion et de librairies
SDL_INC = -I$(SDL_DIR)\include
SDL_LIB = -L$(SDL_DIR)\lib -lmingw32 -lSDL2main -lSDL2

# Compilation
CC = gcc
CFLAGS = -Wall -Wextra -g $(SDL_INC)

# Fichiers sources pour le programme de test
SRC_TEST = test/testCollisions.c test/testPlacement.c src/collision_decor.c src/placer_dinos.c
OBJ_TEST = $(SRC_TEST:.c=.o)
EXEC_TEST = bin/test_physique.exe

# Règle par défaut : compile et lance le test
test: $(EXEC_TEST)
	./$(EXEC_TEST)

$(EXEC_TEST): $(OBJ_TEST)
	@if not exist bin mkdir bin
	$(CC) $(OBJ_TEST) -o $(EXEC_TEST) $(SDL_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@del /f /q src\*.o test\*.o bin\*.exe 2>nul