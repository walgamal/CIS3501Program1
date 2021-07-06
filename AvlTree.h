#pragma once
#include "BstTree.h"
#include "SplayTree.h"
#include "Trees.h"

node* AvlInsert(node* AvlRoot, int data, fstream& AVLFile) {
	//if empty, create node
	//else, do comparisons to find empty node (left is less, right is more)
	//else if equal, add to twin chain
	//If needed, re-balance

	operatorArr[0][1]++;

	if (AvlRoot == NULL) {								//if empty, create node
		AvlRoot = MakeNewNode(data);
	}
	else if (data < AvlRoot->data) {					//else, do comparisons to find empty node (left is less, right is more)
		AvlRoot->leftChild = AvlInsert(AvlRoot->leftChild, data, AVLFile);
	}
	else if (data > AvlRoot->data) {
		AvlRoot->rightChild = AvlInsert(AvlRoot->rightChild, data, AVLFile);
	}
	else {												//else if equal, add to twin chain
		AvlRoot->twin = AvlInsert(AvlRoot->twin, data, AVLFile);
	}

	int balanceFactor = getBalance(AvlRoot);			//Calculates balance factor

	//Rotations
	//R & RR Cases
	if (balanceFactor > 1 && data < AvlRoot->leftChild->data) {
		cout << "Right Rotation -- ";
		AVLFile << "Right Rotation -- ";
		return rightRotation(AvlRoot);
	}
	//L & LL Cases
	if (balanceFactor < -1 && data > AvlRoot->rightChild->data) {
		cout << "Left Rotation -- ";
		AVLFile << "Left Rotation -- ";
		return leftRotation(AvlRoot);
	}
	//LR Case
	if (balanceFactor > 1 && data > AvlRoot->leftChild->data) {
		cout << "Left-Right Rotation -- ";
		AVLFile << "Left-Right Rotation -- ";
		AvlRoot->leftChild = leftRotation(AvlRoot->leftChild);
		return rightRotation(AvlRoot);
	}
	//RL Case
	if (balanceFactor < -1 && data < AvlRoot->rightChild->data) {
		cout << "Right-Left Rotation -- ";
		AVLFile << "Right-Left Rotation -- ";
		AvlRoot->rightChild = rightRotation(AvlRoot->rightChild);
		return leftRotation(AvlRoot);
	}
	
	return AvlRoot;
}

bool AvlSearch(node* AvlRoot, int keyData) {
	//make comparisons and match to search
	//if found, return level and parent of node 
	//if not found, return error

	operatorArr[1][1]++;

	if (AvlRoot == NULL) {
		return false;
	}
	else if (AvlRoot->data == keyData) {				//check if at root
		return true;
	}
	else if (keyData < AvlRoot->data) {					//checks left child
		AvlSearch(AvlRoot->leftChild, keyData);
		return true;
	}
	else if (keyData > AvlRoot->data) {					//checks right child
		AvlSearch(AvlRoot->rightChild, keyData);
		return true;
	}
	else {
		return false;
	}
}

node* AvlDelete(node* AvlRoot, int keyData, fstream& AVLFile) {
	//search
	//if found, delete --> then take appropiate deletion method
	//if not found, return error
	//If needed, re-balance

	operatorArr[2][1]++;

	if (AvlRoot == NULL) {
		return AvlRoot;
	}
	else if (keyData < AvlRoot->data) {
		AvlRoot->leftChild = AvlDelete(AvlRoot->leftChild, keyData, AVLFile);
	}
	else if (keyData > AvlRoot->data) {
		AvlRoot->rightChild = AvlDelete(AvlRoot->rightChild, keyData, AVLFile);
	}
	else if (keyData == AvlRoot->data) {
		//found, delete --> then take appropiate deletion method(Leaf, 1 child, or 2 children)
		if (AvlRoot->leftChild == NULL && AvlRoot->rightChild == NULL) { //NO children
			delete AvlRoot;
			AvlRoot = NULL;
		}
		else if (AvlRoot->twin != NULL) {								//IF THERES A TWIN
			node* prev = AvlRoot;
			while (prev->twin->twin != NULL) {							//Traverse Link List
				prev = prev->twin;
				prev = AvlRoot->twin;									//Keep track of previous node
			}
			delete prev->twin;
			prev->twin = NULL;
		}
		else if (AvlRoot->leftChild == NULL) {							//ONE child (right)
			node* temp = AvlRoot;
			AvlRoot = AvlRoot->rightChild;
			delete temp;
			temp = NULL;
		}
		else if (AvlRoot->rightChild == NULL) {							//ONE child (left)
			node* temp = AvlRoot;
			AvlRoot = AvlRoot->leftChild;
			delete temp;
			temp = NULL;
		}
		else {																	//TWO children
			node* temp = findMax(AvlRoot->leftChild);							//Finds max of left subtree
			AvlRoot->data = temp->data;											//Replace deleted with Max in left subtree
			AvlRoot->twin = temp->twin;
			AvlRoot->leftChild = AvlDelete(AvlRoot->leftChild, AvlRoot->data, AVLFile);
		}

		return AvlRoot;
	}

	int balanceFactor = getBalance(AvlRoot);			//Calculates balance factor

	//Rotations
	//R & RR Cases
	if (balanceFactor > 1 && keyData < AvlRoot->leftChild->data) {
		cout << "Right Rotation -- ";
		AVLFile << "Right Rotation -- ";
		return rightRotation(AvlRoot);
	}
	//L & LL Cases
	if (balanceFactor < -1 && keyData > AvlRoot->rightChild->data) {
		cout << "Left Rotation -- ";
		AVLFile << "Left Rotation -- ";
		return leftRotation(AvlRoot);
	}
	//LR Case
	if (balanceFactor > 1 && keyData > AvlRoot->leftChild->data) {
		cout << "Left-Right Rotation -- ";
		AVLFile << "Left-Right Rotation -- ";
		AvlRoot->leftChild = leftRotation(AvlRoot->leftChild);
		return rightRotation(AvlRoot);
	}
	//RL Case
	if (balanceFactor < -1 && keyData < AvlRoot->rightChild->data) {
		cout << "Right-Left Rotation -- ";
		AVLFile << "Right-Left Rotation -- ";
		AvlRoot->rightChild = rightRotation(AvlRoot->rightChild);
		return leftRotation(AvlRoot);
	}
	
	return AvlRoot;
}