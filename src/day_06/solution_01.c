#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const char* INPUT_FILE_PATH = "input.txt";

int main(void) {
    FILE* fp = NULL;
    char* line = NULL;
    size_t len = 0;
    int solution = 0;
    const int MAGIC_LEN = 4;
    int offset = 0;

    if ((fp = fopen(INPUT_FILE_PATH, "r")) == NULL) {
        fprintf(stderr, "Can't find %s\n", INPUT_FILE_PATH);
        return EXIT_FAILURE;
    }

    getline(&line, &len, fp);

    while (1) {
        char charsSeen[256] = {0};
        int markerFound = 1;
        for (int i = 0; i < MAGIC_LEN; i++) {
            if (charsSeen[(int)line[i+offset]]) {
                markerFound = 0;
                break;
            } else {
                charsSeen[(int)line[i+offset]] = 1;
            }
        }

        if (markerFound) {
            break;
        } else {
            offset++;
        }
    }

    solution = offset + MAGIC_LEN;
    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    return EXIT_SUCCESS;
}
