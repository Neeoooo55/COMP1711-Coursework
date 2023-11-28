#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FitnessDataStruct.h"

// Struct moved to header file

// Define any additional variables here

// Global variables for filename and FITNESS_DATA array
FITNESS_DATA fitness_data_array[100];
char date[11];
char time [6];
char steps[10];

char line_buffer[buffer_size];
char filename[buffer_size];

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
    char choice;

    int count = 0;
    int mean = 0;

    int pos = 0;
    int end_pos = 0;
    int max_count = 0;
    int temp_count = 0;
    int start = 0;
    int end = 0;

    int steps_count = 0;

    while (1) {
        printf("Menu Options:\n");
        printf("A: Specify the filename to be imported\n");                       
        printf("B: Display the total number of records in the file\n");                    
        printf("C: Find the date and time of the timeslot with the fewest steps\n");                 
        printf("D: Find the date and time of the timeslot with the largest number of steps\n");                    
        printf("E: Find the mean step count of all the records in the file\n");       
        printf("F: Find the longest continuous period where the step count is above 500 steps\n");                 
        printf("Q: Quit\n");
        printf("Enter choice: ");

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
                printf("Error: Could not find or open the file.\n");
                return 1;
            } else {
                printf("File successfully loaded.\n");
            }

            // Resets count
            count = 0;

            // Reads each line in the file
            while (fgets(line_buffer, buffer_size, input) != NULL) {
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
            break;

        case 'B':
        case 'b':
            // Returns the total number of records then closes the file.
            printf("Total records: %d\n", count);
            break;

        case 'C':
        case 'c':
            // Resets pos
            pos = 0;
            // Sets the initial step count to the first entry
            steps_count = fitness_data_array[0].steps;

            // Loops through the rest of the entries
            for (int i = 0; i < count; i++) {
                // If the step count of the current entry is lower than stored,
                // replace steps_count and update pos.
                if (fitness_data_array[i].steps <= steps_count) {
                    steps_count = fitness_data_array[i].steps;
                    pos = i;
                }
            }

            // Using pos print out the required information
            printf("Fewest steps: %s %s\n", fitness_data_array[pos].date, fitness_data_array[pos].time);
            break;

        case 'D':
        case 'd':
            // Resets pos
            pos = 0;
            // Sets the initial step count to the first entry
            steps_count = 0;

            // Loops through the rest of the entries
            for (int i = 0; i < count; i++) {
                // If the step count of the current entry is higher than stored,
                // replace steps_count and update pos.
                if (fitness_data_array[i].steps > steps_count) {
                    steps_count = fitness_data_array[i].steps;
                    pos = i;
                }
            }

            // Using pos print out the required information
            printf("Largest steps: %s %s\n", fitness_data_array[pos].date, fitness_data_array[pos].time);
            break;

        case 'E':
        case 'e':
            // Resets Variables
            steps_count = 0;
            mean = 0;
            // Loops through the entries
            for (int i = 0; i < count; i++) {
                // Add each entries step count to mean
                steps_count += fitness_data_array[i].steps;
            }

            // Once we have all the steps added up, divide by count to get the mean.
            mean = (steps_count + count / 2) / count;
            // Prints out the mean.
            printf("Mean step count: %d\n", mean);
            break;
        case 'F':
        case 'f':
            // Resets variables
            pos = 0;
            end_pos = 0;
            max_count = 0;
            temp_count = 0;

            // Loops through all entries
            for (int i = 0; i < count; i++) {
                // If the current steps is greater than 500, 
                // increment the count and update the positions
                if (fitness_data_array[i].steps > 500) {
                    if (temp_count == 0) {
                        pos = i;
                    }
                    temp_count++;
                    end_pos = i;
                // If the current steps is less than 500,
                } else {
                    // Update max_count if temp_count is greater,
                    // then update start and end
                    if (temp_count > max_count) {
                        max_count = temp_count;
                        start = pos;
                        end = end_pos;
                    }
                    // Reset temp_count;
                    temp_count = 0;
                }
            }

            // Print out the results.
            printf("Longest period start: %s %s\n", fitness_data_array[start].date, fitness_data_array[start].time);
            printf("Longest period end: %s %s\n", fitness_data_array[end].date, fitness_data_array[end].time);
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