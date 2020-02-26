#include <stdio.h>
#include <stdlib.h>
#include "stMarkList.h"

int main(void) {
	FILE* sessionResults;
	if ((sessionResults = fopen("sessionResults.txt", "rt")) == NULL) {
		perror("Function fope() returned");
		return 0;
	}
	studList* head = (studList*)calloc(1, sizeof(studList));
	if (head == NULL) {
		fputs("Not more memory.", stderr);
		return 0;
	}
	studList* p;
	while (!feof(sessionResults)) {
		p = fillStudent(sessionResults);
		if (p == NULL) return 0;
		//adding new element to correct position
		if (!head->next) addStudent(&head->next, p);
		else {
			studList* temp = head->next, * prev = head;
			while (temp && p->student.birth.year > temp->student.birth.year) {
				prev = temp;
				temp = temp->next;
			}
			while (temp && p->student.birth.year == temp->student.birth.year
				&& p->student.birth.mon > temp->student.birth.mon) {
				prev = temp;
				temp = temp->next;
			}
			while (temp && p->student.birth.year == temp->student.birth.year
				&& p->student.birth.mon == temp->student.birth.mon
				&& p->student.birth.day > temp->student.birth.day) {
				prev = temp;
				temp = temp->next;
			}
			addStudent(&prev->next, p);
		}
	}
	printf("List before deleting elements:\n");
	displayList(head->next);
	studList* prev = head;
	studList* temp = head->next;
	while (temp) {
		_Bool check = 0;
		for (int i = 0; i < MARKSNUMB; ++i) {
			if (temp->student.marks[i] == 2) {
				prev = temp;
				temp = temp->next;
				check = 1;
				break;
			}
		}
		if (check) continue;
		temp = temp->next;
		deleteStudent(prev);
	}
	printf("List after deleting elements:\n");
	displayList(head->next);
	_getch();
	return 0;
}