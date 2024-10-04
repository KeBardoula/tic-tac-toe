// main.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "tic-tac-toe.h"

// Fonction pour initialiser le plateau
void initializeBoard(char board[3][3]) {
    int k = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = k + '0';
            k++;
        }
    }
}

// Fonction pour afficher le plateau de jeu
void displayBoard(char board[3][3]) {
    system("clear"); // Nettoie le terminal
    printf("\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %c ", board[i][j]);
            if (j < 2) printf("|");
        }
        if (i < 2) printf("\n---|---|---\n");
    }
    printf("\n");
}

// Vérifier si le coup est valide
int isValidMove(char board[3][3], int position) {
    int row = position / 3;
    int col = position % 3;
    return board[row][col] != PLAYER_SYMBOL && board[row][col] != COMPUTER_SYMBOL;
}

// Déplacement du joueur
void playerMove(char board[3][3]) {
    int position;
    do {
        printf("Votre tour ! Entrez une position (0-8) : ");
        scanf("%d", &position);
    } while (position < 0 || position > 8 || !isValidMove(board, position));

    int row = position / 3;
    int col = position % 3;
    board[row][col] = PLAYER_SYMBOL;
}

// Déplacement de l'ordinateur (remplit la première case disponible)
void computerMove(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] != PLAYER_SYMBOL && board[i][j] != COMPUTER_SYMBOL) {
                board[i][j] = COMPUTER_SYMBOL;
                sleep(1); // Pause pour simuler un temps de réflexion
                return;
            }
        }
    }
}

// Vérifier si quelqu'un a gagné
int checkWinner(char board[3][3]) {
    // Vérifier les lignes
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == PLAYER_SYMBOL) ? 1 : 2;
        }
    }
    // Vérifier les colonnes
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return (board[0][j] == PLAYER_SYMBOL) ? 1 : 2;
        }
    }
    // Vérifier les diagonales
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[0][0] == PLAYER_SYMBOL) ? 1 : 2;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        return (board[0][2] == PLAYER_SYMBOL) ? 1 : 2;
    }

    return 0; // Aucun gagnant pour l'instant
}

// Fonction principale du jeu
void playGame() {
    char board[3][3];
    int moves = 0;
    int winner = 0;

    initializeBoard(board);

    while (moves < 9 && winner == 0) {
        displayBoard(board);
        playerMove(board);
        moves++;
        winner = checkWinner(board);
        if (winner || moves == 9) break;

        computerMove(board);
        moves++;
        winner = checkWinner(board);
    }

    displayBoard(board);

    if (winner == 1) {
        printf("Félicitations ! Vous avez gagné !\n");
    } else if (winner == 2) {
        printf("L'ordinateur a gagné. Bonne chance la prochaine fois !\n");
    } else {
        printf("Match nul !\n");
    }
}

int main() {
    playGame();
    return 0;
}
