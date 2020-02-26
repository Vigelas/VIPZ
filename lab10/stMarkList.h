#ifndef STMARKLIST_H
#define STMARKLIST_H

#define MARKSNUMB 10

typedef struct studentList {
	struct studentMarks {
		char fName[20], lName[20];
		struct date {
			int day, mon, year;
		}birth;
		int marks[MARKSNUMB];
	} student;
	struct studentList* next;
}studList;

void addStudent(studList** prev, studList* thisStud);
void displayList(const studList* head);
void deleteStudent(studList* prev);
studList* fillStudent(FILE* file);

#endif