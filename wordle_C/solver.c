 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "solver.h"
#include "game.h"

#define MAX_WORDS 10000

char dictionary[MAX_WORDS][WORD_LENGTH + 1];
int word_count = 0;

// Charger le dictionnaire
void load_dictionary(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Erreur : impossible d'ouvrir %s\n", filename);
        exit(1);
    }
    word_count = 0;
    while (fscanf(file, "%5s", dictionary[word_count]) != EOF) {
        to_lowercase(dictionary[word_count]);
        dictionary[word_count][WORD_LENGTH] = '\0';
        word_count++;
        if (word_count >= MAX_WORDS) break;
    }
    fclose(file);
}

// Générer le code feedback (G=vert, Y=jaune, B=gris)
void generate_feedback_code(const char *guess, const char *target, char *feedback) {
    char target_used[WORD_LENGTH] = {0};
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (guess[i] == target[i]) {
            feedback[i] = 'G';
            target_used[i] = 1;
        } else {
            feedback[i] = 'B';
        }
    }

    for (int i = 0; i < WORD_LENGTH; i++) {
        if (feedback[i] == 'B') {
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!target_used[j] && guess[i] == target[j]) {
                    feedback[i] = 'Y';
                    target_used[j] = 1;
                    break;
                }
            }
        }
    }
    feedback[WORD_LENGTH] = '\0';
}

// Vérifier si un mot correspond au feedback
int matches_feedback(const char *word, const char *guess, const char *feedback) {
    int used[WORD_LENGTH] = {0};

    // Verts
    for (int i = 0; i < WORD_LENGTH; i++)
        if (feedback[i] == 'G' && word[i] != guess[i])
            return 0;

    // Jaunes
    for (int i = 0; i < WORD_LENGTH; i++) {
        if (feedback[i] == 'Y') {
            int found = 0;
            for (int j = 0; j < WORD_LENGTH; j++) {
                if (!used[j] && word[j] == guess[i] && i != j) {
                    found = 1;
                    used[j] = 1;
                    break;
                }
            }
            if (!found) return 0;
        } else if (feedback[i] == 'B') { // gris
            for (int j = 0; j < WORD_LENGTH; j++)
                if (word[j] == guess[i])
                    return 0;
        }
    }
    return 1;
}

// Jouer automatiquement
void play_solver() {
    char target[WORD_LENGTH + 1];
    strcpy(target, dictionary[rand() % word_count]);

    char possible[MAX_WORDS][WORD_LENGTH + 1];
    int possible_count = word_count;
    for (int i = 0; i < word_count; i++)
        strcpy(possible[i], dictionary[i]);

    char guess[WORD_LENGTH + 1];
    char feedback[WORD_LENGTH + 1];
    int attempts = 0;

    printf("=== Wordle Solver ===\n");

    while (attempts < MAX_ATTEMPTS) {
        strcpy(guess, possible[0]); // stratégie simple : premier mot possible
        printf("Essai %d: ", attempts + 1);
        give_feedback(guess, target);
        attempts++;

        if (strcmp(guess, target) == 0) {
            printf("\n Solver a trouvé le mot '%s' en %d essais.\n", target, attempts);
            return;
        }

        generate_feedback_code(guess, target, feedback);

        // Filtrer les mots possibles
        int new_count = 0;
        for (int i = 0; i < possible_count; i++)
            if (matches_feedback(possible[i], guess, feedback))
                strcpy(possible[new_count++], possible[i]);
        possible_count = new_count;
    }

    printf("\n Solver n'a pas trouvé le mot '%s'.\n", target);
} 