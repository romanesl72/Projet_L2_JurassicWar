# Non encore achevé

FLAGS_COMPILATION = -Wall `sdl2-config --cflags`
FLAGS_EDITION = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

REP_SRC = ../src
REP_TEST = ../test

FIC_SRC = $(wildcard $(REP_SRC)/*.c)
FIC_TEST = $(wildcard $(REP_TEST)/*.c)
FIC_OBJETS = $(notdir $(FIC_SRC:.c=.o)) $(notdir $(FIC_TEST:.c=.o))

# Edition de liens

EXECUTABLES = ./testFonctionsRebonds ./main_test ./test_archer
OBJETS_PLACEMENT_DINOS = main_test.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsVerification.o chargerMatrice.o
OBJETS_REBONDS = testFonctionsRebonds.o fonctionsVerification.o fonctionsRebonds.o chargerMatrice.o
OBJETS_ARCHER = test_archer.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsVerification.o chargerMatrice.o tirer_archer.o


all: $(EXECUTABLES)

# faire une ligne par exécutable

./main_test: $(OBJETS_PLACEMENT_DINOS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsRebonds: $(OBJETS_REBONDS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./test_archer: $(OBJETS_ARCHER)
	gcc $^ -o $@ $(FLAGS_EDITION)

# Compilation

%.o: $(REP_SRC)/%.c
	gcc $(FLAGS_COMPILATION) -c $< -o $@

%.o: $(REP_TEST)/%.c
	gcc $(FLAGS_COMPILATION) -c $< -o $@

# Suppression

clean:
	rm -f $(FIC_OBJETS) $(EXECUTABLES)

