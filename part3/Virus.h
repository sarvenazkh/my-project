#include<iostream>

using namespace std;

class QTreeNode {
public:
	char Data;
	QTreeNode *aChild;
	QTreeNode *gChild;
	QTreeNode *cChild;
	QTreeNode *tChild;
};

class QuarterTree {
public:
	QTreeNode *Root;
public:
	QuarterTree() {
		Root = NULL;
	}
	void InsertNode(char * word);
	QTreeNode* createNode(char val);
	int CountNodes(QTreeNode*node);
	int ComputeHeight(QTreeNode*  Root);
	void TraverseTree(char * sequence);
};