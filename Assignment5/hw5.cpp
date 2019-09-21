/* @Author
Student Name: Ahmet Semih Uçan
Student ID : 150160014
Date: 22.12.2018 */

#include <iostream>
#include <fstream>

using namespace std;

struct node {
	int data;
	node* left;
	node* right;
};

struct pathlist {
	int L;
	int R;
	int* L_path;
	int* R_path;
};

struct tree {
	node* root;
	pathlist myPathlist;
	void pathlistcreate();
	void printpath();
	int count;
	int target_sum;
	int* list;
	void create();
	void add(int order, node*);
	void path(int* back_list, int sum, int order, node* parent, char direction);
};

void tree::create() {
	root = NULL;	
}
void tree::pathlistcreate() {
	myPathlist.L = 0;
	myPathlist.R = 0;
	myPathlist.L_path = new int[count];
	myPathlist.R_path = new int[count];
	for (int i = 0; i < count; i++) {
		myPathlist.L_path[i] = 0;
		myPathlist.R_path[i] = 0;
	}
}
void tree::printpath() {
	if (myPathlist.L == 1) {
		int i = 0;
		cout << "Path Found: ";
		while (myPathlist.L_path[i] != 0) {
			cout << myPathlist.L_path[i] << " ";
			i++;
		}
		cout << endl;
	}
	if(myPathlist.R==1){
		int j = 0;
		cout << "Path Found: ";
		while (myPathlist.R_path[j] != 0) {
			cout << myPathlist.R_path[j] << " ";
			j++;
		}
		cout << endl;
	}   
}
void tree::path(int* back_list,int sum, int order,node* parent, char direction) {
	
	if (sum == target_sum) {
		if(direction=='L' && myPathlist.L==0){
			for (int i = 0; i < count; i++) {
				myPathlist.L_path[i] = back_list[i];				
			}
			myPathlist.L = 1;
		}else if (direction == 'R' && myPathlist.R == 0) {
			for (int i = 0; i < count; i++) {
				myPathlist.R_path[i] = back_list[i];				
			}
			myPathlist.R = 1;
		}
	}	
	
	if (parent->left && parent->left->data + sum <= target_sum) {
		int* newpath = new int[count];
		for (int i = 0; i < count; i++) {
			newpath[i] = back_list[i];
		}
		newpath[order] = parent->left->data;
		if (direction == 'O') {
			path(newpath, sum + parent->left->data, order + 1, parent->left, 'L');
		}
		else {
			path(newpath, sum + parent->left->data, order + 1, parent->left, direction);
		}
		
	}
	if (parent->right && parent->right->data + sum <= target_sum) {
		int* newpath = new int[count];
		for (int i = 0; i < count; i++) {
			newpath[i] = back_list[i];
		}
		newpath[order] = parent->right->data;
		if (direction == 'O') {
			direction = 'R';
		}
		path(newpath, sum + parent->right->data, order + 1, parent->right, direction);
	}
	//delete[] back_list;
}
void tree::add(int order, node* parent) {
	if (order == 1) {
		node* new_node = new node;
		new_node->data = list[order - 1];

		root = new_node;
		parent = root;
	}
	if (count >= 2 * order) {
		node* left_node = new node;
		left_node->left = NULL;
		left_node->right = NULL;
		left_node->data = list[2 * order - 1];
		parent->left = left_node;		
	}
	if (count >= 2 * order + 1) {
		node* right_node = new node;
		right_node->left = NULL;
		right_node->right = NULL;
		right_node->data = list[2 * order];
		parent->right = right_node;		
	}
	if (count >= 2 * order) {		
		add(2 * order, parent->left);
	}
	if (count >= 2 * order + 1) {		
		add(2 * order + 1, parent->right);
	}
}

int main(int argc, char* argv[]) {
	
	ifstream input_file;
	//Detection of array size
	input_file.open(argv[1]);

	int count=0;	
	int tmp;

	while (input_file >> tmp) {
		count++;
	}
	count--;
	input_file.close();

	//Create tree
	tree myBinTree;
	myBinTree.create();
	myBinTree.count = count;	
	input_file.open(argv[1]);
	myBinTree.list = new int[count];
	//Fill the array	
	for (int i = 0; i < count; i++) {
		input_file >> myBinTree.list[i];
	}
	//Detect target_sum
	input_file >> myBinTree.target_sum;
	//if root is equal to target_sum
	if (myBinTree.list[0] == myBinTree.target_sum) {
		cout << "Path Found: " << myBinTree.target_sum << endl;
		cout << "Path Found: " << myBinTree.target_sum << endl;
		return 0;
	}
	//Fill the tree
	myBinTree.add(1, myBinTree.root);
	//Create First Array for paths
	int* back_list = new int[myBinTree.count];
	for (int i = 0; i < count; i++) {
		back_list[i]=0;
	}
	back_list[0] = myBinTree.root->data;
	
	myBinTree.pathlistcreate();
	myBinTree.path(back_list,myBinTree.root->data, 1, myBinTree.root, 'O');
	
	if (myBinTree.myPathlist.L == 1 && myBinTree.myPathlist.R == 1) {
		myBinTree.printpath();
	}
	else if((myBinTree.myPathlist.L == 0 && myBinTree.myPathlist.R == 1)){
		cout << "No Path Found" <<endl;
		myBinTree.printpath();
	}
	else if ((myBinTree.myPathlist.L == 1 && myBinTree.myPathlist.R == 0)) {
		myBinTree.printpath();
		cout << "No Path Found"	<< endl;
	}
	else {
		cout << "No Path Found" << endl;
		cout << "No Path Found"	<< endl;
	}

	getchar();
	return 0;
}
