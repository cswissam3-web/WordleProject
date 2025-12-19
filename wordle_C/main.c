 #include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game.h"
#include "solver.h"

int main() {
    srand(time(NULL));
    load_dictionary("words.txt");  // charger le dictionnaire
    play_solver();  // lancer le solver automatique
    return 0;
}


