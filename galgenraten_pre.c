#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


void hangman(int rem_tries) {
    switch (rem_tries) {
        case 9:
            printf("\n\n\n\n\n\n____\n\n");
            break;
        case 8:
            printf("\n\n  |\n  |\n  |\n  |\n__|__\n\n");
            break;
        case 7:
            printf("\n  ______\n  |\n  |\n  |\n  |\n__|__\n\n");
            break;
        case 6:
            printf("\n  ______\n  |    |\n  |\n  |\n  |\n__|__\n\n");
            break;
        case 5:
            printf("\n  ______\n  |    |\n  |    0\n  |\n  |\n__|__\n\n");
            break;
        case 4:
            printf("\n  ______\n  |    |\n  |    0\n  |   / \n  |\n__|__\n\n");
            break;
        case 3:
            printf("\n  ______\n  |    |\n  |    0\n  |   / \\ \n  |\n__|__\n\n");
            break;
        case 2:
            printf("\n  ______\n  |    |\n  |    0\n  |   /|\\ \n  |\n__|__\n\n");
            break;
        case 1:
            printf("\n  ______\n  |    |\n  |    0\n  |   /|\\ \n  |   / \n__|__\n\n");
            break;
        case 0:
            printf("\n  ______\n  |    |\n  |    0\n  |   /|\\ \n  |   / \\ \n__|__\n\n");
            break;
    }
    // printf("Verbleibende Versuche: %d\n", rem_tries);
    return;
}


void hangman_winner(char *thestring) {
    printf("WINNER! '%s' ist korrekt.\n\n   |\\---/|\n   | ,_, |\n    \\_`_/-..----.\n ___/ `   ' ,""+ \\  sk\n(__...'   __\\    |`.___.';\n  (_,...'(_,.`__)/'.....+\n\n", thestring);
    return;
}


int main(void) {
    int max_len_word = 30;
    char theword[max_len_word+1], guessed_word[max_len_word+1], c;
    int MAX_VERSUCHE, i = 0, word_len, rem_letters = 0, found;
    printf("Welcome to Hangman, Player 1.");
    printf("\n\n++++++++++++++++++++++++++++++++\n\n");
    printf("SPIELER 1:\n\n");
    printf("Geben sie ihr Wort ein (Maximal %d Zeichen, Bestätigung mit 'ENTER'): ", max_len_word);
    while ((theword[i] = getchar()) != '\n' && i < max_len_word + 1) {
        if (i == max_len_word) {
            printf("ERROR! Eingabe zu lang.\n");
            return 1;
        } else if (!isalpha(theword[i]) && !isspace(theword[i]) && theword[i] != '-') {
            printf("ERROR! Ungültige Eingabe.\n");
            return 1;
        }
        i++;
    }
    theword[i] = '\0';
    word_len = strlen(theword);
    printf("Geben sie die Anzahl der Versuche ein (1 - 20, Bestätigung mit 'Enter'): ");
    scanf("%d", &MAX_VERSUCHE);
    if (MAX_VERSUCHE < 1 || MAX_VERSUCHE > 20) {
        printf("ERROR! Ungültige Eingabe.\n");
        return 1;
    }
    while (getchar() != '\n') {}
    for (i = 0; i < word_len; i++) {
        if (isalpha(theword[i])) {
            guessed_word[i] = '_';
            rem_letters++;
        } else if (theword[i] == '-') {
            guessed_word[i] = '-';
        } else {
            guessed_word[i] = ' ';
        }
    }
    guessed_word[i] = '\0';
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    printf("Welcome to Hangman, Player 2. Scrollen sie nicht hoch und halten sie Fenster und Türen geschlossen.");
    printf("\n\n++++++++++++++++++++++++++++++++\n\n");
    while (rem_letters) {
        if (MAX_VERSUCHE == 0) {
            printf("Sie sind tot, das Spiel ist leider vorbei. Das richtige Wort war '%s'.\n\n", theword);
            hangman(MAX_VERSUCHE);
            return 0;
        } 
        hangman(MAX_VERSUCHE);
        // printf("Verbleibende Buchstaben: %d\n\n", rem_letters);
        // printf("%s  (ihr Fortschritt)\n\n", guessed_word);
        printf("%s\n\n", guessed_word);
        printf("SPIELER 2: \n(beenden sie das Spiel jederzeit mit '1')\n\n");
        printf("Raten sie einen Buchstaben: ");
        scanf("%c", &c);
        if (c == '1') {
            printf("\n\n++++++++++++++++++++++++++++++++\n\n");
            printf("\nFeige Sau.\n");
            system("firefox https://www.youtube.com/watch?v=r5sTTlph2Vk&ab_channel=DerOsterhase"); 
            return 0;
        }
        while (getchar() != '\n') {}
        found = 0;
        for (i = 0; i < word_len; i++) {
            if (toupper(c) == guessed_word[i] || tolower(c) == guessed_word[i] || c == ' ') {
                found = 2;
                break;
            } else {
                if (toupper(c) == theword[i] || tolower(c) == theword[i]) {
                    guessed_word[i] = theword[i];
                    rem_letters--;
                    found = 1;
                } 
            }
        }
        printf("\n\n++++++++++++++++++++++++++++++++\n\n");
        if (found == 0) {
            if (MAX_VERSUCHE > 1) {
                printf("FALSCH!\n\n");
            }
            MAX_VERSUCHE--;
        } else if (found == 2 && MAX_VERSUCHE > 1) {
            printf("Sie sind ein Idiot, diesen Buchstaben hatten sie bereits.\n\n");
            MAX_VERSUCHE--;
        } else {
            if (rem_letters > 0) {
                printf("Richtig!\n\n");
            }   
        }
    }
    hangman_winner(theword);
    return 0;
}
