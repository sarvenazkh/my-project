#include <fstream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <string.h>
#include "Virus.h"

using namespace std;

void QuarterTree :: InsertNode(char * word) { 

	if (!Root) {	
		Root = createNode(word[0]);
	}
	QTreeNode *ptr; 
	ptr = Root;
	int i = 1; 

	while (i < strlen(word)) {
		if (word[i] == 'a') { 
			if (ptr->aChild) {
				ptr = ptr->aChild;
			} 
			else {
				ptr->aChild = createNode(word[i]);
				ptr = ptr->aChild;
			} 
			i++;
		}
		else if (word[i] == 'g') {
			if (ptr->gChild) {
				ptr = ptr->gChild;
			}	
			else {
				ptr->gChild = createNode(word[i]);
				ptr = ptr->gChild;
			}	
			i++;
		}
		else if (word[i] == 'c') { 
			if (ptr->cChild) {
				ptr = ptr->cChild;
			}
			else {
				ptr->cChild = createNode(word[i]);
				ptr = ptr->cChild;
			}
			i++;
		}
		else if (word[i] == 't') {
			if (ptr->tChild) {
				ptr = ptr->tChild;
			}
			else {
				ptr->tChild = createNode(word[i]);
				ptr = ptr->tChild;
			}
			i++;
		}
	}
}
QTreeNode * QuarterTree::createNode(char val) {
	QTreeNode *newnode = new QTreeNode();
	newnode->Data = val; 
	newnode->aChild = NULL; 
	newnode->gChild = NULL;
	newnode->cChild = NULL;
	newnode->tChild = NULL;
	return newnode;
}

int QuarterTree::CountNodes(QTreeNode* Root) {
	if (Root == NULL) { return 0; } 
	else { 
		return (1 + CountNodes(Root->aChild) + CountNodes(Root->gChild) + CountNodes(Root->cChild) + CountNodes(Root->tChild));
	}
}

int QuarterTree::ComputeHeight(QTreeNode*  Root) {
	int aHeight, gHeight, cHeight, tHeight;
	if (Root == NULL) { return 0; } 

	aHeight = ComputeHeight(Root->aChild); 
	gHeight = ComputeHeight(Root->gChild);
	cHeight = ComputeHeight(Root->cChild); 
	tHeight = ComputeHeight(Root->tChild); 

	int left = fmax(aHeight, gHeight);
	int right = fmax(cHeight, tHeight);
	int largest = fmax(left, right);
	

	return largest + 1;
}

void QuarterTree::TraverseTree(char * sequence) {
	if (!Root) { return; }
	int size = 0;
	size = strlen(sequence);
	QTreeNode *ptr; 
	ptr = Root;
	int i = 1; 
	while (i < (size - 1)) {
		cout << "Checking character : " << sequence[i] << endl;
		if (sequence[i] == 'a') {
			if (ptr->aChild) { ptr = ptr->aChild; i++; }
			else { cout << endl << "Sequence broken at character : " << sequence[i] << " at iteration " << i << endl; break; }
		}
		else if (sequence[i] == 'g') {
			if (ptr->gChild) { ptr = ptr->gChild; i++; }
			else { cout << endl << "Sequence broken at character : " << sequence[i] << " at iteration " << i << endl; break; }
		}
		else if (sequence[i] == 'c') { 
			if (ptr->cChild) { ptr = ptr->cChild; i++; }
			else { cout << endl << "Sequence broken at character : " << sequence[i] << " at iteration " << i << endl; break; }
		}
		else if (sequence[i] == 't') { 
			if (ptr->tChild) { ptr = ptr->tChild; i++; }
			else { cout << endl << "Sequence broken at character : " << sequence[i] << " at iteration " << i << endl; break; }
		}
		else {
			cout << "sequence broken." << endl; break;
		}
	}
	if (i == (size - 1)) 
	{
		cout << endl << "Match found: " << endl << endl << sequence << endl << endl;
	}
	else { cout << endl << "Unable to find Sequence : " << endl << endl << sequence << endl << endl; }
}
