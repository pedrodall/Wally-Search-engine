#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <time.h>

using namespace std;

struct Node {
	int doc_size;
	vector<int>* docs; 
	Node* pChild[128];
	Node() {
		for (int i = 0; i < 128; i++) {
			pChild[i] = nullptr;
		}
		doc_size = 0;
	}
	void array_size(int size) {
		docs = new vector<int>[size];
		doc_size = size;
	}
};