#include <stdio.h>
#include <stdlib.h>

const char* CALORIE_FILE_PATH = "input.txt";

int main() {
    FILE* fs = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int current_elf_total = 0;
    int most_calories = 0;

    if ((fs = fopen(CALORIE_FILE_PATH, "r")) == NULL) {
        return 1;
    }

    while((read = getline(&line, &len, fs)) != -1) {
        int current_line_value = 0;
        if ((current_line_value = atoi(line)) != 0) {
            current_elf_total += current_line_value;
        } else {
            if (current_elf_total > most_calories) {
                most_calories = current_elf_total;
            }
            current_elf_total = 0;
        }
    }

    printf("best: %d\n", most_calories);
    fclose(fs);
    return 0;
}
