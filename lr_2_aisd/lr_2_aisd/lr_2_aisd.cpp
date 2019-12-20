// lr_2_aisd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include "time.h"

using namespace std;
//---------------------------------------------------------------------
struct List{
	int value;
	bool boolean;
	List* next;
};
//---------------------------------------------------------------------
struct Stack{
	int value;
};
//---------------------------------------------------------------------
void Print(List *u) {
	//функция вывода элементов списка
	int i = 0;
	printf("\nList:\n");
	while(u) {
		printf("%d: %d\n", ++i, u->value);
		u = u->next;
	}
}
//---------------------------------------------------------------------
List* addB(int x, List *u) {
	//функция которая добавляет в начало списка новые элементы
	List *t = new List;
	t->next = u;
	t->boolean = true;
	t->value = x;
	return t;
}
//---------------------------------------------------------------------
List* sortByPasteMethod(List *u, Stack *stack) {
	//сортировка методом вставки с использованием стека
	List *begin = u;
	while ((u->value <= u->next->value) && (u->next->boolean != false)) {
		u = u->next;
	}
	stack->value = u->next->value;
	List *dataToSort = u->next;
	u = begin;
	while (stack->value > u->value) {
		u = u->next;
	}
	int temp = 0;
	while (u != dataToSort) {
		temp = u->value;
		u->value = stack->value;
		stack->value = temp;
		u = u->next;
	}
	u->value = stack->value;
	return begin;
}
//---------------------------------------------------------------------
List* sortByBitwiseMethod(List *l, int t = 2) {
	//  t - разрядность (максимальная длина числа) 
	int i, j, d, m = 1;
	List *temp, /**out,*/ *head[10], *tail[10];
	/*out=l;*/

	for (j = 1; j <= t; j++) { 
		for (i = 0; i <= 9; i++)
			head[i] = (tail[i] = NULL);
		while (l != NULL ) {
			d = ((int)(l->value / m)) % (int)10;
			temp = tail[d];
			if (head[d] == NULL) head[d] = l;
			else temp->next = l;
			temp = tail[d] = l;
			l = l->next;
			temp->next = NULL;
		}
		for (i = 0; i <= 9; i++)
			if (head[i] != NULL) break;
		l = head[i];
		temp = tail[i];
		for (d = i + 1; d <= 9; d++) {
			if (head[d] != NULL) { 
				temp->next = head[d];
				temp = tail[d];
			}
		}
		m *= 10;
	}
	return l;
}
//---------------------------------------------------------------------
void _tmain(int argc, _TCHAR* argv[]) {

	List *list = new List;
	list->value = rand() % 100;
	list->next = NULL;
	list->boolean = false;
	int var = 12;
	int x = 0;
	int choice = 0;
	double since, now;

	cout<<"Insert your number of variant: ";
	cin>>var;

	for (int i = 1; i < (40 + 2 * var); i++) {
		x = rand() % 100;
		list = addB(x, list);
		x = NULL;
	}

	cout<<"Insert sort type:\n	1. By Paste Method;\n	2. By Bitwise Method;\nYour choice: ";
	cin>>choice;

	since = clock();
	switch(choice) {
		case 1: {
			Stack *stack = new Stack;
			stack->value = NULL;
			Print(list);
			List *begin = list;
			sortByPasteMethod(list, stack);
			for (int i = 0; i < (40 + 2 * var); i++) {
				while ((list->value < list->next->value) & (list->next->boolean != false)) {
					list =  list->next;		
				}
				if (list->next->boolean == false) {
					break;
				}
				sortByPasteMethod(begin, stack);
				list = begin;
			}
			list = begin;
			sortByPasteMethod(begin, stack);
			Print(list);
			begin = NULL;
			stack = NULL;
			delete stack;
			break;
		}
		case 2: {
			Print(list);
			list = sortByBitwiseMethod(list);
			Print(list);
			break;
		}
	}
	now = clock() - since;

	cout<<endl<<endl<<now<<endl<<endl;

	list = NULL;
	delete list;

	cout<<"\nPress any key to continue...";
	_getch();
}