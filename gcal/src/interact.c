/*
 * Program name: interact.c
 * Purpose: To implment the methods needed to store reminders to the reminders.txt file
 * Author: Willie Leung
 */

#include "interact.h"

void readFile(const char *fileName) { // Function to read from file and reminders to calendar
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n"); // Error if file can't be opened
        exit(1);
    }

    int day = 0;
    char reminder[MAX_STR_LEN];

    while (fscanf(file, " %d ", &day) == 1 && fgets(reminder, sizeof(reminder), file) != NULL) { // Loop to read reminders and insert to calendar
        reminder[strcspn(reminder, "\n")] = 0; // Get rid of new line character at the end
        insertToCalendar(day, reminder);
    }
    
    fclose(file); // Close file
}

void writeFile(const char *fileName) { // Function to write to file
    FILE *file = fopen(fileName, "w"); // Make new file if it doesn't exist

    struct DayNode *day;
    struct ReminderNode *reminder;
    for (day = month.reminderList; day != NULL; day = day->next) { // Loop to write reminders to file
        for (reminder = day->reminders; reminder != NULL; reminder = reminder->next) {
            fprintf(file, "%d %s\n", day->day, reminder->reminder);
        }
    }
    fclose(file); // Close file
}

void flushBuffer(const char *fileName) { // Function to flush buffer
    FILE *file = fopen(fileName, "r"); // Open file and print error message if file can't be opened
    if (file == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    fflush(file); // Flush file
    fclose(file); // Close file
}
