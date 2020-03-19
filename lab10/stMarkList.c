#include <stdio.h>
#include <stdlib.h>
#include "stMarkList.h"

//////////////////////////////////////////////////////////////////////////////////////////

void addStudent(studList** head, studList* prev, studList* newStud) 
{
	if (prev == NULL) 
	{
		newStud->next = *head;
		*head = newStud;
	}
	else 
	{
		newStud->next = prev->next;
		prev->next = newStud;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void deleteStudent(studList** head, studList* prev) 
{
	studList* temp;
	if (prev == NULL) 
	{
		temp = *head;
		*head = (*head)->next;
	}
	else 
	{
		temp = prev->next;
		prev->next = temp->next;
	}
	free(temp);
}

//////////////////////////////////////////////////////////////////////////////////////////

void fprintStud(const FILE* outputFile, const studList* thisStud) 
{
	fprintf(outputFile, "%-20s|%-20s|%02d.%02d.%4d|   ", thisStud->student.lName, thisStud->student.fName,
		thisStud->student.birth.day, thisStud->student.birth.mon, thisStud->student.birth.year);
	for (int i = 0; i < MARKSNUMB; ++i) 
	{
		fprintf(outputFile, "%d ", thisStud->student.marks[i]);
	}
	putc('\n', outputFile);
}

//////////////////////////////////////////////////////////////////////////////////////////

void fprintList(const FILE* outputFile, const studList* head) 
{
	fprintf(outputFile, "Last name           |First name          |Birth date|          Marks\n");
	studList* temp = head;
	while (temp) 
	{
		fprintStud(outputFile, temp);
		temp = temp->next;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

studList* fillStudent(const FILE* file) 
{
	studList* p = (studList*)malloc(sizeof(studList));
	if (p == NULL) 
	{
		fputs("Not more memory.", stderr);
		return p;
	}
	if (fscanf(file, "%s %s %d %d %d", p->student.lName, p->student.fName,
		&p->student.birth.day, &p->student.birth.mon, &p->student.birth.year) != 5) 
	{
		fputs("You entered incorrect information.", stderr);
		return NULL;
	}
	for (int i = 0; i < MARKSNUMB; ++i) 
	{
		if (fscanf(file, "%d", &p->student.marks[i]) != 1) 
		{
			fputs("You entered incorrect information.", stderr);
			return NULL;
		}
	}
	p->next = NULL;
	return p;
}

//////////////////////////////////////////////////////////////////////////////////////////

studList* fillList(const FILE* inputFile) 
{
	studList* head = NULL, * p;
	while (!feof(inputFile)) 
	{
		if ((p = fillStudent(inputFile)) == NULL) {
			return NULL;
		}
		addToCorrectPos(&head, p);
	}
	return head;
}

//////////////////////////////////////////////////////////////////////////////////////////

void addToCorrectPos(studList** head, studList* newStud) 
{
	studList* temp = *head, *prev = NULL;
	while (temp && dateComparison(&temp->student.birth, &newStud->student.birth) == 1) 
	{
		prev = temp;
		temp = temp->next;
	}
	addStudent(head, prev, newStud);
}

//////////////////////////////////////////////////////////////////////////////////////////

int dateComparison(const struct date* date1, const struct date* date2) 
{
	if (date2->year > date1->year) 
	{
		return 1; 
	}
	else if (date2->year < date1->year) 
	{
		return -1;
	}
	if (date2->mon > date1->mon) 
	{
		return 1;
	}
	else if (date2->mon < date1->mon) 
	{
		return -1;
	}
	if (date2->day > date1->day) 
	{
		return 1;
	}
	else if (date2->day < date1->day) 
	{
		return -1;
	}
	return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////

void printTwoYoungestStudents(const FILE* outputFile, const studList* head) 
{
	studList* temp = head;
	while (temp->next && temp->next->next) 
	{
		temp = temp->next;
	}
	printf("Two youngest students:\n");
	fprintf(outputFile, "Two youngest students:\n");
	fprintList(stdout, temp);
	fprintList(outputFile, temp);
}

//////////////////////////////////////////////////////////////////////////////////////////

void delStudWithout2(studList** head) 
{
	studList* prev = NULL, * temp = *head;
	while (temp) {
		_Bool check = 0;
		for (int i = 0; i < MARKSNUMB; ++i) 
		{
			if (temp->student.marks[i] == 2) 
			{
				prev = temp;
				temp = temp->next;
				check = 1;
				break;
			}
		}
		if (!check) {
			temp = temp->next;
			deleteStudent(head, prev);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void delStudWithout4and5(studList** head) 
{
	studList* prev = NULL, * temp = *head;
	while (temp) 
	{
		_Bool check = 0;
		for (int i = 0; i < MARKSNUMB; ++i) 
		{
			if (temp->student.marks[i] == 4 || temp->student.marks[i] == 5) 
			{
				prev = temp;
				temp = temp->next;
				check = 1;
				break;
			}
		}
		if (!check) 
		{
			temp = temp->next;
			deleteStudent(head, prev);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void chooseAction(const FILE* outputFile, studList** head) 
{
	printf("Enter 1 for print delite students who have marks 4 and 5 in exams\n");
	printf("Enter 2 for print two youngest students\n");
	printf("Enter 3 for print a list of students who have not mark 2 in the exam\n");
	printf("Enter 4 for save\n");
	int numb;
	while (1) 
	{
		scanf("%d", &numb);
		_Bool check = 0;
		switch (numb)
		{
		case 1:
			delStudWithout4and5(head);
			fprintList(stdout, *head);
			fprintList(outputFile, *head);
			break;
		case 2:
			printTwoYoungestStudents(outputFile, *head);
			break;
		case 3:
			delStudWithout2(head);
			fprintList(stdout, *head);
			fprintList(outputFile, *head);
			break;
		case 4:
			check = 1;
			fprintList(outputFile, *head);
			break;
		default:
			printf("You enter incorrect information. Try again.\n");
		}
		if (check) 
		{
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////

void deleteList(studList** head)
{
	studList* temp;
	while (*head) 
	{
		temp = (*head)->next;
		free(*head);
		*head = temp;
	}
	
}

//////////////////////////////////////////////////////////////////////////////////////////