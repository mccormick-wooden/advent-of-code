#include <stdio.h>
#include <stdlib.h>

const char* CALORIE_FILE_PATH = "input.txt";

int main() {
    FILE* fs = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int current_elf_total = 0;
    int most_calories_1 = 0;
    int most_calories_2 = 0;
    int most_calories_3 = 0;

    if ((fs = fopen(CALORIE_FILE_PATH, "r")) == NULL) {
        return 1;
    }

    while((read = getline(&line, &len, fs)) != -1) {
        int current_line_value = 0;
        if ((current_line_value = atoi(line)) != 0) {
            current_elf_total += current_line_value;
        } else {
            if (current_elf_total > most_calories_1) {
                most_calories_3 = most_calories_2;
                most_calories_2 = most_calories_1;
                most_calories_1 = current_elf_total;
            } else if (current_elf_total > most_calories_2) {
                most_calories_3 = most_calories_2;
                most_calories_2 = current_elf_total;
            } else if (current_elf_total > most_calories_3) {
                most_calories_3 = current_elf_total;
            }
            current_elf_total = 0;
        }
    }

    printf("best: %d\n", most_calories_1 + most_calories_2 + most_calories_3);
    fclose(fs);
    return 0;
}
