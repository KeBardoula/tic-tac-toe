#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include "tic-tac-toe.h"

// Fonction pour initialiser le plateau
void initializeBoard(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' '; // Initialiser avec des espaces vides
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

// Vérifier si un joueur peut gagner lors du prochain coup
int canWin(char board[3][3], char symbol) {
    // Vérifier les lignes
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == symbol && board[i][1] == symbol && board[i][2] == ' ') return i * 3 + 2;
        if (board[i][0] == symbol && board[i][2] == symbol && board[i][1] == ' ') return i * 3 + 1;
        if (board[i][1] == symbol && board[i][2] == symbol && board[i][0] == ' ') return i * 3;
    }
    // Vérifier les colonnes
    for (int j = 0; j < 3; j++) {
        if (board[0][j] == symbol && board[1][j] == symbol && board[2][j] == ' ') return 6 + j;
        if (board[0][j] == symbol && board[2][j] == symbol && board[1][j] == ' ') return 3 + j;
        if (board[1][j] == symbol && board[2][j] == symbol && board[0][j] == ' ') return j;
    }
    // Vérifier les diagonales
    if (board[0][0] == symbol && board[1][1] == symbol && board[2][2] == ' ') return 8;
    if (board[0][0] == symbol && board[2][2] == symbol && board[1][1] == ' ') return 4;
    if (board[1][1] == symbol && board[2][2] == symbol && board[0][0] == ' ') return 0;

    if (board[0][2] == symbol && board[1][1] == symbol && board[2][0] == ' ') return 6;
    if (board[0][2] == symbol && board[2][0] == symbol && board[1][1] == ' ') return 4;
    if (board[1][1] == symbol && board[2][0] == symbol && board[0][2] == ' ') return 2;

    return -1; // Aucun coup gagnant possible
}

// Déplacement de l'ordinateur avec latence
void computerMove(char board[3][3]) {
    // Introduire une latence pour simuler la réflexion de l'ordinateur
    printf("L'ordinateur réfléchit...\n");
    sleep(2); // Attente de 2 secondes (ajustable)

    // Vérifier si l'ordinateur peut gagner
    int position = canWin(board, COMPUTER_SYMBOL);
    if (position == -1) {
        // Sinon, vérifier si le joueur peut gagner, et bloquer
        position = canWin(board, PLAYER_SYMBOL);
    }
    if (position == -1) {
        // Sinon, jouer aléatoirement
        srand(time(0));

        int emptyPositions[9];
        int emptyCount = 0;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != PLAYER_SYMBOL && board[i][j] != COMPUTER_SYMBOL) {
                    emptyPositions[emptyCount] = i * 3 + j;
                    emptyCount++;
                }
            }
        }

        if (emptyCount > 0) {
            position = emptyPositions[rand() % emptyCount];
        }
    }

    int row = position / 3;
    int col = position % 3;
    board[row][col] = COMPUTER_SYMBOL;
}

// Vérifier si quelqu'un a gagné
int checkWinner(char board[3][3]) {
    // Vérifier les lignes
    for (int i = 0; i < 3; i++) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            return (board[i][0] == PLAYER_SYMBOL) ? 1 : 2;
        }
    }
    // Vérifier les colonnes
    for (int j = 0; j < 3; j++) {
        if (board[0][j] != ' ' && board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            return (board[0][j] == PLAYER_SYMBOL) ? 1 : 2;
        }
    }
    // Vérifier les diagonales
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        return (board[0][0] == PLAYER_SYMBOL) ? 1 : 2;
    }
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
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

        // Tour du joueur
        playerMove(board);
        moves++;
        winner = checkWinner(board);
        if (winner || moves == 9) break;

        // Afficher le plateau après le coup du joueur
        displayBoard(board);

        // Tour de l'ordinateur
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
