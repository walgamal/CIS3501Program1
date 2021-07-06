#pragma once
#include "AvlTree.h"
#include "BstTree.h"
#include "Trees.h"

node* Splay(node* SplayRoot, int keyData, fstream& SplayFile) {
	//After any operation --> Move latest accessed node to root
	//Use the proper rotation --> Zig, Zag, Zig-Zig, Zag-Zag, Zig-Zag, Zag-Zig

	if (SplayRoot == NULL ) {							//empty tree
		return SplayRoot;
	}
	else if (SplayRoot->data == keyData) {				//Already splayed
		return SplayRoot;
	}
	else if (SplayRoot->data > keyData) {				//key is in left subtree
		if (SplayRoot->leftChild == NULL) {				//left child is NULL, so key is at root
			return SplayRoot;
		}
		else if (SplayRoot->leftChild->data > keyData) {			//Zig and Zig-Zig Case
			SplayRoot->leftChild->leftChild = Splay(SplayRoot->leftChild->leftChild, keyData, SplayFile);		//bring key to root
			cout << "Zig-";
			SplayFile << "Zig-";
			SplayRoot = zigRotation(SplayRoot);														//preform first rotation
			
		}
		else if (SplayRoot->leftChild->data < keyData) {			//Zag-Zig Case
			SplayRoot->leftChild->rightChild = Splay(SplayRoot->leftChild->rightChild, keyData, SplayFile);	//bring key to root
			
			if(SplayRoot->leftChild->rightChild != NULL){											//preform first rotation
				cout << "Zag-";
				SplayFile << "Zag-";
				SplayRoot->leftChild = zagRotation(SplayRoot->leftChild);
			}

		}

		if (SplayRoot->leftChild == NULL) {			//preform second rotation
			return SplayRoot;
		}
		else {
			cout << "Zig Rotation -- ";
			SplayFile << "Zig Rotation -- ";
			return zigRotation(SplayRoot);
			
		}
	}
	else {											//key MUST be in right subtree now
		if (SplayRoot->rightChild == NULL) {		//no right subtree, so it is already splayed				
			return SplayRoot;
		}
		else if (SplayRoot->rightChild->data < keyData) {			//Zag-Zag Case
			SplayRoot->rightChild->rightChild = Splay(SplayRoot->rightChild->rightChild, keyData, SplayFile);	//bring key to root
			cout << "Zag-";
			SplayFile << "Zag-";
			SplayRoot = zagRotation(SplayRoot);													//preform first rotation
		}
		else if (SplayRoot->rightChild->data > keyData) {			//Zig-Zag Case
			SplayRoot->rightChild->leftChild = Splay(SplayRoot->rightChild->leftChild, keyData, SplayFile);	//bring key to root
			
			if (SplayRoot->rightChild->leftChild != NULL) {
				cout << "Zig-";
				SplayFile << "Zig-";
				SplayRoot->rightChild = zigRotation(SplayRoot->rightChild);						//preform first rotation
			}
		}

		if (SplayRoot->rightChild == NULL) {		//preform second rotation
			return SplayRoot;
		}
		else {
			cout << "Zag Rotation -- ";
			SplayFile << "Zag Rotation -- ";
			return zagRotation(SplayRoot);
		}
		
	}

	//Splay
	return SplayRoot;
}

node* SplayInsert(node* SplayRoot, int data, fstream& SplayFile) {
	//if empty, create node
	//else, do comparisons to find empty node (left is less, right is more)
	//else if equal, add to twin chain
	//If needed, re-balance

	operatorArr[0][2]++;
	
	if (SplayRoot == NULL) {								//if empty, create node
		SplayRoot = MakeNewNode(data);
	}
	else if (data < SplayRoot->data) {					//else, do comparisons to find empty node (left is less, right is more)
		SplayRoot->leftChild = SplayInsert(SplayRoot->leftChild, data, SplayFile);
	}
	else if (data > SplayRoot->data) {
		SplayRoot->rightChild = SplayInsert(SplayRoot->rightChild, data, SplayFile);
	}
	else {												//else if equal, add to twin chain
		SplayRoot->twin = SplayInsert(SplayRoot->twin, data, SplayFile);
	}

	//Splay
	return Splay(SplayRoot, data, SplayFile);
}

bool SplaySearch(node* SplayRoot, int keyData) {
	//make comparisons and match to search
	//if found, return level and parent of node 
	//if not found, return error

	operatorArr[1][2]++;
	
	if (SplayRoot == NULL) {
		return false;
	}
	else if (SplayRoot->data == keyData) {					//check if at root
		return true;
	}
	else if (keyData < SplayRoot->data) {					//checks left child
		SplaySearch(SplayRoot->leftChild, keyData);
		return true;
	}
	else if (keyData > SplayRoot->data) {					//checks right child
		SplaySearch(SplayRoot->rightChild, keyData);
		return true;
	}
	else {
		return false;
	}

}

node* SplayDelete(node* SplayRoot, int keyData, fstream& SplayFile) {
	//search
	//if found, delete --> then take appropiate deletion method
	//if not found, return error
	//If needed, re-balance

	operatorArr[2][2]++;

	SplayRoot = Splay(SplayRoot, keyData, SplayFile);
	
	if (SplayRoot == NULL) {
		return SplayRoot;
	}
	else if (SplayRoot->twin != NULL) {								//IF THERES A TWIN
		node* prev = SplayRoot;
		while (prev->twin->twin != NULL) {							//Traverse Link List
			prev = prev->twin;
			prev = SplayRoot->twin;									//Keep track of previous node
		}
		delete prev->twin;
		prev->twin = NULL;
	}
	else if (keyData < SplayRoot->data) {
		SplayRoot->leftChild = SplayDelete(SplayRoot->leftChild, keyData, SplayFile);
	}
	else if (keyData > SplayRoot->data) {
		SplayRoot->rightChild = SplayDelete(SplayRoot->rightChild, keyData, SplayFile);
	}
	else if (keyData == SplayRoot->data) {
		//found, delete --> then take appropiate deletion method(Leaf, 1 child, or 2 children)
		if (SplayRoot->leftChild == NULL && SplayRoot->rightChild == NULL) { //NO children
			delete SplayRoot;
			SplayRoot = NULL;
		}
		else if (SplayRoot->leftChild == NULL) {								//ONE child (right)
			node* temp = SplayRoot;
			SplayRoot = SplayRoot->rightChild;
			delete temp;
			temp = NULL;
		}
		else if (SplayRoot->rightChild == NULL) {								//ONE child (left)
			node* temp = SplayRoot;
			SplayRoot = SplayRoot->leftChild;
			delete temp;
			temp = NULL;
		}
		else {																	//TWO children
			node* temp = findMax(SplayRoot->leftChild);							//Finds max of left subtree
			SplayRoot->data = temp->data;										//Replace deleted with Max in left subtree
			SplayRoot->twin = temp->twin;
			SplayRoot->leftChild = SplayDelete(SplayRoot->leftChild, SplayRoot->data, SplayFile);
		}

		return SplayRoot;
	}

	//Splay
	return SplayRoot;
}