#include "stdafx.h"
#include "LinkedHashTable.h"
#include "iostream"

using namespace std;
Element::Element(int data,int key, Element * next)
{
	this->data = data;
	this->next = next;
	this->key = key;
}

LinkedHashTable::LinkedHashTable()
{
	countElem = 0;
	size = 5;
	hashTable = new Element*[5];
	list = new HashList();
	for (int i = 0; i < size; i++) {
		hashTable[i] = nullptr;
	}
}

LinkedHashTable::LinkedHashTable(int size)
{
	countElem = 0;
	this->size = size;
	hashTable = new Element*[size];
	list = new HashList();
	for (int i = 0; i < size; i++) {
		hashTable[i] = nullptr;
	}
}

void LinkedHashTable::addElem(int elem, int key)
{
	int position = key%size;
	if (!hashTable[position]) {
		hashTable[position] = new Element(elem, key);
	}
	else {
		Element* temp = hashTable[position];
		while (temp->next) {
			temp = temp->next;
		}
		temp->next = new Element(elem, key);
	}
	list->addElem(elem, key);
	countElem++;
}

void LinkedHashTable::removeElem(int key)
{
	int position = key%size;
	Element* temp = hashTable[position];
	Element *buf = temp;
	while (temp) {
		if (key == temp->key) {
			if (buf == temp) {
				hashTable[position] = temp->next;
			}
			else {
				buf->next = temp->next;
			}
			list->delElem(temp->data);
			delete temp;
			countElem--;
			return;
		}
		buf = temp;
		temp = temp->next;
	}
}

int LinkedHashTable::findElem(int key)
{
	int position = key%size;
	Element* temp = hashTable[position];
	while (temp) {
		if (key == temp->key) {
			return temp->data;
		}
		temp = temp->next;
	}
	throw NoElemException();
}

void LinkedHashTable::doEmpty()
{
	for (int i = 0; i < size; i++) {
		Element *temp = hashTable[i];
		Element *buf;
		while (temp) {
			buf = temp->next;
			delete temp;
			temp = buf;
		}
		hashTable[i] = nullptr;
	}
	countElem = 0;
	list->doEmpty();
}

bool LinkedHashTable::isEmpty()
{
	if (countElem > 0) { return false; }
	return true;
}

void LinkedHashTable::printElem()
{
	for (int i = 0; i < size; i++) {
		Element* temp = hashTable[i];
		cout << i << ": ";
		while (temp) {
			cout<<" " << temp->data<<" ";
			temp = temp->next;
		}
		cout << endl;
	}
}


LinkedHashTable::~LinkedHashTable()
{
	doEmpty();
	delete[] hashTable;
	delete list;
}

HashList::HashList()
{
	first = nullptr;
	last = nullptr;
}

HashList::~HashList()
{
	Element* temp = first;
	while (temp != last) {
		temp = temp->next;
		delete first;
		first = temp;
	}
	delete first;
}

void HashList::addElem(int elem, int key)
{
	if (!last) {
		last = new Element(elem, key);
		first = last;
	}
	else {
		last->next = new Element(elem, key);
		last = last->next;
	}
}

void HashList::delElem(int elem)
{
	Element* temp = first->next;
	Element* buf = first;
	if (first->data == elem) {
		delete first;
		first = temp;
		return;
	}
	while (temp->data != elem) {
		buf = temp;
		temp = temp->next;
	}
		buf->next = temp->next;
		delete temp;
	
}

void HashList::doEmpty()
{
	Element* temp = first;
	while (temp != last) {
		temp = temp->next;
		delete first;
		first = temp;
	}
	delete first;
}

Iterator::Iterator(LinkedHashTable* & hashTable)
{
	hashList = hashTable;
	now = hashList->list->first;
}

Iterator::~Iterator()
{
}

bool Iterator::hasNext()
{
	if (now != hashList->list->last) { return true; }
	return false;
}

void Iterator::start()
{
	now = hashList->list->first;
}

void Iterator::next()
{
	now = now->next;
}

int Iterator::seeElem()
{
	return now->data;
}

