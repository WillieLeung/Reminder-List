#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include "reminder.h"

#define MAX_STR_LEN 100

struct DayNode {
    int day;
    bool haveReminder;
    struct ReminderNode *reminders;
    struct DayNode *next;
};

struct ReminderNode {
    char reminder[MAX_STR_LEN];
    struct ReminderNode *next;
};

bool dayExists(struct DayNode *list, int day);
bool reminderExists(struct DayNode *list, int day, char *reminder);
struct DayNode *addNode(struct DayNode *list, int day, char *reminder);
struct DayNode *removeReminder(struct DayNode *list, int day, int index);
void freeAll(struct DayNode *list);
void printReminders(struct DayNode *list, int startDate);
void printRemindersToday(struct DayNode *list, int startDate, int day);


#endif //LINKEDLIST_H

