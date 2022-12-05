#include <stdio.h>
#include <stdlib.h>
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
    int winLossScore = DRAW_SCORE;
    char whoBeatsWho[256] = {0};
    char moveTranslations[256] = {0};
    whoBeatsWho['A'] = 'C';
    whoBeatsWho['B'] = 'A';
    whoBeatsWho['C'] = 'B';
    moveTranslations['X'] = 'A';
    moveTranslations['Y'] = 'B';
    moveTranslations['Z'] = 'C';

    while((read = getline(&line, &len, fp)) != -1) {
        char oppMove, yourMove;
        assert(sscanf(line, "%c %c", &oppMove, &yourMove) == 2);

        yourMove = moveTranslations[(int)yourMove];

        if (oppMove == yourMove) {
            winLossScore = DRAW_SCORE;
        } else {
            if (whoBeatsWho[(int)yourMove] == oppMove) {
                winLossScore = WIN_SCORE;
            } else {
                winLossScore = LOSS_SCORE;
            }
        }

        solution += winLossScore + yourMove + YOUR_MOVE_SCORE_ASCII_OFFSET;
    }

    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    return EXIT_SUCCESS;
}
