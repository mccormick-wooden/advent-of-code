// --- Part Two ---
// By the time you calculate the answer to the Elves' question, they've already realized that the Elf carrying the most Calories
// of food might eventually run out of snacks.

// To avoid this unacceptable situation, the Elves would instead like to know the total Calories carried by the top three
// Elves carrying the most Calories. That way, even if one of those Elves runs out of snacks, they still have two backups.

// In the example above, the top three Elves are the fourth Elf (with 24000 Calories), then the third Elf (with 11000 Calories),
// then the fifth Elf (with 10000 Calories). The sum of the Calories carried by these three elves is 45000.

// Find the top three Elves carrying the most Calories. How many Calories are those Elves carrying in total?

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
