/* Program: gcal.c
 * Purpose: Main function of program to keep track of reminders
 * Author: Willie Leung
 */

#include "reminder.h"
#include "interact.h"
#include <stdio.h>
#include <signal.h>
#include <time.h>

struct Month month;

void signalHandler(int sig) {
    if (sig == SIGINT) { // If SIGINT occurs print error message, write to file and free all allocated memory
        printf("Program interrupted\nWriting to file...\n");
        writeFile(FILENAME);
        flushBuffer(FILENAME);
        freeAll(month.reminderList);
        exit(0);
    }
    if (sig == SIGTERM) { // If SIGTERM occurs print error message, write to file and free all allocated memory
        printf("Program terminated...\nWriting to file...\n");
        writeFile(FILENAME);
        flushBuffer(FILENAME);
        freeAll(month.reminderList);
        exit(0);
    }
    if (sig == SIGSEGV) { // If SIGSEGV occurs print error message, write to file and free all allocated memory
        printf("Program attempting to access invalid storage\nWriting to file...\n");
        writeFile(FILENAME);
        flushBuffer(FILENAME);
        free(month.reminderList);
        exit(0);
    }
}

int main(int argc, char *argv[]) {
    initializeMonth();
    month.reminderList = NULL;
	
    signal(SIGINT, signalHandler); // Catch signal and call signalHandler
    signal(SIGTERM, signalHandler);
    signal(SIGSEGV, signalHandler);
    
    readFile(FILENAME); // Read saved reminders
    flushBuffer(FILENAME);
	
    if (strcmp(argv[1], "add") == 0 && argc >= 4) { // gcal add...
        int day = atoi(argv[2]); // Get day
        char reminder[MAX_STR_LEN]; // Variable to store reminder
        for (int i = 3; i < argc; i++) { // Get reminder
            if (i == 3){
		strcpy(reminder, argv[i]);
	        strcat(reminder, " ");
	    }
	    else{
	    	strcat(reminder, argv[i]);
            	strcat(reminder, " ");
	    }
        }
        if (day > 0 && day <= month.monthDays){ // Check if day is valid
            insertToCalendar(day, reminder); // Insert reminder and print calendar
            printCalendar(); 
        }else {printf("Invalid day\n");}
    }
    else if (strcmp(argv[1], "remove") == 0 && argc == 4) { // gcal remove...
        int day = atoi(argv[2]); // Get day
        int index = atoi(argv[3]); // Get index
	if (argv[3] == NULL){printf("Invalid arguments\nUsage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");} // Check for invalid arguments
	else {
	    if (day > 0 && day < month.monthDays) { // Check if day is valid
                if (index > 0){
		    removeFromCalendar(day, index); // Remove reminder and print calendat
            	    printCalendar();
	        }else{printf("Invalid arguments\nUsage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");}
            }else {printf("Invalid day\n");}
	}
    }
    else if (strcmp(argv[1], "view") == 0 && argc == 2) {printCalendar();} // gcal view...
    else if (strcmp(argv[1], "today") == 0 && argc == 2) { // gcal today...
        time_t now = time(NULL); // Get current day
        struct tm *time = localtime(&now);
        remindersToday(time->tm_mday); // Print reminders on current day
    }
    else {printf("Invalid arguments\nUsage: ./gcal [view | add <day> <reminder> | remove <day> <index> | today]\n");} // Invalid if not one of the above

    writeFile(FILENAME); // Save reminders to file
    flushBuffer(FILENAME);
    return 0;
}


