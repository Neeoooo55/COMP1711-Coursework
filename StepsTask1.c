#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define an appropriate struct
typedef struct {
	char date[11];
	char time[6];
	int steps;
} FITNESS_DATA;

// Define any additional variables here
int count = 0;
char delimiter = ',';
char date[11];
char date_array[3] = {};
char time[6];
char steps[10];

// This is your helper function. Do not change it in any way.
// Inputs: character array representing a row; the delimiter character
// Ouputs: date character array; time character array; steps character array
void tokeniseRecord(const char *input, const char *delimiter, char *date, char *time, char *steps) {
    // Create a copy of the input string as strtok modifies the string
    char *inputCopy = strdup(input);
    
    // Tokenize the copied string
    char *token = strtok(inputCopy, delimiter);
    if (token != NULL) {        
        strcpy(date, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(time, token);
    }
    
    token = strtok(NULL, delimiter);
    if (token != NULL) {
        strcpy(steps, token);
    }
    
    // Free the duplicated string
    free(inputCopy);
}

FILE *open_file(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);

    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    return file;
}

// Complete the main function
int main() {
    char* filename = "FitnessData_2023.csv";
    FILE *file = open_file(filename, "r");

    int buffer_size = 100;
    char line_buffer[buffer_size];

    while (fgets(line_buffer, buffer_size, file) != NULL) {
        count += 1;
    }

    printf("Number of records in file: %d\n", count);

    fclose(file);

    count = 0;

    FILE *file2 = open_file(filename, "r");

    while (fgets(line_buffer, buffer_size, file2) != NULL) {
        if (count < 3) {
            tokeniseRecord(line_buffer, &delimiter, date, time, steps);
            printf("%s/%s/%d\n", date, time, atoi(steps));
        }

        count += 1;
    }

    fclose(file2);
    return 0;
}