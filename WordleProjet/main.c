 #include <stdio.h>
#include <string.h>
#include <ctype.h>

#define WORD_LENGTH 5
#define MAX_ATTEMPTS 6

// Mot secret fixe
const char TARGET[WORD_LENGTH + 1] = "apple";

// Convertir une chaîne en minuscules
void to_lowercase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Afficher le feedback comme Wordle officiel
 void give_feedback(const char *guess, const char *target) {
    char target_used[WORD_LENGTH] = {0};
    char result_colors[WORD_LENGTH]; // 0 = gris, 1 = jaune, 2 = vert

    // Étape 1 : vérifier les lettres vertes
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            result_colors[i] = 2; // vert
            target_used[i] = 1;
        } else {
            result_colors[i] = 0; // par défaut gris
        }
    }

    // Étape 2 : vérifier les lettres jaunes
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result_colors[i] == 0) { // seulement les lettres non vertes
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!target_used[j] && guess[i] == target[j]) {
                    result_colors[i] = 1; // jaune
                    target_used[j] = 1;
                    break;
                }
            }
        }
    }

    // Étape 3 : afficher le feedback dans l’ordre de l’essai
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (result_colors[i] == 2) {
            printf("\033[1;32m%c\033[0m", guess[i]); // vert
        } else if (result_colors[i] == 1) {
            printf("\033[1;33m%c\033[0m", guess[i]); // jaune
        } else {
            printf("\033[1;30m%c\033[0m", guess[i]); // gris
        }
    }
    printf("\n");
}

int main() {
    char guess[WORD_LENGTH + 1];
    int attempts = 0;
    int win = 0;

    printf("=== Bienvenue dans le jeu Wordle ===\n");
    printf("Devinez le mot de 5 lettres ! Vous avez %d essais.\n\n", MAX_ATTEMPTS);

    while (attempts < MAX_ATTEMPTS) {
        printf("Essai %d: ", attempts + 1);
        scanf("%5s", guess);
        guess[WORD_LENGTH] = '\0'; // s'assurer que la chaîne est terminée
        to_lowercase(guess);

        if (strlen(guess) != WORD_LENGTH) {
            printf("Le mot doit avoir 5 lettres.\n");
            continue;
        }

        give_feedback(guess, TARGET);
        attempts++;

        if (strcmp(guess, TARGET) == 0) {
            win = 1;
            break;
        }
    }

    if (win) {
        printf("\n Felicitations ! Vous avez trouve le mot '%s' en %d essais.\n", TARGET, attempts);
    } else {
        printf("\n Dommage ! Le mot etait '%s'.\n", TARGET);
    }

    return 0;
}