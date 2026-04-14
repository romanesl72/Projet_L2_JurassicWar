# Projet_L2_JurassicWar

## Membres du Projet :
- Solène Orieux
- Romane Saint-Léger
- Hannah Sergent

## Cadre :

Nous avons entrepris ce projet dans le cadre de la deuxième année de notre cursus de double licence Mathématiques Informatique à l'université du Mans.

[Obtenir plus d'informations sur la double licence Mathématiques Informatique](https://www.univ-lemans.fr/fr/formation/catalogue-des-formations/licence-lmd-LILMD/sciences-technologies-sante-0004/licence-informatique-IW600Y1Z/double-licence-mathematiques-informatique-LOYFWWL9.html)  

***Chronologie du projet :***

janvier 2026 --> avril 2026

## Description du Projet:

Le jeu JurassicWar est composé de 2 équipes, contenant chacune 3 dinosaures. Chaque dinosaure joue tour à jour.
Quand vient le moment pour lui d'agir, le dinosaure peut se déplacer sur le terrain et tirer une seule fois avec l'arme de son choix dans une limite de temps impartie.

Ce jeu reprend les principes des jeux à succès [Hedgewars](https://www.hedgewars.org/fr) et [Worms](https://fr.wikipedia.org/wiki/Worms_(s%C3%A9rie_de_jeux_vid%C3%A9o)).    


***Principales règles du jeu :***

- Un dinosaure possède 100 points de vie au départ d'une partie.
- Un dinosaure meurt s'il a perdu tous ses points de vie, s'il tombe dans l'eau ou heurte une extrémité du terrain.
- Un dinosaure ne peut utiliser qu'un seul outil par tour.
- Un dinosaure a un temps limité pour agir.
- Une arme frappant un dinosaure de notre équipe inflige les mêmes dégâts que si elle avait touché l'adversaire. 

***Objectifs :***

Le but est de tuer tous les dinosaures de l'équipe adverse en perdant le moins de points de vie possible. Pour cela, les dinosaures disposent de différentes armes redoutables telles que la dinoBombe, le grapin ou encore le revolver.

## Documentation :

**Accéder au Diagramme de GANTT :**

```bash
cd Projet_L2_JurassicWar/doc/DiagrammeDeGanttPlanningProjet.ods
cd Projet_L2_JurassicWar/doc/PlanningProjet.ods
```

**Accéder à la documentation Doxygen :**

- ***En local (dernière mise à jour le 14/04/2026)***

```bash
cd Projet_L2_JurassicWar/doc/doxygen/html/index.thml
```

- ***En ligne (dernière mise à jour le 9/04/2026)***

[Documentation doxygen de JurassicWar](https://web-info.univ-lemans.fr/~s2400921/documentationJurassicWar/html/index.html)

## Informations d'installation :

Les bibliothèques SDL2, SDL2_image et SDL_ttf sont nécessaires au fonctionnement du jeu.

**Installer SDL :**

- ***Sur Linux***

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```

- ***Sur macOS***

```bash
brew install sdl2 sdl2_image sdl2_ttf
```

**Exécuter le jeu :**

```bash
cd Projet_L2_JurassicWar/bin
make -f makeProjetGlobal
./main
```
