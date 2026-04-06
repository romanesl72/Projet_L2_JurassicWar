FLAGS_COMPILATION = -Wall `sdl2-config --cflags`
FLAGS_EDITION = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

REP_SRC = ../src
REP_TEST = ../test

FIC_SRC = $(wildcard $(REP_SRC)/*.c)
FIC_TEST = $(wildcard $(REP_TEST)/*.c)
FIC_OBJETS = $(notdir $(FIC_SRC:.c=.o)) $(notdir $(FIC_TEST:.c=.o))

# Edition de liens

EXECUTABLES = ./main_test \
./testAffichageMenuHIP \
./testTirsAffichageJeu \
./test_archer \
./testCollisions \
./testFonctionsChangementTour \
./testFonctionsRebonds \
./testFonctionsTuerDinos \
./testTirArmes \
./testRegression


OBJETS_MAIN = main_test.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsVerification.o chargerMatrice.o

OBJETS_COMMUNS = placer_dinos.o chargerMatrice.o tda_nuage.o fonctionsVerification.o
OBJETS_COMMUNS2 = gestion_zones.o fonctionsStructJoueur.o

OBJETS_ARCHER = 			test_archer.o 					$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsTirs.o fonctionsMenuHIP.o
OBJETS_AFFICHAGE_HIP =		testAffichageMenuHIP.o 			$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsMenuHIP.o
OBJETS_TIRSAFFICHAGE = 		testTirsAffichageJeu.o 			$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsMenuHIP.o fonctionsTirs.o fonctionsRebonds.o fonctionsPlacementBombe.o fonctionSoin.o


OBJETS_BOMBE_DINOS_TOURS = 	testBombeDinosTours.o 			$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsChangementTour.o fonctionsPlacementBombe.o fonctionsRebonds.o fonctionsTuerDinos.o
OBJETS_CHANGEMENT_TOUR = 	testFonctionsChangementTour.o 	placer_dinos.o chargerMatrice.o fonctionsChangementTour.o fonctionsStructJoueur.o
OBJETS_COLLISIONS = 		testCollisions.o 				placer_dinos.o testPlacement.o collision_decor.o chargerMatrice.o

OBJETS_REBONDS = 			testFonctionsRebonds.o 			$(OBJETS_COMMUNS) fonctionsMenuHIP.o fonctionsPlacementBombe.o fonctionsRebonds.o fonctionsStructJoueur.o

OBJETS_REGRESSION = 		testRegression.o 				tda_nuage.o regression.o
OBJETS_TIR = 				testTirArmes.o 					placer_dinos.o chargerMatrice.o fonctionsTirs.o fonctionsMenuHIP.o fonctionsStructJoueur.o
OBJETS_TUER_DINOS = 		testFonctionsTuerDinos.o 		$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsRebonds.o fonctionsTuerDinos.o fonctionsPlacementBombe.o fonctionsMenuHIP.o



all: $(EXECUTABLES)


# -------------------   FICHIERS MAIN   -------------------

./main_test: $(OBJETS_MAIN)
	gcc $^ -o $@ $(FLAGS_EDITION)



# -------------------   FICHIERS TEST   -------------------

./test_archer: $(OBJETS_ARCHER)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testAffichageMenuHIP: $(OBJETS_AFFICHAGE_HIP)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testTirsAffichageJeu: $(OBJETS_TIRSAFFICHAGE)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testBombeDinosTours: $(OBJETS_BOMBE_DINOS_TOURS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsChangementTour: $(OBJETS_CHANGEMENT_TOUR)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testCollisions: $(OBJETS_COLLISIONS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testDino: $(OBJETS_DINO)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testPlacement: $(OBJETS_PLACEMENT)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsRebonds: $(OBJETS_REBONDS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testRegression: $(OBJETS_REGRESSION)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testTirArmes: $(OBJETS_TIR)
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

