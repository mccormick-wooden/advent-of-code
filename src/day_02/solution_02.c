#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

const char *INPUT_FILE_PATH = "input.txt";

int main(void) {
    FILE *fp = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;
    int solution = 0;

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    const int YOUR_MOVE_SCORE_ASCII_OFFSET = -64;
    const int WIN_SCORE = 6;
    const int DRAW_SCORE = 3;
    const int LOSS_SCORE = 0;
    int winLossScore = 0;
    const char LOSS_CODE = 'X';
    const char DRAW_CODE = 'Y';
    const char WIN_CODE = 'Z';
    char whoBeatsWho[256] = {0};
    char whoLosesWho[256] = {0};
    whoBeatsWho['A'] = 'C';
    whoBeatsWho['B'] = 'A';
    whoBeatsWho['C'] = 'B';
    whoLosesWho['C'] = 'A';
    whoLosesWho['A'] = 'B';
    whoLosesWho['B'] = 'C';

    while((read = getline(&line, &len, fp)) != -1) {
        char oppMove, moveCode, yourMove;
        assert(sscanf(line, "%c %c", &oppMove, &moveCode) == 2);

        if (moveCode == DRAW_CODE) {
            yourMove = oppMove;
            winLossScore = DRAW_SCORE;
        } else if (moveCode == LOSS_CODE) {
            yourMove = whoBeatsWho[(int)oppMove];
            winLossScore = LOSS_SCORE;
        } else if (moveCode == WIN_CODE) {
            yourMove = whoLosesWho[(int)oppMove];
            winLossScore = WIN_SCORE;
        } else {
            assert(1);
        }

        solution += winLossScore + yourMove + YOUR_MOVE_SCORE_ASCII_OFFSET;
    }

    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    return EXIT_SUCCESS;
}
