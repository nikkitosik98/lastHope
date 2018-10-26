#include "stdafx.h"
#include "TreeDictionary.h"

//����������� ����
Node::Node(std::string word, unsigned int frequency, Node * right, Node * left)
{
	this->word = word;
	this->frequency = frequency;
	this->right = right;
	this->left = left;
}

void TreeDictionary::del2(Node *& rootLeft, Node *& toDel)
{//�������� ���� ��� �������, ������ ����� ������ � ��� ���� �������
	if (rootLeft->right) {//���� � ������ ���� ���-�� ������
		del2(rootLeft->right, toDel);
	}
	toDel->word = rootLeft->word;//��������� �����, �������
	toDel->frequency = root->frequency;
	toDel = rootLeft;
	rootLeft = rootLeft->left;
}

void TreeDictionary::copyTree(Node * root, Node * copy)
{
	if (!copy) {
		return;
	}
	root = new Node(copy->word, copy->frequency);
	copyTree(root->left, copy->left);
	copyTree(root->right, copy->right);
}

void TreeDictionary::deleteTree(Node * root)
{//�������� ������
	if (!root) {
		return;
	}
	deleteTree(root->left);
	deleteTree(root->right);
	delete root;
}

unsigned int TreeDictionary::findWord(Node * root, std::string word)
{//����� �����, ��������� ���������� ���������
	if (!root) { return 0; }
	if (root->word.compare(word) == 0) {
		return root->frequency;
	}
	if (root->word.compare(word) > 0) {
		return findWord(root->left, word);
	}
	if (root->word.compare(word) < 0) {
		return findWord(root->right, word);
	}
}

void TreeDictionary::addWord(Node *& root, std::string &word)
{//�������� �����
	if (!root) {
		root = new Node(word);
		return;
	}
	if (root->word.compare(word) == 0) {
		root->frequency++;
		return;
	}
	if (root->word.compare(word) > 0) {
		addWord(root->left, word);
	}
	if (root->word.compare(word) < 0) {
		addWord(root->right, word);
	}
}

void TreeDictionary::deleteWord(Node *& root, std::string& word)
{
	if (!root) {
		return;
	}
	if (root->word.compare(word) > 0) {
		deleteWord(root->left, word);
		return;
	}
	if (root->word.compare(word) < 0) {
		deleteWord(root->right, word);
		return;
	}
	Node* pDel = root;//����� �� �����, ������� ���� �������
	if (root->frequency > 1) {
		root->frequency--;//��������� �������
	}
	else {//���� ������� =1, �� ������� ����
		if (!root->right) {
			root = root->left;
			delete pDel;
			return;
		}
		if (!root->left) {
			root = root->right;
			delete pDel;
			return;
		}
		del2(root->left, pDel);
		delete pDel;
	}
}

void TreeDictionary::printTree(std::ostream & os, Node * root)
{//����� ������ � ���������� ������� � ��������
	if (!root) { return; }
	printTree(os, root->left);
	os << root->word << " - " << root->frequency << std::endl;
	printTree(os, root->right);
}


TreeDictionary::TreeDictionary()
{
	root = nullptr;
	size = 0;
}

TreeDictionary::TreeDictionary(const TreeDictionary & copy)
{
	copyTree(root, copy.root);
	size = copy.size;
}

TreeDictionary::TreeDictionary(TreeDictionary && move)
{
	size = move.size;
	std::swap(root, move.root);
}


TreeDictionary::~TreeDictionary()
{
	size = 0;
	deleteTree(root);
}

TreeDictionary & TreeDictionary::operator=(const TreeDictionary & copy)
{//�������� ������������ 
	if (this == &copy) {
		return *this;
	}
	deleteTree(root);
	root = nullptr;
	size = copy.size;
	copyTree(root, copy.root);
}

TreeDictionary & TreeDictionary::operator=(TreeDictionary && move)
{//�������� �����������
	size = move.size;
	std::swap(root, move.root);
	move.deleteTree(move.root);
	return *this;
}

unsigned int TreeDictionary::findWord(std::string word)
{//����� �����
	return findWord(root, word);
}

void TreeDictionary::addWord(std::string word)
{//�������� �����
	size++;
	addWord(root, word);
}

void TreeDictionary::deleteWord(std::string word)
{
	size--;
	deleteWord(root, word);
}

unsigned int TreeDictionary::countWords()
{
	return size;
}

std::ostream& operator<< (std::ostream& os, TreeDictionary& obj)
{
	obj.printTree(os, obj.root);
	return os;
}
