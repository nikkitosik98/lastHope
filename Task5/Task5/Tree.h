#pragma once
#include "vector"
#include "iostream"
struct VectorException {};

struct TreeElem {
	int data;
	TreeElem* left;
	TreeElem* right;
	TreeElem(int data, TreeElem *left, TreeElem* rigth);
};
class Tree
{
private:
	TreeElem* root;
	int size;
	void copyTree(TreeElem*& root, TreeElem* copy);
	void delTree(TreeElem * root);
	void writeTree(std::ostream & os, TreeElem * root, int step);
	int countEven(TreeElem* root);
	bool positiveElem(TreeElem* root);
	void delLeaves(TreeElem*& root);
	double middle(TreeElem* root);
	bool findElem(int x, TreeElem* root, std::vector<int> &vect);
public:
	Tree();
	Tree(const Tree &copy);
	Tree(Tree &&copy);
	Tree& operator= (const Tree &copy);
	Tree& operator= ( Tree &&copy);
	~Tree();
	void pasteElem(int elem, std::vector<int> vector);
	friend std::ostream& operator<<(std::ostream & stream, Tree &tree);
	int countEven();
	bool positiveElem();
	void delLeaves();
	double middle();
	std::vector<int> findElem(int x);
};

