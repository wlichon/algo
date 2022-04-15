#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <string>
#include <memory>


using namespace std;

class Node
{
public:
	

	Node(int key) {
		this->key = key;
		unique_ptr<Node> left = NULL;
		unique_ptr<Node> right = NULL;
	}
	
	int min() {  // O(h) wobei h = hoehe des baumes, bei AVL Baeumen also O(logn) andernfalls O(n)
		if (left == NULL) {
			return key;
		}
		return left->min();
	}

	int max() {  // O(n) falls kein AVL baum sonst O(logn)
		if (right == NULL) {
			return key;
		}
		return right->max();
	}

	void insert(int key) { // O(n) falls kein AVL baum sonst O(logn)
		if (this->key < key) {
			if (right == NULL) {
				right = make_unique<Node>(key);
				return;
			}
			right->insert(key);
		}
		else if (this->key > key) {
			if (left == NULL) {
				left = make_unique<Node>(key);
				return;
			}
			left->insert(key);
		}

	}

	void keySum(int& sum,int& count) { //praeorder O(n) da alle Knoten besucht werden muessen
		count++;
		sum += key;

		if(left)
			left->keySum(sum,count);
		
		if(right)
			right->keySum(sum,count);
	}

	int AVL(bool& isAVL) { // O(n) es muss jeder Knoten untersucht werden
		int rdepth = 0;
		int ldepth = 0;		

		if (right)
			rdepth = right->AVL(isAVL);
		if (left)
			ldepth = left->AVL(isAVL);

		int balanceFactor = rdepth - ldepth;

		cout << "\nbal(" << key << ") = " << balanceFactor;
		if (balanceFactor > 1 || balanceFactor < -1) {
			cout << " (AVL violation!)";
			isAVL = false;
		}

		return std::max(rdepth, ldepth) + 1;
	}

	void easySearch(vector<int>& path,int searchKey) {
		if (this == NULL) {
			return;
		}
		
		path.push_back(key);
		if (searchKey == key) {
			return;
		}
		if (searchKey > key) {
			right->easySearch(path, searchKey);
		}
		if (searchKey < key) {
			left->easySearch(path, searchKey);
		}
	}

	// O(n) wobei n die groesse des Subtrees ist

	void subtreeCheck(Node* mainnode,bool& isSubTree) { //untersucht knoten von subtree, head von main tree wird beim erstaufruf uebergeben
		Node* nextMain = isSub(key,mainnode); //ist Schluessel des subtrees im mainnode subtree enthalten? falls ja wird der node des main trees fuer spaeter im nextMain gespeichert
		
		//nextMain ist noetig um zu wissen ab welchem Knoten im HAUPTTREE man die Suche fortsetzen soll, falls spaeter ein rekursiver Stack gepoppt wird und man in diesen Stackframe zurueckkehrt.

		if (nextMain == NULL) {
			isSubTree = false;	
			return;			// falls nextMain NULL ist, ist der node nicht im subtree des mainnodes enthalten (heisst nicht unbedingt dass der knoten im haupttree nicht existiert)
		}

		if (left != NULL && isSubTree != false) { //left ist linker node vom subtree dessen key value wir im nextMain suchen
			left->subtreeCheck(nextMain,isSubTree);
		}
		if (right != NULL && isSubTree != false) {
			right->subtreeCheck(nextMain,isSubTree);
		}


	}

	Node* isSub(int& key,Node* mainnode) { //O(n^2) wobei n die groesse des Untertrees ist
		if (key == mainnode->key) {
			return mainnode; 
		}

		if (key < mainnode->key) {
			if (mainnode->left == NULL) {
				return NULL;
			}
			return isSub(key, mainnode->left.release());
		}

		if (key > mainnode->key) {
			if (mainnode->right == NULL) {
				return NULL;
			}
			return isSub(key, mainnode->right.release());
		}

		return NULL;
	}


	int getKey() {
		return key;
	}



	int key;
	unique_ptr<Node> left;
	unique_ptr<Node> right;
};

