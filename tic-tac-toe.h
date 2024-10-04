// tic-tac-toe.h

#ifndef TIC_TAC_TOE_H
#define TIC_TAC_TOE_H

// Prototypes des fonctions
void initializeBoard(char board[3][3]);
void displayBoard(char board[3][3]);
int isValidMove(char board[3][3], int position);
void playerMove(char board[3][3]);
void computerMove(char board[3][3]);
int checkWinner(char board[3][3]);
void playGame();

// Constantes
#define PLAYER_SYMBOL 'X'
#define COMPUTER_SYMBOL 'O'

#endif
