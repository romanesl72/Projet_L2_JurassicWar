# Projet_L2_JurassicWar

## Membres du Projet :
- Romane Saint-Léger
- Hannah Sergent
- Solène Orieux

## Cadre :

Projet de L2 Informatique de Le Mans Université

janvier 2026 --> mars 2026


## Description du Projet:

Ce jeu inspiré de Hedgewars est un Worms.

[Lien vers le jeu hedgewars](https://www.hedgewars.org/fr)

Notre jeu est composé de 2 équipes, chacune contenant 3 dinosaures. Tour par tour nous pouvons nous deplacer sur une certaine distance et tirer une seule fois avec l'arme de notre choix dans un certain temps donné.


***Principales règles du jeu :***
- Jeu tour par tour
- Ne pas mourir
- Ne pas tuer ses propres dinos
- Ne pas sortir du terrain
- Ne pas tomber dans l'eau
- Tuer l'équipe adverse

***Objectifs :***
Le but est de tuer toute l'équipe adverse en perdant le moins de points de vie possible avec différentes armes.


## Documentation/GANTT :

**Lien GANTT (Google Sheet)**


**Documentation Doxygen**
Site Doxygen se trouve dans :



## infos installation :

Pour installer les bibliothèques SDL2, SDL2_image et SDL2_ttf :

- ***Sur Linux***

```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
```
- ***Sur macOS***
```bash
brew install sdl2 sdl2_image sdl2_ttf
```

### Pour exécuter le Jeu :

```bash
cd Projet/Projet_L2_JurassicWar/bin
make -f Makefile
./main
```
