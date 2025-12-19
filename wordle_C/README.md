# Wordle Project - Partie 2

## Description
Ce projet est un solver automatique pour le jeu Wordle, écrit en C.
Le programme choisit un mot secret au hasard dans le dictionnaire et essaie de le deviner automatiquement.
Chaque essai est affiché avec les lettres en vert (bonne lettre, bonne position), jaune (bonne lettre, mauvaise position) ou gris (lettre incorrecte).

## Fichiers
- main.c : point d'entrée du programme, lance le solver
- game.c / game.h : fonctions pour afficher le feedback des lettres
- solver.c / solver.h : logique du solver automatique
- words.txt : dictionnaire de mots de 5 lettres
- README.md : ce fichier
- report.pdf : analyse et documentation (à ajouter)

## Compilation
Pour compiler le programme, utilisez la commande suivante dans le terminal :

```bash
gcc main.c game.c solver.c -o solver 