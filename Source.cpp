#include "AvlTree.h"
#include "BstTree.h"
#include "SplayTree.h"
#include "Trees.h"

// create 2D operations array	
											
int main() {
	char readChar;
	int parent = -1, level, readInt, initRead;

	string testName, fileName;
	fstream inputFile1, inputFile2, BSTFile, AVLFile, SplayFile, SummaryFile;

	//ASK USER FOR TEST NAME
	cout << "Please enter a test name: ";
	cin >> testName;

	//ASK USER FOR INPUT/OUTPUT FILE NAMES
	cout << "\nPlease enter your first input file name [inserts file]: ";		//Initial inserts
	cin >> fileName;
	inputFile1.open(fileName);
	fileTest(inputFile1, fileName);

	cout << "\nPlease enter your second input file name [actions file]: ";		//Actions 
	cin >> fileName;
	inputFile2.open(fileName);
	fileTest(inputFile2, fileName);

	cout << "\nPlease enter your output BST file name: ";
	cin >> fileName;
	BSTFile.open(fileName);
	fileTest(BSTFile, fileName);

	cout << "\nPlease enter your output AVL file name: ";
	cin >> fileName;
	AVLFile.open(fileName);
	fileTest(AVLFile, fileName);

	cout << "\nPlease enter your output Splay file name: ";
	cin >> fileName;
	SplayFile.open(fileName);
	fileTest(SplayFile, fileName);

	cout << "\nPlease enter your output Summary file name: ";
	cin >> fileName;
	SummaryFile.open(fileName, ios::app);
	fileTest(SummaryFile, fileName);

	node* BstRoot = NULL;
	node* AvlRoot = NULL;
	node* SplayRoot = NULL;

	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++) {
			operatorArr[i][j] = 0;
		}
	}

	cout << endl;

	//populate all trees with initial inserts
	while (inputFile1 >> initRead) {
		//Print Each Tree
		cout << endl << "BST: ";
		BstRoot = BstInsert(BstRoot, initRead);
		cout << "Inserted " << initRead << endl;
		BSTFile << "Inserted " << initRead << endl;
		
		cout << "Binary Search Tree: \n";
		printTree(BstRoot, BSTFile);

		cout << "AVL ROTATIONS: ";
		AVLFile << "AVL ROTATIONS: ";
		AvlRoot = AvlInsert(AvlRoot, initRead, AVLFile);
		cout << endl << "AVL: ";
		AVLFile << endl << "AVL: ";
		cout << "Inserted " << initRead << endl;
		AVLFile << "Inserted " << initRead << endl;
		
		cout << "AVL Tree: \n";
		printTree(AvlRoot, AVLFile);

		cout << "Splay ROTATIONS: ";
		SplayFile << "Splay ROTATIONS: ";
		SplayRoot = SplayInsert(SplayRoot, initRead, SplayFile);
		cout << endl << "Splay: ";
		SplayFile << endl << "Splay: ";
		cout << "Inserted " << initRead << endl;
		SplayFile << "Inserted " << initRead << endl;
		
		cout << "Splay Tree: \n";
		SplayFile << "Splay Tree: \n";
		printTree(SplayRoot, SplayFile);
		cout << endl;
	}

	//Read action file and execute proper command for each line
	inputFile2.get(readChar);

	while (!inputFile2.eof()) {
		//Use a switch case in order to make sure that each command is taken properly and discard invalid commands
		switch (readChar) {
		case 'I':
			inputFile2 >> readInt;
			
			//Print Each Tree
			cout << endl << "BST: ";
			BSTFile << endl << "BST: ";
			BstRoot = BstInsert(BstRoot, readInt);
			cout << "Inserted " << readInt << endl;
			BSTFile << "Inserted " << readInt << endl;
			
			cout << "Binary Search Tree: \n";
			BSTFile << "Binary Search Tree: \n";
			printTree(BstRoot, BSTFile);
						
			cout << "AVL ROTATIONS: ";
			AVLFile << "AVL ROTATIONS: ";
			AvlRoot = AvlInsert(AvlRoot, readInt, AVLFile);
			cout << endl << "AVL: ";
			AVLFile << endl << "AVL: ";
			cout << "Inserted " << readInt << endl;
			AVLFile << "Inserted " << readInt << endl;
			
			cout << "AVL Tree: \n";
			AVLFile << "AVL Tree: \n";
			printTree(AvlRoot, AVLFile);

			
			cout << "Splay ROTATIONS: ";
			SplayFile << "Splay ROTATIONS: ";
			SplayRoot = SplayInsert(SplayRoot, readInt, SplayFile);
			cout << endl << "Splay: ";
			SplayFile << endl << "Splay: ";
			cout << "Inserted " << readInt << endl;
			SplayFile << "Inserted " << readInt << endl;
			
			
			cout << "Splay Tree: \n";
			SplayFile << "Splay Tree: \n";
			printTree(SplayRoot, SplayFile);
			break;
		case 'S':
			inputFile2 >> readInt;

			//Print Each Tree
			cout << endl << "BST: ";
			BSTFile << endl << "BST: ";
			cout << "Searched " << readInt << endl;
			BSTFile << "Searched " << readInt << endl;
			if (BstSearch(BstRoot, readInt)) {
				cout << "Found BST node at Level: " << getLevel(BstRoot, readInt) << endl;
				BSTFile << "Found BST node at Level: " << getLevel(BstRoot, readInt) << endl;
				cout << "Parent: ";
				BSTFile << "Found BST node at Level: " << getLevel(BstRoot, readInt) << endl;
				BSTFile << "Parent: ";
				findParent(BstRoot, readInt, parent, BSTFile);
				cout << endl;
				BSTFile << endl;
			}
			else {
				cout << "BST node is not found.\n";
				BSTFile << "BST node is not found.\n";
			}
			
			cout << "Binary Search Tree: \n";
			BSTFile << "Binary Search Tree: \n";
			printTree(BstRoot, BSTFile);

			cout << endl << "AVL: ";
			AVLFile << endl << "AVL: ";
			cout << "Searched " << readInt << endl;
			AVLFile << "Searched " << readInt << endl;
			if (AvlSearch(AvlRoot, readInt)) {
				cout << "Found AVL node at Level: " << getLevel(AvlRoot, readInt) << endl;
				AVLFile << "Found AVL node at Level: " << getLevel(AvlRoot, readInt) << endl;
				cout << "Parent: ";
				AVLFile << "Parent: ";
				findParent(AvlRoot, readInt, parent, AVLFile);
				cout << endl;
				AVLFile << endl;
			}
			else {
				cout << "AVL node is not found.\n";
				AVLFile << "AVL node is not found.\n";
			}
	
			cout << "AVL Tree: \n";
			AVLFile << "AVL Tree: \n";
			printTree(AvlRoot, AVLFile);

			cout << endl << "Splay: "; 
			SplayFile << endl << "Splay: "; 
			cout << "Searched " << readInt << endl;
			SplayFile << "Searched " << readInt << endl;
			cout << "\nFound Splay node at Level: " << getLevel(SplayRoot, readInt) << endl;
			SplayFile << "\nFound Splay node at Level: " << getLevel(SplayRoot, readInt) << endl;
			cout << "Parent: ";
			SplayFile << "Parent: ";
			findParent(SplayRoot, readInt, parent, SplayFile);
			cout << "\nSplay ROTATIONS: ";
			SplayFile << "\nSplay ROTATIONS: ";
			if (SplaySearch(SplayRoot, readInt)) {
				SplayRoot = Splay(SplayRoot, readInt, SplayFile);
			}
			else {
				cout << "Splay node is not found.\n";
				SplayFile << "Splay node is not found.\n";
			}
			
			cout << endl;
			SplayFile << endl;

			cout << "Splay Tree: \n";
			SplayFile << "Splay Tree: \n";
			printTree(SplayRoot, SplayFile);
			break;
		case 'D':
			inputFile2 >> readInt;

			//Print Each Tree
			cout << endl << "BST: ";
			BSTFile << endl << "BST: ";
			BstRoot = BstDelete(BstRoot, readInt);
			cout << "Deleted " << readInt << endl;
			BSTFile << "Deleted " << readInt << endl;
			
			cout << "Binary Search Tree: \n";
			BSTFile << "Binary Search Tree: \n";
			printTree(BstRoot, BSTFile);

			cout << "AVL ROTATIONS: ";
			AVLFile << "AVL ROTATIONS: ";
			AvlRoot = AvlDelete(AvlRoot, readInt, AVLFile);
			cout << endl << "AVL: ";
			AVLFile << endl << "AVL: ";
			cout << "Deleted " << readInt << endl;
			AVLFile << "Deleted " << readInt << endl;
			
			cout << "AVL Tree: \n";
			AVLFile << "AVL Tree: \n";
			printTree(AvlRoot, AVLFile);

			
			cout << "Splay ROTATIONS: ";
			SplayFile << "Splay ROTATIONS: ";
			SplayRoot = SplayDelete(SplayRoot, readInt, SplayFile);
			cout << endl << "Splay: ";
			SplayFile << endl << "Splay: ";
			cout << "Deleted " << readInt << endl;
			SplayFile << "Deleted " << readInt << endl;
			
			cout << "Splay Tree: \n";
			SplayFile << "Splay Tree: \n";
			printTree(SplayRoot, SplayFile);

			cout << endl;
			SplayFile << endl;
			break;
		case '\n':
			break;
		default:
			cout << "ERROR: INVALID OPERATION\n";									//Default catches all invalid operations
			break;
		}

		inputFile2.get(readChar);
	}

	printArr(testName);
	printArrToFiles(BSTFile, testName);
	printArrToFiles(AVLFile, testName);
	printArrToFiles(SplayFile, testName);
	printSummary(SummaryFile, testName);

	inputFile1.close();
	inputFile2.close();
	BSTFile.close();
	AVLFile.close();
	SplayFile.close();
	SummaryFile.close();

	return 0;
}
