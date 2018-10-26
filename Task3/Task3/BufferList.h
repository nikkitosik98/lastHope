#pragma once
#include "List.h"
class BufferList : public List
{
private:
	Node* head;
	int size;

public:
	friend class ListIterator;
	class ListIterator : public Iterator {
	private:
		BufferList *list;
		Node * nowPointer;
	public:
		ListIterator(BufferList *list);
		void start();
		TElem getElement() const;
		void next();
		void prev();
		bool finish() const;
		Node* getNow() const;
	};

        void addElem(const TElem &elem, Iterator &iter);
	void deleteElem(Iterator &iter);
	void makeEmpty();
	bool isEmpty() const;
	int getSize() const;
	Iterator* findElem(const TElem &elem);
	Iterator* getIterator();
	BufferList();
	BufferList(const BufferList& copy);
	BufferList(BufferList&& copy);
	BufferList& operator= (const BufferList &copy);
	BufferList& operator=(BufferList&& copy);
	~BufferList();
};

