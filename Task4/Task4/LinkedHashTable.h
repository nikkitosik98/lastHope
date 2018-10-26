
#pragma once

struct NoElemException{};

struct Element // кирпич
{
	int data;
	int key;
	Element* next;
	Element(int data, int key, Element* next = nullptr);
};

class HashList {
private:
	Element* first;
	Element* last;
public:
	friend class Iterator;
	HashList();
	~HashList();
	void addElem(int elem, int key);
	void delElem(int elem);
	void doEmpty();
};

class LinkedHashTable
{
private:
	Element** hashTable;
	HashList* list;
	int size;
	int countElem;
public:
	friend class Iterator;
	LinkedHashTable();
	LinkedHashTable(int size);
	void addElem(int elem, int key);
	void removeElem(int key);
	int findElem(int key);
	void doEmpty();
	bool isEmpty();
	void printElem();
	~LinkedHashTable();
};


class Iterator {
private:
	Element* now;
	LinkedHashTable* hashList;
	
public:
	Iterator(LinkedHashTable* &hashTable);
	~Iterator();
	bool hasNext();
	void start();
	void next();
	int seeElem();
};

