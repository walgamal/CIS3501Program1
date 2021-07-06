#pragma once
#include "AvlTree.h"
#include "SplayTree.h"
#include "Trees.h"

node* BstInsert(node* BstRoot, int data) {

	operatorArr[0][0]++;

	if (BstRoot == NULL) {								//if empty, create node
		BstRoot = MakeNewNode(data);
	}
	else if (data < BstRoot->data) {					//else, do comparisons to find empty node (left is less, right is more)
		BstRoot->leftChild = BstInsert(BstRoot->leftChild, data);
	}
	else if (data > BstRoot->data) {
		BstRoot->rightChild = BstInsert(BstRoot->rightChild, data);
	}
	else {												//else if equal, add to twin chain
		BstRoot->twin = BstInsert(BstRoot->twin, data);
	}

	return BstRoot;
}

bool BstSearch(node* BstRoot, int keyData) {	

	operatorArr[1][0]++;

	if (BstRoot == NULL) {
		return false;
	}
	else if (BstRoot->data == keyData) {				//check if at root
		return true;
	}
	else if (keyData < BstRoot->data) {					//checks left child
		BstSearch(BstRoot->leftChild, keyData);
		return true;
	}
	else if (keyData > BstRoot->data) {					//checks right child
		BstSearch(BstRoot->rightChild, keyData);
		return true;
	}
	else {
		return false;
	}	   
}

node* BstDelete(node* BstRoot, int keyData) {
	
	operatorArr[2][0]++;

	if (BstRoot == NULL) {
		return BstRoot;
	}
	else if (keyData < BstRoot->data) {
		BstRoot->leftChild = BstDelete(BstRoot->leftChild, keyData);
	}
	else if (keyData > BstRoot->data) {
		BstRoot->rightChild = BstDelete(BstRoot->rightChild, keyData);
	}
	else if (keyData == BstRoot->data){
		//found, delete --> then take appropiate deletion method(Leaf, 1 child, or 2 children)
		if (BstRoot->leftChild == NULL && BstRoot->rightChild == NULL) { //NO children
			delete BstRoot;
			BstRoot = NULL;
		}
		else if (BstRoot->twin != NULL) {								//IF THERES A TWIN
			node* prev = BstRoot;
			while (prev->twin->twin != NULL) {							//Traverse Link List
				prev = prev->twin;						
				prev = BstRoot->twin;									//Keep track of previous node
			}
			delete prev->twin;
			prev->twin = NULL;
		}
		else if (BstRoot->leftChild == NULL) {							//ONE child (right)
			node* temp = BstRoot;
			BstRoot = BstRoot->rightChild;
			delete temp;
			temp = NULL;
		}
		else if (BstRoot->rightChild == NULL) {							//ONE child (left)
			node* temp = BstRoot;
			BstRoot = BstRoot->leftChild;
			delete temp;
			temp = NULL;
		}
		else {																	//TWO children
			node* temp = findMax(BstRoot->leftChild);							//Finds max of left subtree
			BstRoot->data = temp->data;											//Replace deleted with Max in left subtree
			BstRoot->twin = temp->twin;
			BstRoot->leftChild = BstDelete(BstRoot->leftChild, BstRoot->data);								//Deletes moved node, so no duplicate
		}
	}

	return BstRoot;
}