// --- Day 2: Rock Paper Scissors ---

// The Elves begin to set up camp on the beach. To decide whose tent gets to be closest to the snack storage,
// a giant Rock Paper Scissors tournament is already in progress.

// Rock Paper Scissors is a game between two players. Each game contains many rounds; in each round, the players
// each simultaneously choose one of Rock, Paper, or Scissors using a hand shape. Then, a winner for that round is
// selected: Rock defeats Scissors, Scissors defeats Paper, and Paper defeats Rock. If both players choose the same
// shape, the round instead ends in a draw.

// Appreciative of your help yesterday, one Elf gives you an encrypted strategy guide (your puzzle input) that they
// say will be sure to help you win. "The first column is what your opponent is going to play: A for Rock, B for Paper,
// and C for Scissors. The second column--" Suddenly, the Elf is called away to help with someone's tent.

// The second column, you reason, must be what you should play in response: X for Rock, Y for Paper, and Z for Scissors.
// Winning every time would be suspicious, so the responses must have been carefully chosen.

// The winner of the whole tournament is the player with the highest score. Your total score is the sum of your scores
// for each round. The score for a single round is the score for the shape you selected (1 for Rock, 2 for Paper, and 3
// for Scissors) plus the score for the outcome of the round (0 if you lost, 3 if the round was a draw, and 6 if you won).

// Since you can't be sure if the Elf is trying to help you or trick you, you should calculate the score you would get
// if you were to follow the strategy guide.

// For example, suppose you were given the following strategy guide:

// A Y
// B X
// C Z

// This strategy guide predicts and recommends the following:

//     - In the first round, your opponent will choose Rock (A), and you should choose Paper (Y). This ends in a
//       win for you with a score of 8 (2 because you chose Paper + 6 because you won).
//     - In the second round, your opponent will choose Paper (B), and you should choose Rock (X). This ends in a
//       loss for you with a score of 1 (1 + 0).
//     - The third round is a draw with both players choosing Scissors, giving you a score of 3 + 3 = 6.

// In this example, if you were to follow the strategy guide, you would get a total score of 15 (8 + 1 + 6).

// What would your total score be if everything goes exactly according to your strategy guide?

// A, X = ROCK. Score = 1
// B, Y = PAPER. Score = 2
// C, Z = Scissors. Score = 3

// score = shapeYouChose + outcome
// win = 6, draw = 3, lose = 0

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *INPUT_FILE_PATH = "input.txt";

typedef struct moves {
    int len;
    char *oppMoves;
    char *yourMoves;
} moves_t;

void countLine_itercbk(char *line, int lineNumber, void *returnptr) {
    (*(int*)returnptr)++;
}

void populateMoves_itercbk(char *line, int lineNumber, void *returnptr) {
    moves_t *moves = (moves_t*)returnptr;

    moves->oppMoves[lineNumber] = line[0];

    // normalize
    char normalized = ' ';
    if (line[2] == 'X')
        normalized = 'A';
    else if (line[2] == 'Y')
        normalized = 'B';
    else if (line[2] == 'Z')
        normalized = 'C';
    moves->yourMoves[lineNumber] = normalized;
}

void fileIterator(FILE *fp, void (*callback)(), void *cbkretptr) {
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int lineNumber = 0;

    rewind(fp);
    while((read = getline(&line, &len, fp)) != -1) {
        (*callback)(line, lineNumber, cbkretptr);
        lineNumber++;
    }
    free(line); // gets malloc'd in getline so we have to free
    rewind(fp);
}

int calculateScore(moves_t *theMoves) {
    int totalScore = 0;
    const int YOUR_MOVE_SCORE_ASCII_OFFSET = 64;
    const int WIN_SCORE = 6;
    const int DRAW_SCORE = 3;
    const int LOSS_SCORE = 0;

    for (int i = 0; i < theMoves->len; i++) {

        char oppMove = theMoves->oppMoves[i];
        char yourMove = theMoves->yourMoves[i];
        int yourMoveScore = yourMove - YOUR_MOVE_SCORE_ASCII_OFFSET; // 'A', 'B', 'C' ascii codes = 65, 66, 67

        int winLossScore = DRAW_SCORE;
        switch(oppMove) {
            case 'A':
                switch(yourMove) {
                    case 'B':
                        winLossScore = WIN_SCORE;
                        break;
                    case 'C':
                        winLossScore = LOSS_SCORE;
                        break;
                }
                break;
            case 'B':
                switch(yourMove) {
                    case 'A':
                        winLossScore = LOSS_SCORE;
                        break;
                    case 'C':
                        winLossScore = WIN_SCORE;
                        break;
                }
                break;
            case 'C':
                switch(yourMove) {
                    case 'A':
                        winLossScore = WIN_SCORE;
                        break;
                    case 'B':
                        winLossScore = LOSS_SCORE;
                        break;
                }
                break;
        }

        totalScore = totalScore + winLossScore + yourMoveScore;
    }

    return totalScore;
}

int main() {
    FILE *fp = NULL;
    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL)
        return 1;

    // get file length
    int lineCount = 0;
    fileIterator(fp, &countLine_itercbk, &lineCount);

    // init main data structure to hold moves
    printf("%d\n", lineCount);
    char oppMoves[lineCount];
    char yourMoves[lineCount];
    memset(oppMoves, 0, sizeof lineCount);
    memset(yourMoves, 0, sizeof lineCount);
    moves_t theMoves = {.len = lineCount, .oppMoves = oppMoves, .yourMoves = yourMoves};

    // populate moves data structure
    fileIterator(fp, &populateMoves_itercbk, &theMoves);

    // done
    printf("total score: %d\n", calculateScore(&theMoves));

    // cleanup
    fclose(fp);
    return 0;
}
