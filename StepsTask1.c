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
FITNESS_DATA fitness_data_array[4] = {};
char date[11];
char time [6];
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

// Function to open the file
FILE *open_file(char *filename, char *mode) {
    FILE *file = fopen(filename, mode);

    // If there is an error opening the file, return an error message
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Else return the opened file
    return file;
}

// Complete the main function
int main() {
    // Declare the file name
    char* filename = "FitnessData_2023.csv";

    // Opens the file using the function above
    FILE *file = open_file(filename, "r");

    int buffer_size = 100;
    char line_buffer[buffer_size];

    // Reads each line in the file
    while (fgets(line_buffer, buffer_size, file) != NULL) {
        
        // Since we only want the first 3 lines, we only split up the first three lines and store them
        // into separate variables, date, time and steps.
        if (count < 3) {
            // Using the tokeniseRecord function, we can split each line from the file into separate variables
            tokeniseRecord(line_buffer, ",", date, time, steps);
            // Now that each section (date, time and steps) are in there own variables, they can be added to the struct
            // Using strcpy to assign a copy of the string into fitness_data_array and not a pointer to the string
            strcpy(fitness_data_array[count].date, date);
            strcpy(fitness_data_array[count].time, time);
            fitness_data_array[count].steps = atoi(steps);
        }

        // Increment count
        count += 1;
    }

    // Print out the number of records in the file using count
    printf("Number of records in file: %d\n", count);
    
    // Using a for loop to print out the first three lines in the specified format
    for (int i = 0; i < 3; i++) {
        printf("%s/%s/%d\n", fitness_data_array[i].date, fitness_data_array[i].time, fitness_data_array[i].steps);
    }

    // Close the file
    fclose(file);

    return 0;
}