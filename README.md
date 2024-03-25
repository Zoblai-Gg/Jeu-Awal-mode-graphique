# Projet de jeu AWELE

Il s'agit d'une simple implémentation du jeu Awale utilisant SDL2 en langage C.

## Dépendances

- SDL2
- SDL2_image
- SDL2_ttf
- SDL2_mixer

## Installation des dépendances

Ce projet nécessite les bibliothèques SDL2, SDL2_image, SDL2_ttf, SDL2_mixer,
ainsi que `make` et `build-essential`pour construire le projet. Voici comment 
les installer sur différents systèmes d'exploitation, plus précisement dans 
notre environnement de dévellopement qui est Linux (Ubuntu).

### Ubuntu
```sh
sudo apt-get update -y 
```
```sh
sudo apt-get install make build-essential libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev -y
```
## Construire le projet

Le projet inclut un `makefile` pour construire l'application. Pour construire le projet, exécutez la commande suivante dans le terminal :

Pour compiler le projet, utilisez :
```sh
make
```
Pour le nettoyage des fichiers, utilisez :
```sh
make clean
```
## Exécuter le projet

Après avoir compilé le projet, vous pouvez lancer le jeu avec la commande suivante :
```sh
./main


