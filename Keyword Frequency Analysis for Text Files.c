#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to convert a string to lowercase
void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int main(int argc, char *argv[]) {
    // Check for proper command-line arguments
    if (argc != 3) {
        printf("Usage: %s <filename> <keyword>\n", argv[0]);
        return 1;
    }

    char *filename = argv[1];
    char *keyword = argv[2];
    char buffer[1024];
    int count = 0;

    // Open the file
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Convert keyword to lowercase
    toLowerCase(keyword);

    // Read the file line by line
    while (fgets(buffer, sizeof(buffer), file)) {
        // Convert the buffer to lowercase
        toLowerCase(buffer);

        // Search for the keyword in the buffer
        char *pos = buffer;
        while ((pos = strstr(pos, keyword)) != NULL) {
            // Ensure the match is a whole word
            if ((pos == buffer || !isalnum((unsigned char)*(pos - 1))) &&
                !isalnum((unsigned char)*(pos + strlen(keyword)))) {
                count++;
            }
            pos += strlen(keyword);
        }
    }

    fclose(file);

    // Print the result
    printf("The word \"%s\" appears %d time(s).\n", keyword, count);

    return 0;
}
