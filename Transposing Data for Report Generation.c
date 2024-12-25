#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 100
#define MAX_COLS 100
#define MAX_LENGTH 50

void transpose(char data[MAX_ROWS][MAX_COLS][MAX_LENGTH], int rows, int cols) {
    for (int col = 0; col < cols; col++) {
        for (int row = 0; row < rows; row++) {
            printf("%s", data[row][col]);
            if (row < rows - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main() {
    FILE *file = fopen("employee_data.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char data[MAX_ROWS][MAX_COLS][MAX_LENGTH];
    int rows = 0, cols = 0;

    while (fgets(data[rows][0], MAX_LENGTH, file)) {
        char *token = strtok(data[rows][0], " \n");
        int col = 0;
        while (token != NULL) {
            strncpy(data[rows][col], token, MAX_LENGTH);
            data[rows][col][MAX_LENGTH - 1] = '\0';
            col++;
            token = strtok(NULL, " \n");
        }
        if (rows == 0) {
            cols = col;
        }
        rows++;
    }

    fclose(file);

    transpose(data, rows, cols);

    return 0;
}
