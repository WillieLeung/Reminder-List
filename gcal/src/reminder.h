#ifndef REMINDER_H
#define REMINDER_H

#include "linkedList.h"

#define FILENAME "reminders.txt"

struct Month{
    int monthDays;
    int startDay;
    int monthIdx;
    struct DayNode *reminderList;
};

extern struct Month month;

void insertToCalendar(int day, char *value) ;
void removeFromCalendar(int day, int index);
int readReminder(char *str, int n) ;
void printCalendar();
void remindersToday(int day);
void initializeMonth(void);

#endif

