#pragma once
#include <iostream>
#include "Node.h"
#include <vector>
#include <fstream>
#include <string>
#include <memory>


using namespace std;

class Node;

static void readFile(const char* fileName, vector<int>& values) {

	ifstream fin;
	fin.open(fileName);
	string strNumber;
	int number = 0;

	if (!fin.is_open()) {
		perror("Error open");
		exit(EXIT_FAILURE);
	}

	while (getline(fin, strNumber)) {
		if (strNumber.empty()) {
			break;
		}
		number = stoi(strNumber);
		values.push_back(number);
	}

	fin.close();
}

class Tree
{
public:
	
	Tree() {
		head = NULL;
	}

	void treeRead(const char* searchTree) {
		vector<int> valuesTree;
		readFile(searchTree, valuesTree);
		if (valuesTree.size() == 0) {
			return;
		}
		fillTree(valuesTree);
		getAVL();
		cout << "min: " << getMin() << ", max: " << getMax() << ", avg: " << getAverage() << endl;
	}

	void treeRead(const char* searchTree, const char* subTree) {
		vector<int> valuesTree;
		vector<int> valuesSubTree;
		readFile(searchTree, valuesTree);
		readFile(subTree, valuesSubTree);
		fillTree(valuesTree);

		if (valuesSubTree.size() == 0) {
			cout << "Subtree found\n";
		}
		if (valuesTree.size() == 0) {
			cout << "Subtree not found\n";
		}

		if (valuesSubTree.size() == 1) {
			int key = valuesSubTree.front();
			vector<int> path;
			head->easySearch(path, key);
			if (path.back() == key) {
				cout << key << " found ";
				for (auto i : path)
					(i == path.back()) ? cout << i << "\n" : cout << i << ", ";
			}
			else {
				cout << key << " not found!\n";
			}
		}
		else {
			Tree subtree;
			subtree.fillTree(valuesSubTree);
			bool isSubTree = true;
			subtree.head->subtreeCheck(head.release(),isSubTree);
			if (isSubTree) {
				cout << "Subtree found\n";
			}
			else {
				cout << "Subtree not found\n";
			}
		}
	}

	void fillTree(vector<int>& values) {
		for (auto key : values) {
			if (head == NULL) {
				head = make_unique<Node>(key);
				continue;
			}
			head->insert(key);
		}
	}

	int getMin() {
		return head->min();
	}

	int getMax() {
		return head->max();
	}

	float getAverage() {
		int sum = 0;
		int count = 0;
		if (head != NULL) {
			head->keySum(sum,count);
		}
		return (float)sum/(float)count;

	}

	void getAVL() {
		bool isAVL = true;
		head->AVL(isAVL);
		cout << endl;
		isAVL ? cout << "AVL: yes" : cout << "AVL: no";
		cout << endl;
	}

	unique_ptr<Node> head;
};

