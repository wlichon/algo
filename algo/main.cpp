#include "Tree.h"
#include "Node.h"

using namespace std;

int main(int argc, char** argv) {
	Tree tree;
	if (argc == 2) {
		char* searchTree = argv[1];
		tree.treeRead(searchTree);
	}
	else if (argc == 3) {
		char* searchTree = argv[1];
		char* subTree = argv[2];
		tree.treeRead(searchTree,subTree);
	}

	
}