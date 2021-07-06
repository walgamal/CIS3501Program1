#pragma once

using namespace std;
#include <iostream>
#include <string>
#include <fstream>

#include "AvlTree.h"
#include "BstTree.h"
#include "SplayTree.h"

const int COLS = 3, ROWS = 4;
int operatorArr[ROWS][COLS];

struct node {
	int data;
	node* leftChild;
	node* rightChild;
	//node* parent;
	node* twin;
};

bool isEmpty(fstream& fileInUse) {
	return fileInUse.peek() == fstream::traits_type::eof();
}

void fileTest(fstream& fileInUse, string& fileName) {							//ENSURE OF VALID INPUT, ELSE USE WHILE LOOP!!  
	while (fileInUse.fail()) {
		cout << "ERROR: CANNOT FIND FILE! TRY ENTERING AGAIN: ";
		cin >> fileName;
		fileInUse.open(fileName);
		fileTest(fileInUse, fileName);
	}

	if (isEmpty(fileInUse)) {
		cout << "WARNING: FILE IS EMPTY!\n";
		fileInUse.seekg(0, ios::beg);
	}
}

node* MakeNewNode(int data) {
	node* newNode = new node;
	newNode->data = data;
	newNode->leftChild = newNode->rightChild = newNode->twin = NULL;
	return newNode; 
}

node* findMax(node* root) {				//finds largest node in tree
	if (root->rightChild != NULL) {
		root = root->rightChild;
		findMax(root);
	}
	else {
		return root;
	}
}

int max(int a, int b) {
	if (a > b) { return a; }
	else { return b; }
}

int findHeight(node* root) {
	int leftHeight = 0, rightHeight = 0;

	if (root == NULL) {
		return 0;
	}
	else {
		//Recursively find height of each subtree
		leftHeight = findHeight(root->leftChild);
		rightHeight = findHeight(root->rightChild);
	}

	return max(leftHeight, rightHeight) + 1;			//Add the largest depth and the root node added for height
}

int getBalance(node* AvlRoot) {
	//After insert or delete --> Retrace path back to root
	//If imbalance is found do the proper rotation --> R,L,RR,LL,RL,LR
	if (AvlRoot == NULL) { return 0; }
	return findHeight(AvlRoot->leftChild) - findHeight(AvlRoot->rightChild);
}

node* rightRotation(node* n) {
	node* temp = n->leftChild;
	node* temp2 = temp->rightChild;

	temp->rightChild = n;
	n->leftChild = temp2;

	findHeight(n);
	findHeight(temp);

	return temp;
}

node* leftRotation(node* n) {
	node* temp = n->rightChild;
	node* temp2 = temp->leftChild;

	temp->leftChild = n;
	n->rightChild = temp2;

	findHeight(n);
	findHeight(temp);

	return temp;
}

node* zagRotation(node* n) {		//Zig == left
	node* temp = n->rightChild;
	n->rightChild = temp->leftChild;
	temp->leftChild = n;
	return temp;
}

node* zigRotation(node* n) {		//Zag == right
	node* temp = n->leftChild;
	n->leftChild = temp->rightChild;
	temp->rightChild = n;
	return temp;
}

void countTwins(node* root, int& count) {
	count++;
	if (root->twin != NULL) {
		countTwins(root->twin, count);
	}
}

int getLevelUntil(node* n, int data, int lvl) {
	if (n == NULL) {
		return 0;
	}
	else if (n->data == data) {
		return lvl;
	}

	int dlvl = getLevelUntil(n->leftChild, data, lvl + 1);

	if (dlvl != 0) {
		return dlvl;
	}
	else {
		dlvl = getLevelUntil(n->rightChild, data, lvl + 1);
		return dlvl;
	}
	
}

int getLevel(node* n, int data) {
	return getLevelUntil(n, data, 1);
}

void findParent(node* n, int data, int parent, fstream& fileInUse) {
	if (n == NULL) {
		return;
	}
	else if (n->data == data) {
		if (parent != -1) {
			cout << parent;
		}
		else {
			cout << "No Parent.";
		}
	}
	else {
		findParent(n->leftChild, data, n->data, fileInUse);
		findParent(n->rightChild, data, n->data, fileInUse);
	}
}

void print(node* root, int spaceCount, int spaces, fstream& fileInUse) {
	if (root == NULL){
		return;
	}

	spaces += spaceCount;

	print(root->rightChild, spaceCount, spaces, fileInUse);
	cout << endl;
	fileInUse << endl;
	

	for (int i = spaceCount; i < spaces; i++) {
		cout << " ";
		fileInUse << " ";
	}

	cout << root->data;
	fileInUse << root->data;

	if (root->twin != NULL) {
		int count = 0; 
		countTwins(root, count);
		cout << "(" << count << ")" << endl;
		fileInUse << "(" << count << ")" << endl;
	}

	print(root->leftChild, spaceCount, spaces, fileInUse);
}

void printTree(node* root, fstream& fileInUse) {
	int count = 10;
	print(root, count, 0, fileInUse);
	int TreeHeight = findHeight(root);
	cout << "\n\nHeight: " << TreeHeight - 1 << endl;
	cout << "\n----------------------------------------------------------------------------------------------------------------------------\n";
	
	fileInUse << "\n\nHeight: " << TreeHeight - 1 << endl;
	fileInUse << "\n----------------------------------------------------------------------------------------------------------------------------\n";
}

void printSummary(fstream& summaryFile, string testName) {
	summaryFile << endl << testName;	

	for (int i = 0; i < COLS; i++) {
		summaryFile << "			" << operatorArr[3][i];
	}

}

void printArr(string testName) {

	//TOTALS
	operatorArr[3][0] = operatorArr[0][0] + operatorArr[1][0] + operatorArr[2][0];
	operatorArr[3][1] = operatorArr[0][1] + operatorArr[1][1] + operatorArr[2][1];
	operatorArr[3][2] = operatorArr[0][2] + operatorArr[1][2] + operatorArr[2][2];

	cout << "						" << testName <<
		"\n			BST			AVL			Splay\n";
	
	cout << "Inserts:		"; //1st row;
	for (int i = 0; i < COLS; i++) {
		cout << operatorArr[0][i] << "			";
	}
	cout << endl;

	cout << "Searches:		"; //2nd row;
	for (int i = 0; i < COLS; i++) {
		cout << operatorArr[1][i] << "			";
	}
	cout << endl;

	cout << "Deletes:		"; //3rd row;
	for (int i = 0; i < COLS; i++) {
		cout << operatorArr[2][i] << "			";
	}
	cout << endl;

	cout << "Totals:			"; //4th row;
	for (int i = 0; i < COLS; i++) {
		cout << operatorArr[3][i] << "			";
	}
	cout << "\n----------------------------------------------------------------------------------------------------------------------------\n";
}

void printArrToFiles(fstream& fileInUse, string testName) {
	fileInUse << "						" << testName <<
		"\n			BST			AVL			Splay\n";
	
	fileInUse << "Inserts:		"; //1st row;
	for (int i = 0; i < COLS; i++) {
		fileInUse << operatorArr[0][i] << "			";
	}
	fileInUse << endl;

	fileInUse << "Searches:		"; //2nd row;
	for (int i = 0; i < COLS; i++) {
		fileInUse << operatorArr[1][i] << "			";
	}
	fileInUse << endl;

	fileInUse << "Deletes:		"; //3rd row;
	for (int i = 0; i < COLS; i++) {
		fileInUse << operatorArr[2][i] << "			";
	}
	fileInUse << endl;

	fileInUse << "Totals:			"; //4th row;
	for (int i = 0; i < COLS; i++) {
		fileInUse << operatorArr[3][i] << "			";
	}
	fileInUse << "\n----------------------------------------------------------------------------------------------------------------------------\n";
}

