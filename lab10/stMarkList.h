#ifndef STMARKLIST_H
#define STMARKLIST_H

#define MARKSNUMB 10

typedef struct studentList {
	struct studentMarks {
		char fName[20], lName[20];
		struct date {
			signed int day, mon, year;
		}birth;
		int marks[MARKSNUMB];
	} student;
	struct studentList* next;
}studList;

//додає новий елемент у правильну позицію у відсортований однозв'язний список
void addToCorrectPos(studList** head, studList* newStud);

//додає новий елемент у однозв'язний список після заданого попереднього елемента
//якщо prev рівне NULL то новий елемент встановиться в голову списку
void addStudent(studList** head, studList* prev, studList* newStud);

//виводить одного студента в заданий потік
void fprintStud(const FILE* outputFile, const studList* thisStud);

//виводить список студентів в заданий потік
void fprintList(const FILE* outputFile, const studList* head);

//повертає вказівник на створений в динамічній пам'ять в яку записана
//інформація з заданого потоку, якщо вказано не правильну кількість даних 
//aбо невистачило пам'яті повертає NULL
studList* fillStudent(const FILE* file);

//повертає вказівник на перший елемент однозв'язного списку
//в який записано всю інформацію про студентів з даного потоку
//якщо вказано не правильну кількість даних aбо невистачило пам'яті повертає NULL
studList* fillList(const FILE* inputFile);

//видаляє елемент однозв'язного списку, який знаходиться після заданого,
//якщо prev рівний NULL то видаляється перший елемент списку
void deleteStudent(studList** head, studList* prev);

//повертає 1 якщо перша дата є старішою
//повертає -1 якщо друга дата є старішою
//повертає 0 якщо дати є однаковими
int dateComparison(const struct date* date1, const struct date* date2);

//виводить двох наймолодших студентів в заданий та стандартний потоки
void printTwoYoungestStudents(const FILE* outputFile, const studList* head);

//видаляє елементи з однозв'язного списку у яких немає оцінки 2
void delStudWithout2(studList** head);

//видаляє елементи з однозв'язного списку у яких немає оцінок 4 або 5
void delStudWithout4and5(studList** head);

//дає користувачу програми вибрати які дії зробити з заданим списком
void chooseAction(const FILE* outputFile, studList** head);

//видаляє список студентів
void deleteList(studList* head);

#endif