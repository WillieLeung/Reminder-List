/*
 * Program name: reminder.c
 * Purpose: To implment the methods needed to keep track of reminders for a month
 * Author: Willie Leung
 */

#include "reminder.h"

void insertToCalendar(int day, char *value) // Function to insert reminder into calendar
{
    struct DayNode *checkError = addNode(month.reminderList, day, value);

    if (checkError == NULL) {printf("Day and reminder already in the list\n");} // Check if day and reminder are in the list already
    else {month.reminderList = checkError;}
}

void removeFromCalendar(int day, int index) // Function to remove calendar
{
    char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    struct DayNode *checkError = removeReminder(month.reminderList, day, index);

    if (checkError == NULL) {printf("Reminder on %s %d does not exist in the list\n", months[month.monthIdx], day);} // If reminder does not exist in given day print error message
    else {month.reminderList = checkError;}
}

int readReminder(char *str, int n) { // Function to read reminder
    int ch, i = 0, dayCounter = 0; // Initialize length of characters read
    char day[n];
    while (isspace(ch = getchar())) // Skip all preceding white space
        ;
    while (ch != ' ') { // Loop to get day
        day[dayCounter++] = ch;
        ch = getchar();
        if (ch == '\n') {
            if (day[0] == '0'){return 0;} // If zero is entered to quit
            return 100; // If reminder with no day is enter or day with no reminder is entered then set day to be invalid
        }
    }
    day[dayCounter] = '\0'; // Manually add null character
    while (isspace(ch = getchar())) // Skip all preceding white space
        ;
    while (ch != '\n' && ch != EOF) { // Loop to store characters in given string
        if (i < n){str[i++] = ch;}
        ch = getchar();
    }
    str[i] = '\0'; // Manually add null character
    return atoi(day);
}

void printCalendar() { // Function to print calendar
    char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    printf("Sun  Mon  Tue  Wed  Thu  Fri  Sat\n");
    for (int i = 1; i <= month.monthDays; i++) //Loop to print the numbers on the calendar and format the calendar
    {
        if (i == 1){for (int j = 1; j < month.startDay; j++){printf("     ");}} //Loop to print blanks spaces before the start date
        if (i < 10) { // Formats single digit days

            if (dayExists(month.reminderList, i)) {
                for (struct DayNode *p = month.reminderList; p != NULL; p = p->next) {
                    if (p->day == i && p->haveReminder == true) {printf("(%d)  ", i);}
                }
            }
            else {printf("%d    ", i);}
        }
        else { // Formats 2 digit days

            if (dayExists(month.reminderList, i)) {
                for (struct DayNode *p = month.reminderList; p != NULL; p = p->next) {
                    if (p->day == i && p->haveReminder == true) {printf("(%d) ", i);}
                }
            }
            else {printf("%d   ", i);}
        }
        if ((i + month.startDay - 1) % 7 == 0){printf("\n");} // Determines when to use new line
    }
    printf("\n________________________________\n"); // Print all reminders
    printf("%s Reminders:\n", months[month.monthIdx]);
    printReminders(month.reminderList, month.startDay);
    printf("\n");
}

void remindersToday(int day) { // Function to print reminders on a given day
    char *months[12] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    if (dayExists(month.reminderList, day) == false ) {printf("No reminders exist for this day\n");} // Error message if day doesn't have reminders
    else {
        printf("Reminders for %s %d:\n", months[month.monthIdx], day);
        printRemindersToday(month.reminderList, month.startDay, day);
    }
}

void initializeMonth(void){ // Function to initialize number of days in month and start day of month
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    month.monthIdx = t->tm_mon;

    t->tm_mday = 1;
    mktime(t);
    month.startDay = t->tm_wday + 1;

    month.monthDays = t->tm_mday;
    while (t->tm_mon == month.monthIdx){
        month.monthDays = t->tm_mday;
        t->tm_mday++;
        mktime(t);
    }
}

