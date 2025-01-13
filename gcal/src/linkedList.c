/*
 * Program name: linkedList.c
 * Purpose: To implment the methods needed store multiple reminders for each day and to print all reminders
 * Author: Willie Leung
 */

#include "linkedList.h"

bool dayExists(struct DayNode *list, int day) { // Function to check of day is already in the list
    for (struct DayNode *p = list; p != NULL; p = p->next){if (p->day == day) {return true;}}
    return false;
}

bool reminderExists(struct DayNode *list, int day, char *reminder) { // Function to check if reminder on given day exists
    struct DayNode *p;
    for (p = list; p != NULL && p->day != day; p = p->next){}
    if (p == NULL) {return false;}
    for (struct ReminderNode *q = p->reminders; q != NULL; q = q->next) {
        if (strcmp(q->reminder, reminder) == 0) {return true;}
    }
    return false;
}

struct DayNode *addNode(struct DayNode *list, int day, char *reminder){ // Function to add node to an ordered list
    if (dayExists(list, day) == false && reminderExists(list, day, reminder) == false) { // If day and reminder are not in the list
        struct DayNode *newDayNode = malloc(sizeof(struct DayNode)); // Create new Day and Reminder nodes
        struct ReminderNode *newReminderNode = malloc(sizeof(struct ReminderNode));
        newDayNode->day = day; // Initalize Day and Reminder nodes with their corresponding values
        strcpy(newReminderNode->reminder, reminder);
        newReminderNode->next = NULL;
        newDayNode->reminders = newReminderNode;
        newDayNode->haveReminder = 1;
        newDayNode->next = NULL;

        struct DayNode *prev, *cur;
        for(prev = NULL, cur = list; cur != NULL && (newDayNode->day > cur->day); prev = cur, cur = cur->next) {}

        if (cur == NULL) { // Add to end of list
            if (prev == NULL) {list = newDayNode;}
            else {prev->next = newDayNode;}
        }
        else {
            if (prev != NULL) { // Add to middle of list
                prev->next = newDayNode;
                newDayNode->next = cur;
            }
            else { // Add to front of list
                newDayNode->next = cur;
                list = newDayNode;
            }
        }
        return list;
    }
    else if (dayExists(list, day) == true && reminderExists(list, day, reminder) == false) { // If reminder is not in the list but day is 
        struct ReminderNode *newReminderNode = malloc(sizeof(struct ReminderNode)); // Create new reminder node and set it's next pointer to NULL 
        strcpy(newReminderNode->reminder, reminder);
	newReminderNode->next = NULL;
        for (struct DayNode *p = list; p != NULL; p = p->next) { // Go through days 
            if (p->day == day) { 
		struct ReminderNode *prev, *cur;
		for (prev = NULL, cur = p->reminders; cur != NULL; prev = cur, cur = cur->next) {} // Go through reminders
		if (cur == NULL) { // Add to end or front (if first reminder)
		    if (prev == NULL){p->reminders = newReminderNode;}
		    else{prev->next = newReminderNode;}
		}
                return list;
            }
        }
    }
    return NULL; // Return null if node is already in the list
}

struct DayNode *removeReminder(struct DayNode *list, int day, int index) { // Function to remove reminder of a given day
    if (dayExists(list, day) == false) {return NULL;}
    for (struct DayNode *p = list; p != NULL; p = p->next) { // Go through days
        if (p->day == day) {
            int indexCounter = 1;
            struct ReminderNode *prev, *cur;
            for (prev = NULL, cur = p->reminders; cur != NULL && (indexCounter < index); prev = cur, cur = cur->next) {indexCounter++;} // Go through reminders
            if (prev == NULL && indexCounter == index) { // Remove front
		    p->reminders = cur->next;
		    p->haveReminder = 0;
	    } 
            else if (cur == NULL && indexCounter == index) {prev->next = NULL;} // Remove end
            else {if (indexCounter == index) prev->next = cur->next;} // Remove middle
        }
    }
    return list;
}

void printReminders(struct DayNode *list, int startDate) { // Function to format and print list of reminders
    char *daysOfWeek[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"}; 
    for (struct DayNode *p = list; p != NULL; p = p->next) {
        if (p->haveReminder) {
            int reminderCounter = 1;
            printf("%s %d:", daysOfWeek[((p->day + startDate - 2) % 7)],p->day);
            for (struct ReminderNode *q = p->reminders; q != NULL; q = q->next) {
                if (reminderCounter == 1) {
                    if (p->day < 10){printf("  (%d) %s\n", reminderCounter, q->reminder);}
                    else {printf(" (%d) %s\n", reminderCounter, q->reminder);}
                    reminderCounter++;
                }
                else {
                    if (p->day < 10) {printf("        (%d) %s\n", reminderCounter, q->reminder);}
                    else {printf("        (%d) %s\n", reminderCounter, q->reminder);}
                    reminderCounter++;
                }
            }
        }
    }
}

void printRemindersToday(struct DayNode *list, int startDate, int day) { // Function to format and print list of reminders on a given day
    char *daysOfWeek[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    for (struct DayNode *p = list; p != NULL; p = p->next) {
        if (p->haveReminder && p->day == day) {
            int reminderCounter = 1;
            printf("%s %d:", daysOfWeek[((p->day + startDate - 2) % 7)],p->day);
            for (struct ReminderNode *q = p->reminders; q != NULL; q = q->next) {
                if (reminderCounter == 1) {
                    if (p->day < 10){printf("  (%d) %s\n", reminderCounter, q->reminder);}
                    else {printf(" (%d) %s\n", reminderCounter, q->reminder);}
                    reminderCounter++;
                }
                else {
                    if (p->day < 10) {printf("        (%d) %s\n", reminderCounter, q->reminder);}
                    else {printf("        (%d) %s\n", reminderCounter, q->reminder);}
                    reminderCounter++;
                }
            }
        }
    }
}

void freeAll(struct DayNode *list) {free(list);} // Function to deallocate list
