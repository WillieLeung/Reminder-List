gcal: gcal.o reminder.o linkedList.o interact.o
	gcc -o gcal gcal.o reminder.o linkedList.o interact.o

gcal.o: gcal.c reminder.h interact.h
	gcc -c gcal.c

reminder.o: reminder.c reminder.h
	gcc -c reminder.c

linkedList.o: linkedList.c linkedList.h
	gcc -c linkedList.c

interact.o: interact.c interact.h
	gcc -c interact.c
