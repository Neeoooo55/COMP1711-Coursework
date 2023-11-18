#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here

// Global variables for filename and FITNESS_DATA array


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

// Complete the main function
int main() {
    // array of daily readings
    FITNESS_DATA fitness_data_array[100];
    char date[11];
    char time [6];
    char steps[10];

    char line_buffer[buffer_size];
    char filename[buffer_size];

    char choice;
    int count = 0;
    float mean = 0;

    while (1) {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");                       
        printf("B: Display the total number of records in the file\n");                    
        printf("C: Find the date and time of the timeslot with the fewest steps\n");                 
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");                    
        printf("E: Find the mean step count of all the records in the file\n");       
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");                 
        printf("Q: Quit\n");

        // Get the next character typed in and store in the 'choice'
        choice = getchar();

        // This gets rid of the newline character which the user will enter
        // as otherwise this will stay in the stdin and be read next time
        while (getchar() != '\n');

        // Switch statement to control the menu.
        switch (choice) {
        case 'A':
        case 'a':
            // Reads the filename inputed by the user then stores it in filename
            printf("Input filename: ");
            fgets(line_buffer, buffer_size, stdin);
            sscanf(line_buffer, " %s ", filename);

            // Opens the file using fopen
            FILE *input = fopen(filename, "r");

            // If there is an error opening the file, return an error message
            if (!input) {
                printf("Error: Could not find or open the file\n");
                return 1;
            } else {
                printf("File successfully loaded.\n");
            }

            fclose(input);
            break;

        case 'B':
        case 'b':
            fopen(filename, "r");
            // Set count to 0 so that everytime a new file is chosen,
            // the count starts from the beginning.
            count = 0;

            // Reads each line in the file, then increments count
            // if the lines is not blank.
            while (fgets(line_buffer, buffer_size, input) != NULL) {
                count += 1;
            }   

            // Returns the total number of records then closes the file.
            printf("Total records: %d\n", count);

            fclose(input);
            break;

        case 'C':
        case 'c':
            return 0;
            break;

        case 'D':
        case 'd':
            return 0;
            break;

        case 'E':
        case 'e':
            fopen(filename, "r");
            count = 0;

            while (fgets(line_buffer, buffer_size, input) != NULL) {
                // Using the tokeniseRecord function, we can split
                // each line from the file into separate variables
                tokeniseRecord(line_buffer, ",", date, time, steps);
                
                mean += atoi(steps);

                // Increment count
                count += 1;
            }

            mean /= count;
            printf("Mean step count: %f\n", mean);

            fclose(input);
            break;

        case 'F':
        case 'f':
            return 0;
            break;

        case 'Q':
        case 'q':
            return 0;
            break;

        // if they type anything else:
        default:
            printf("Invalid choice. Try again.\n");
            break;
        }
    }
}