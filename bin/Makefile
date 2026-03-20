FLAGS_COMPILATION = -Wall `sdl2-config --cflags`
FLAGS_EDITION = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

REP_SRC = ../src
REP_TEST = ../test

FIC_SRC = $(wildcard $(REP_SRC)/*.c)
FIC_TEST = $(wildcard $(REP_TEST)/*.c)
FIC_OBJETS = $(notdir $(FIC_SRC:.c=.o)) $(notdir $(FIC_TEST:.c=.o))

# Edition de liens

EXECUTABLES = ./main_test ./test_archer ./test_deplacement ./testCollisions ./testDino ./testFonctionsChangementTour ./testFonctionsRebonds ./testFonctionsTuerDinos ./testPlacement ./testRegression

OBJETS_MAIN = main_test.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsVerification.o chargerMatrice.o

OBJETS_ARCHER = test_archer.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsVerification.o chargerMatrice.o tirer_archer.o
OBJETS_CHANGEMENT_TOUR = testFonctionsChangementTour.o chargerMatrice.o fonctionsChangementTour.o fonctionsStructJoueur.o placer_dinos.o
OBJETS_COLLISIONS = testCollisions.o testPlacement.o collision_decor.o placer_dinos.o
OBJETS_DEPLACEMENT = test_deplacement.o deplacement.o fonctionsVerification.o tda_nuage.o chargerMatrice.o placer_dinos.o regression.o collision_decor.o
OBJETS_DINO = testDino.o placer_dinos.o deplacement.o
OBJETS_PLACEMENT = testPlacement.o collision_decor.o placer_dinos.o
OBJETS_REBONDS = testFonctionsRebonds.o placer_dinos.o fonctionsVerification.o fonctionsRebonds.o chargerMatrice.o
OBJETS_REGRESSION = testRegression.o tda_nuage.o regression.o
OBJETS_TUER_DINOS = testFonctionsTuerDinos.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsRebonds.o fonctionsStructJoueur.o fonctionsVerification.o fonctionsTuerDinos.o chargerMatrice.o


all: $(EXECUTABLES)


# -------------------   FICHIERS MAIN   -------------------

./main_test: $(OBJETS_MAIN)
	gcc $^ -o $@ $(FLAGS_EDITION)



# -------------------   FICHIERS TEST   -------------------

./test_archer: $(OBJETS_ARCHER)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsChangementTour: $(OBJETS_CHANGEMENT_TOUR)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testCollisions: $(OBJETS_COLLISIONS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./test_deplacement: $(OBJETS_DEPLACEMENT)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testDino: $(OBJETS_DINO)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testPlacement: $(OBJETS_PLACEMENT)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsRebonds: $(OBJETS_REBONDS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testRegression: $(OBJETS_REGRESSION)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsTuerDinos: $(OBJETS_TUER_DINOS)
	gcc $^ -o $@ $(FLAGS_EDITION)





# -------------------   COMPILATION   -------------------

%.o: $(REP_SRC)/%.c
	gcc $(FLAGS_COMPILATION) -c $< -o $@

%.o: $(REP_TEST)/%.c
	gcc $(FLAGS_COMPILATION) -c $< -o $@

# Suppression

clean:
	rm -f $(FIC_OBJETS) $(EXECUTABLES)
