#include <stdio.h>
#include "stMarkList.h"

void addStudent(studList** prev, studList* thisStud) {
	if (*prev == NULL)
		*prev = thisStud;
	else {
		thisStud->next = *prev;
		*prev = thisStud;
	}
}

void displayList(const studList* first) {
	printf("Last name           |First name          |Birth date|          Marks\n");
	studList* temp = first;
	while (temp) {
		printf("%-20s|%-20s|%02d.%02d.%4d|   ", temp->student.lName, temp->student.fName,
			temp->student.birth.day, temp->student.birth.mon, temp->student.birth.year);
		for (int i = 0; i < MARKSNUMB; ++i) {
			printf("%d ", temp->student.marks[i]);
		}
		putc('\n', stdout);
		temp = temp->next;
	}
}

void deleteStudent(studList* prev) {
	studList* temp = prev->next->next;
	free(prev->next);
	prev->next = temp;
}

studList* fillStudent(FILE* file) {
	studList* p = (studList*)malloc(sizeof(studList));
	if (p == NULL) {
		fputs("Not more memory.", stderr);
		return p;
	}
	if (fscanf(file, "%s %s %d %d %d", p->student.lName, p->student.fName,
		&p->student.birth.day, &p->student.birth.mon, &p->student.birth.year) != 5) {
		fputs("You entered incorrect information.", stderr);
		return NULL;
	}
	for (int i = 0; i < MARKSNUMB; ++i)
		if (fscanf(file, "%d", &p->student.marks[i]) != 1) {
			fputs("You entered incorrect information.", stderr);
			return NULL;
		}
	p->next = NULL;
	return p;
}