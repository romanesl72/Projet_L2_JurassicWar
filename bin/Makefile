FLAGS_COMPILATION = -g -Wall `sdl2-config --cflags`
FLAGS_EDITION = `sdl2-config --libs` -lSDL2_image -lSDL2_ttf -lm

REP_SRC = ../src
REP_TEST = ../test

FIC_SRC = $(wildcard $(REP_SRC)/*.c)
FIC_TEST = $(wildcard $(REP_TEST)/*.c)
FIC_OBJETS = $(notdir $(FIC_SRC:.c=.o)) $(notdir $(FIC_TEST:.c=.o))

# Edition de liens

EXECUTABLES = ./main \
./testAffichageMenuHIP \
./test_vol \
./testTirsAffichageJeu \
./test_archer \
./testCollisions \
./testBombeDinosTours \
./testBombeDinosToursV2 \
./testFonctionsChangementTour \
./testFonctionsMenuPrinc \
./testFonctionsPagesInformations \
./testFonctionsRebonds \
./testFonctionsTuerDinos \
./testFonctionsVerification \
./testTirArmes \
./testRegression \
./testAffichageDinosMap\
./test_deplacement\
./testGrappin


OBJETS_VOL = test_vol.o fonctionsTirs.o fonctionsVerification.o

OBJETS_MAIN = main.o \
chargerMatrice.o \
fonctionsChangementTour.o \
fonctionsMenuHIP.o \
fonctionsMenuPrinc.o \
fonctionSoin.o \
fonctionsPageJeu.o \
fonctionsPagesInformations.o \
fonctionsPlacementBombe.o \
fonctionsRebonds.o \
fonctionsStructJoueur.o \
fonctionsTirs.o \
fonctionsTuerDinos.o \
fonctionsVerification.o \
gestion_zones.o \
placer_dinos.o \
tda_nuage.o \
deplacement.o \
regression.o \
collision_decor.o \
fonctionsPageFinPartie.o

OBJETS_COMMUNS = placer_dinos.o chargerMatrice.o tda_nuage.o fonctionsVerification.o
OBJETS_COMMUNS2 = gestion_zones.o fonctionsStructJoueur.o fonctionsMenuHIP.o

OBJETS_ARCHER = 			test_archer.o 					$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsTirs.o
OBJETS_AFFICHAGE_DINOS = testAffichageDinosMap.o placer_dinos.o gestion_zones.o tda_nuage.o fonctionsVerification.o chargerMatrice.o
OBJETS_AFFICHAGE_HIP =		testAffichageMenuHIP.o 			$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2)
OBJETS_TIRSAFFICHAGE = 		testTirsAffichageJeu.o 			$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsTirs.o fonctionsRebonds.o fonctionsPlacementBombe.o fonctionSoin.o


OBJETS_BOMBE_DINOS_TOURS = 	testBombeDinosTours.o 			$(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsChangementTour.o fonctionsPlacementBombe.o fonctionsRebonds.o fonctionsTuerDinos.o

OBJETS_BOMBE_DINOS_TOURS_V2 = testBombeDinosToursV2.o \
$(OBJETS_COMMUNS) \
$(OBJETS_COMMUNS2) \
fonctionsChangementTour.o \
fonctionsPlacementBombe.o \
fonctionsRebonds.o \
fonctionsTuerDinos.o \
fonctionsPageJeu.o \
fonctionsTirs.o \
fonctionSoin.o \
deplacement.o \
regression.o \
collision_decor.o \
fonctionsPageFinPartie.o

OBJETS_CHANGEMENT_TOUR = 	testFonctionsChangementTour.o 	placer_dinos.o chargerMatrice.o fonctionsChangementTour.o fonctionsStructJoueur.o
OBJETS_COLLISIONS = 		testCollisions.o 				placer_dinos.o testPlacement.o collision_decor.o chargerMatrice.o

OBJETS_PAGES_INFOS = testFonctionsPagesInformations.o \
$(OBJETS_COMMUNS) \
$(OBJETS_COMMUNS2) \
fonctionsChangementTour.o \
fonctionsMenuPrinc.o \
fonctionsPageJeu.o \
fonctionsPagesInformations.o \
fonctionsPlacementBombe.o \
fonctionsRebonds.o \
fonctionsTuerDinos.o \
fonctionsTirs.o \
fonctionSoin.o \
deplacement.o \
regression.o \
collision_decor.o


OBJETS_REBONDS = testFonctionsRebonds.o \
$(OBJETS_COMMUNS) \
fonctionsMenuHIP.o \
fonctionsPlacementBombe.o \
fonctionsRebonds.o \
fonctionsStructJoueur.o

OBJETS_REGRESSION = testRegression.o 	tda_nuage.o regression.o

OBJETS_TIR = testTirArmes.o \
placer_dinos.o \
chargerMatrice.o \
fonctionsTirs.o \
fonctionsMenuHIP.o \
fonctionsStructJoueur.o

OBJETS_TUER_DINOS = testFonctionsTuerDinos.o \
$(OBJETS_COMMUNS) \
$(OBJETS_COMMUNS2) \
fonctionsRebonds.o \
fonctionsTuerDinos.o \
fonctionsPlacementBombe.o

OBJETS_MENU_PRINC = testFonctionsMenuPrinc.o \
chargerMatrice.o \
fonctionsChangementTour.o \
fonctionsMenuHIP.o \
fonctionsMenuPrinc.o \
fonctionSoin.o \
fonctionsPageJeu.o \
fonctionsPagesInformations.o \
fonctionsPlacementBombe.o \
fonctionsRebonds.o \
fonctionsStructJoueur.o \
fonctionsTirs.o \
fonctionsTuerDinos.o \
fonctionsVerification.o \
gestion_zones.o \
placer_dinos.o \
tda_nuage.o \
deplacement.o \
regression.o \
collision_decor.o

OBJETS_VERIFICATION = testFonctionsVerification.o fonctionsVerification.o

OBJETS_GRAPPIN = testGrappin.o \
	$(OBJETS_COMMUNS) \
	$(OBJETS_COMMUNS2) \
	grappin.o \
	tda_file.o \
	fonctionsAffichage.o \
	fonctionsPageJeu.o \
	fonctionsPageFinPartie.o \
	fonctionsChangementTour.o \
	fonctionsTirs.o \
	fonctionsPlacementBombe.o \
	fonctionsRebonds.o \
	fonctionsTuerDinos.o \
	fonctionsPagesInformations.o \
	fonctionsMenuPrinc.o \
	fonctionSoin.o \
	deplacement.o \
	regression.o \
	collision_decor.o


all: $(EXECUTABLES)


# -------------------   FICHIERS MAIN   -------------------

./main: $(OBJETS_MAIN)
	gcc $^ -o $@ $(FLAGS_EDITION)


# -------------------   FICHIERS TEST   -------------------

./test_archer: $(OBJETS_ARCHER)
	gcc $^ -o $@ $(FLAGS_EDITION)

./test_vol: $(OBJETS_VOL)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testAffichageDinosMap: $(OBJETS_AFFICHAGE_DINOS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testAffichageMenuHIP: $(OBJETS_AFFICHAGE_HIP)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testTirsAffichageJeu: $(OBJETS_TIRSAFFICHAGE)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testBombeDinosTours: $(OBJETS_BOMBE_DINOS_TOURS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testBombeDinosToursV2: $(OBJETS_BOMBE_DINOS_TOURS_V2)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsChangementTour: $(OBJETS_CHANGEMENT_TOUR)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsMenuPrinc: $(OBJETS_MENU_PRINC)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsPagesInformations: $(OBJETS_PAGES_INFOS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testCollisions: $(OBJETS_COLLISIONS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testDino: $(OBJETS_DINO)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testPlacement: $(OBJETS_PLACEMENT)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsRebonds: $(OBJETS_REBONDS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsTuerDinos: $(OBJETS_TUER_DINOS)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testFonctionsVerification: $(OBJETS_VERIFICATION)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testRegression: $(OBJETS_REGRESSION)
	gcc $^ -o $@ $(FLAGS_EDITION)

./testTirArmes: $(OBJETS_TIR)
	gcc $^ -o $@ $(FLAGS_EDITION)

./test_deplacement: test_deplacement.o deplacement.o $(OBJETS_COMMUNS) $(OBJETS_COMMUNS2) fonctionsPageJeu.o fonctionsChangementTour.o regression.o fonctionsAffichage.o fonctionsTirs.o fonctionsPlacementBombe.o fonctionsRebonds.o fonctionSoin.o fonctionsTuerDinos.o fonctionsPagesInformations.o collision_decor.o fonctionsMenuPrinc.o
	gcc $^ -o $@ $(FLAGS_EDITION)

./testGrappin: $(OBJETS_GRAPPIN)
	gcc $^ -o $@ $(FLAGS_EDITION)
# -------------------   COMPILATION   -------------------

%.o: $(REP_SRC)/%.c
	gcc $(FLAGS_COMPILATION) -c $< -o $@

%.o: $(REP_TEST)/%.c
	gcc $(FLAGS_COMPILATION) -c $< -o $@

# Suppression

clean:
	rm -f $(FIC_OBJETS) $(EXECUTABLES)

