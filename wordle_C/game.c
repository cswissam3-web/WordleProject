 #include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "game.h"

// Convertir une chaîne en minuscules
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Afficher le feedback comme Wordle officiel
void give_feedback(const char *guess, const char *target) {
    char target_used[WORD_LENGTH] = {0};
    char result_colors[WORD_LENGTH];

    // Lettres vertes
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            result_colors[i] = 2;
            target_used[i] = 1;
        } else {
            result_colors[i] = 0;
        }
    }

    // Lettres jaunes
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result_colors[i] == 0) {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!target_used[j] && guess[i] == target[j]) {
                    result_colors[i] = 1;
                    target_used[j] = 1;
                    break;
                }
            }
        }
    }

    // Affichage
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result_colors[i] == 2) printf("\033[1;32m%c\033[0m", guess[i]);
        else if (result_colors[i] == 1) printf("\033[1;33m%c\033[0m", guess[i]);
        else printf("\033[1;30m%c\033[0m", guess[i]);
    }
    printf("\n");
}