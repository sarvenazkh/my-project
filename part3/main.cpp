#include <fstream>
#include <vector>
#include <cstring>
#include "Virus.h"
#include <string>
//#include <time.h> 
#include <iostream>

using namespace std;
bool get_reads(char * file_name, vector<string> &r, int vsize);
void checkinput(char input);

int main()
{


	int vsize = 0;
	int len = 0;
	char input;

	cout << "How long of a genome sequence would you like to analyze? 1,000,000 is default." << endl;
	while (len < 1 || len > 1000000000) {
		cout << "Enter a valid genome length between 1 and 1 billion." << endl;
		cin >> len;
		cin.clear();
		cin.ignore(1000000000, '\n');
	}

	cout << "How long of a virus sequence would like to analyze? 100 is default." << endl;
	while (vsize < 1 || vsize > 10000) {
		cout << "Enter a valid virus length between 1 and 1000." << endl;
		cin >> vsize;
		cin.clear();
		cin.ignore(1000000000, '\n');
	}

	cout << "We're loading up " << len << " characters into the tree, one moment please." << endl;

	QuarterTree a, g, c, t;

	ifstream in;
	in.open("genome.txt"); 
	if (!in.is_open()) {
		cout << "The read file could not be opened. Check the location.\t";
	}
	
	char * word = new char[vsize]; 
	
	word[vsize] = '\0'; 


	for (int i = 1; i < (len - vsize -1); i++)  
	{
		for (int j = 0; j < (vsize - 1); j++) 
			word[j] = word[j + 1];
		in >> word[(vsize - 1)];
		word[vsize] = '\0';
		if (i % (vsize - 1) == 0) 
		{
			if (word[0] == 'a')a.InsertNode(word); 
			else if (word[0] == 'g')g.InsertNode(word);
			else if (word[0] == 'c')c.InsertNode(word);
			else if (word[0] == 't')t.InsertNode(word);
		}
	}
	
	in.clear();
	in.close(); 
	
	word = NULL;
	delete word; 
	 
	cout << "Char 'a' tree height : " << a.ComputeHeight(a.Root) << " Char 'a' total nodes : " << a.CountNodes(a.Root) << endl;	
	cout << "Char 'g' tree height : " << g.ComputeHeight(g.Root) << " Char 'g' total nodes : " << g.CountNodes(g.Root) << endl;
	cout << "Char 'c' tree height : " << c.ComputeHeight(c.Root) << " Char 'c' total nodes : " << c.CountNodes(c.Root) << endl;
	cout << "Char 't' tree height : " << t.ComputeHeight(t.Root) << " Char 't' total nodes : " << t.CountNodes(t.Root) << endl;


	vector<string> rds; 
	get_reads("virus.txt", rds, vsize); 
	char *wo = new char[(vsize + 1)]; 
	for (int k = 0; k < rds.size(); k++) 
	{
		cout << wo << endl;
		cout << wo[0];
		cout << "Testing sequence: " << rds[k] << endl;
		string rd = rds[k]; 
		strcpy_s(wo, (vsize + 1), rd.c_str());
		if (wo[0] == 'a')a.TraverseTree(wo);
		else if (wo[0] == 'g') g.TraverseTree(wo); 
		else if (wo[0] == 'c') c.TraverseTree(wo);
		else if (wo[0] == 't')t.TraverseTree(wo);
		else break;
	}

	cout << "Now that you've seen how it works, you may test your own sequence against our genome if you wish." << endl;

	char * test_sequence = new char[vsize]; 
											
	string test = "";
	cout << "Would you like to test a specific virus sequence of length " << vsize << " ? Enter y or n." << endl;
	cin >> input;
	cin.ignore(100, '\n');
	checkinput(input); 
	
	while (true) {
		if (input == 'y' || input == 'Y') {
			cout << "Note, only " << vsize << " characters will be accepted." << endl;
			cout << "Please enter virus sequence: " << endl;
			cin >> test; 
			
			while (test.length() != vsize)
			{
				cout << "Please enter in a sequence of the right size : " << vsize << " characters" << endl;
				cin >> test; 
			}

			for (int k = 0; k < vsize; k++) {
				test[k] = tolower(test[k]);
			}

			strcpy_s(test_sequence, (vsize + 1), test.c_str());
			
			if (test_sequence[0] == 'a') { (a.TraverseTree(test_sequence)); } 
			else if (test_sequence[0] == 'g') { g.TraverseTree(test_sequence); } 
			else if (test_sequence[0] == 'c') { c.TraverseTree(test_sequence); }
			else if (test_sequence[0] == 't') { t.TraverseTree(test_sequence); }
		}
		cout << "Would you like to test another specific virus sequence of length " << vsize << " ? Enter y or n." << endl;
		cin >> input; 
		cin.ignore(100, '\n');
		checkinput(input);
		if (input == 'n' || input == 'N') { break; }
	}

	delete wo;
	wo = NULL; 
	
	system("pause");
	return true;
}

bool get_reads(char * file_name, vector<string> &r, int vsize) {
	ifstream in;
	in.open(file_name);
	if (!in.is_open()) {
		cout << "The read file could not be opened. Check the location.\t";
		return false;
	}
	char * word = new char[(vsize + 1)]; 
	while (in.peek() != EOF)
	{
		in.getline(word, (vsize + 1), '\n'); 
		r.push_back(word);
	}
	in.clear();
	in.close();
	
	word = NULL; 
	delete word;
	
	return true;
}

void checkinput(char input) {
	while (input != 'y' && input != 'n' && input != 'Y' && input != 'N')
	{
		cout << "Enter y or n, please." << endl;
		cin >> input;
		cin.clear();
		cin.ignore(100, '\n');
	}
}