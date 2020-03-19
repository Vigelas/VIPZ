#include <stdio.h>
#include <stdlib.h>
#include "stMarkList.h"

int main(void) 
{
	FILE* sessionResults, * outputTable;
	if ((sessionResults = fopen("sessionResults.txt", "rt")) == NULL) 
	{
		perror("Function fopen() returned");
		return 0;
	}
	if ((outputTable = fopen("outputTable.txt", "wt")) == NULL) 
	{
		perror("Function fopen() returned");
		return 0;
	}
	studList* head = fillList(sessionResults);
	if (head == NULL) 
	{
		return 0;
	}
	printf("You'r sorted list:\n");
	fprintList(stdout, head);
	chooseAction(outputTable, &head);
	deleteList(&head);
	fclose(sessionResults);
	fclose(outputTable);
	_getch();
	return 0;
}