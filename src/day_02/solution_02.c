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

char calculateYourMove(char oppMove, char outcome) {
    char yourMove = '\0';

    switch(outcome) {
        case 'Y': // draw
            yourMove = oppMove;
            break;
        case 'X': // lose
            switch (oppMove)
            {
                case 'A':
                    yourMove = 'C';
                    break;
                case 'B':
                    yourMove = 'A';
                    break;
                case 'C':
                    yourMove = 'B';
                    break;
            }
            break;
        case 'Z': // win
            switch (oppMove)
            {
                case 'A':
                    yourMove = 'B';
                    break;
                case 'B':
                    yourMove = 'C';
                    break;
                case 'C':
                    yourMove = 'A';
                    break;
            }
            break;
    }

    return yourMove;
}

void populateMoves_itercbk(char *line, int lineNumber, void *returnptr) {
    moves_t *moves = (moves_t*)returnptr;

    moves->oppMoves[lineNumber] = line[0];
    moves->yourMoves[lineNumber] = calculateYourMove(line[0], line[2]);
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

int main(void) {
    FILE *fp = NULL;
    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    // get file length
    int lineCount = 0;
    fileIterator(fp, &countLine_itercbk, &lineCount);

    // init main data structure to hold moves
    char oppMoves[lineCount];
    char yourMoves[lineCount];
    memset(oppMoves, 0, sizeof lineCount);
    memset(yourMoves, 0, sizeof lineCount);
    moves_t theMoves = {.len = lineCount, .oppMoves = oppMoves, .yourMoves = yourMoves};

    // populate moves data structure
    fileIterator(fp, &populateMoves_itercbk, &theMoves);

    // done
    printf("solution: %d\n", calculateScore(&theMoves));

    // cleanup
    fclose(fp);
    return EXIT_SUCCESS;
}
