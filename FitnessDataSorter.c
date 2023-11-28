#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the struct for the fitness data
typedef struct {
    char date[11];
    char time[6];
    int steps;
} FitnessData;

// Global variables for filename and FITNESS_DATA array
FitnessData fitness_data_array[100];
FitnessData temp[1];
char date[11];
char time [6];
char steps[10];

char line_buffer[100];
char filename[100];

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

int main() {
    // Reads the filename inputed by the user then stores it
    printf("Enter filename: ");
    fgets(line_buffer, 100, stdin);
    sscanf(line_buffer, " %s ", filename);

    // Opens the file using fopen
    FILE *input = fopen(filename, "r");

    // If there is an error opening the file, return an error message
    // If there is an error opening the file, return an error message
    if (input == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    int count = 0;

    // Reads each line in the file
    while (fgets(line_buffer, 100, input) != NULL) {
        // Using the tokeniseRecord function, we can split each line from the file into separate variables
        tokeniseRecord(line_buffer, ",", date, time, steps);
        // Now that each section (date, time and steps) are in there own variables, they can be added to the struct
        // Using strcpy to assign a copy of the string into fitness_data_array and not a pointer to the string
        strcpy(fitness_data_array[count].date, date);
        strcpy(fitness_data_array[count].time, time);
        fitness_data_array[count].steps = atoi(steps);

        // Increment Count
        count++;
    }

    // Closes the file.
    fclose(input);

    // To check if there are any gaps in the data
    for (int i = 0; i < count; i++) {
        // Checks if there is a bad date
        if (!strcmp(fitness_data_array[i].date, "")) {
            return 1;
        }
        // Checks if there is a bad time
        if (!strcmp(fitness_data_array[i].time, "")) {
            return 1;
        }
        // Checks if there are no steps
        if (fitness_data_array[i].steps == 0) {
            return 1;
        }
    }

    // Bubblesort to order the data by step count
    for (int i = 0; i <= count - 1; i++) {
        int no_swap = 1;

        // Loops through the data
        for (int j = 0; j <= count - (i + 1); j++) {
            // If two items are in the wrong positions, swap them
            if (fitness_data_array[j].steps < fitness_data_array[j + 1].steps) {
                temp[1] = fitness_data_array[j];
                fitness_data_array[j] = fitness_data_array[j + 1];
                fitness_data_array[j + 1] = temp[1];
                no_swap = 0;
            }
        }
        
        // If not swaps happened on the previous pass, break
        if (no_swap == 1) {
            break;
        }
    }

    // Create a new variable for the tsv filename
    char outputfilename[strlen(filename) + 4];
    strcpy(outputfilename, filename);
    strcat(outputfilename, ".tsv");

    // Create the new file using fopen and "w"
    FILE *file = fopen(outputfilename, "w");

    // If there is an error, exit
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    // Print to the file in the tsv format
    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\t%s\t%d\n",fitness_data_array[i].date, fitness_data_array[i].time, fitness_data_array[i].steps);
    }

    // Close the file
    fclose(file);

    //Output required info
    printf("Data sorted and written to %s\n", outputfilename);
}
