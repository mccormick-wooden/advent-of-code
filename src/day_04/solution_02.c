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

    while((read = getline(&line, &len, fp)) != -1) {
        int lhlower, lhupper, rhlower, rhupper;

        assert(sscanf(line, "%d-%d,%d-%d", &lhlower, &lhupper, &rhlower, &rhupper) == 4);

        if ((lhupper >= rhlower && lhupper <= rhupper) || (rhupper >= lhlower && rhupper <= lhupper)) {
            solution++;
        }
    }

    printf("solution: %d\n", solution);

    // cleanup
    fclose(fp);
    free(line);
    return EXIT_SUCCESS;
}
