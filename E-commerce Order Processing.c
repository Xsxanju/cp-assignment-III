#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ORDERS 1000
#define CITY_CODE_LENGTH 4

int main() {
    // Open the file
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Variables to store orders and city counts
    char orders[MAX_ORDERS][CITY_CODE_LENGTH];
    int city_count[MAX_ORDERS] = {0};
    char city_codes[MAX_ORDERS][CITY_CODE_LENGTH];
    int city_index = 0;
    char buffer[1024];

    // Read the file into a buffer
    if (fgets(buffer, sizeof(buffer), file) == NULL) {
        perror("Error reading file");
        fclose(file);
        return 1;
    }
    fclose(file);

    // Tokenize the input by commas to extract order IDs
    char *token = strtok(buffer, ", ");
    int order_count = 0;

    while (token != NULL && order_count < MAX_ORDERS) {
        strncpy(orders[order_count++], token, CITY_CODE_LENGTH - 1);
        orders[order_count - 1][CITY_CODE_LENGTH - 1] = '\0';
        token = strtok(NULL, ", ");
    }

    // Count city occurrences
    for (int i = 0; i < order_count; i++) {
        char city_code[CITY_CODE_LENGTH];
        strncpy(city_code, orders[i], CITY_CODE_LENGTH - 1);
        city_code[CITY_CODE_LENGTH - 1] = '\0';

        // Check if city code already exists
        int found = 0;
        for (int j = 0; j < city_index; j++) {
            if (strcmp(city_codes[j], city_code) == 0) {
                city_count[j]++;
                found = 1;
                if (city_count[j] == 5) {
                    printf("%s\n", city_code);
                    return 0;
                }
                break;
            }
        }

        // If city code is new, add it to city_codes
        if (!found) {
            strcpy(city_codes[city_index], city_code);
            city_count[city_index]++;
            if (city_count[city_index] == 5) {
                printf("%s\n", city_code);
                return 0;
            }
            city_index++;
        }
    }

    // If no city completes 5 orders, print -1
    printf("-1\n");
    return 0;
}
