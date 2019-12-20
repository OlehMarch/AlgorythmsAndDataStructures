// lr_3_aisd.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include <time.h>
using namespace std;
//------------------------------------------------------------------------
struct Tree {
	int value;
	Tree *left;
	Tree *right;
};
//------------------------------------------------------------------------
void output(Tree *u) {
	//фугкция вывода элементов дерева
	if (u) {
		output(u->right);
		cout<<u->value<<" ";;
		output(u->left);
	}
}
//------------------------------------------------------------------------
Tree* addElements(Tree *u, int x) {
	//функция добавления элеметов дерева
	if (u == NULL) {
		u = new Tree;
		u->left = NULL;
		u->right = NULL;
		u->value = x;
		return u;
	}
	if (x < u->value) {
		u->left = addElements(u->left, x);
	}
	else {
		u->right = addElements(u->right, x);
	}
	return u;
}
//------------------------------------------------------------------------
void findElement(Tree *root, int key){
	if (root == NULL) {
		return;
	} 
	findElement(root->left, key);
	if (key == root->value) {
		cout << "\n\nElement found" << endl;
	}
	findElement(root->right, key); 
}
//------------------------------------------------------------------------
void sortTree(Tree *root, Tree *last, int &check) {
	int temp = 0;
	if (root == NULL) {
		return;
	}
	else {
		if (last->value < root->value) {
			temp = root->value;
			root->value = last->value;
			last->value = temp;
			check = 1;
		}
		last = root;
		sortTree(root->left,last, check);
		last = root;
		sortTree(root->right,last, check);
	}
}
//------------------------------------------------------------------------
void _tmain(int argc, _TCHAR* argv[]) {

	Tree *u = new Tree;
	int check = 0;
	int *chk = &check;
	int key = 0;

	u->value = rand() % 100;
	u->left = NULL;
	u->right = NULL;
	for (int i = 0; i < 63; i++) {
		addElements(u, rand() % 100);
	}

	cout<<"Output of the elements of a binary tree:\n\n";
	output(u);

	cout << "\n\nInsert value to find: ";
	cin >> key;

	long t1 = clock();
	findElement(u, key);
	long t2 = clock();

	Tree *last = u;
	do {
		*chk = 0;
		sortTree(u, last, *chk);
	}
	while (*chk != 0);

	cout<<"\n\nOutput of the elements of a tree after JSort:\n\n";
	output(u);

	long t3 = clock();
	findElement(u, key);
	long t4 = clock();

	cout << "\nTime of search in binary tree is: " << t2 - t1;
	cout << "\nTime of search in tree with JSort is: " << t4 - t3;

	cout<<"\n\nPress any key to continue...";
	_getch();
}