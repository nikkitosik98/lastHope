#include "stdafx.h"
#include "BufferList.h"


BufferList::BufferList()
{
	size = 0;
	head = new Node(0);
	head->next = head;
	head->prev = head;
}

BufferList::BufferList(const BufferList & copy)
{
	size = copy.size;
	head = new Node(0);
	head->next = head;
	head->prev = head;
	Node* countCopy = copy.head->next;
	Node* temp = head;
	for (int i = 1; i < size; i++) {
		temp->next = new Node(countCopy->data);
		temp->next->prev = temp;
		temp = temp->next;
		countCopy = countCopy->next;
	}
	temp->next = head;
	head->prev = temp;
}

BufferList::BufferList(BufferList && copy)
{
	size = copy.size;
	std::swap(head, copy.head);
}
// оператор присваивания
BufferList & BufferList::operator=(const BufferList & copy)
{
	if (this == &copy) {
		return *this;
	}
	makeEmpty();
	Node* countCopy = copy.head->next;
	Node* temp = head;
	size = copy.size;
	for (int i = 1; i < size; i++) {
		temp->next = new Node(countCopy->data);
		temp->next->prev = temp;
		temp = temp->next;
		countCopy = countCopy->next;
	}
	temp->next = head;
	head->prev = temp;
		return *this;
}
 // оператор перемещения
BufferList & BufferList::operator=(BufferList && copy)
{
	makeEmpty();
	size = copy.size;
	std::swap(head, copy.head);
	delete copy.head;
	return *this;
}


BufferList::~BufferList()
{
	makeEmpty();
	delete head; 
}
// конструктор итератора
BufferList::ListIterator::ListIterator(BufferList * list)
{
	this->list = list;
	this->nowPointer = list->head;
}
// начать работу итератора
void BufferList::ListIterator::start()
{
	nowPointer = list->head;
}
// смотреть итер
TElem BufferList::ListIterator::getElement() const
{
	if (nowPointer == list->head) {
		throw BufferException();
	}
	return nowPointer->data;
}
// переход на след элемент
void BufferList::ListIterator::next()
{
	nowPointer = nowPointer->next;
}
//на пред
void BufferList::ListIterator::prev()
{
	nowPointer = nowPointer->prev;
}
// всё ли проитерировано
bool BufferList::ListIterator::finish() const
{
	if (nowPointer->next == list->head) {
		return true;
	}
	return false;
}
// получить текущий указатель
Node * BufferList::ListIterator::getNow() const
{
	return  nowPointer;
}

// добавить
void BufferList::addElem(const TElem & elem, Iterator & iter)
{
	size++;
	Node *tempNode = new Node(elem, iter.getNow()->next, iter.getNow());
	iter.getNow()->next->prev = tempNode;
	iter.getNow()->next = tempNode;
}
// удалить
void BufferList::deleteElem(Iterator & iter)
{
	if (iter.getNow() == head) {
		throw BufferException();
	}
	Node* delElem = iter.getNow();
	iter.next();
	delElem->next->prev = delElem->prev;
	delElem->prev->next = delElem->next;
	delete delElem;
	size--;
}
// сделать пустым
void BufferList::makeEmpty()
{
	head = head->next;
	for (int i = 0; i < size; i++) {
		head = head->next;
		delete head->prev;
	}
	head->next = head;
	head->prev = head;
	size = 0;
}
// проверка на пустоту
bool BufferList::isEmpty() const
{
	if (size == 0) {
		return true;
	}
	return false;
}

int BufferList::getSize() const
{

	return size;
}
// получить итер на требуемый элемент
Iterator * BufferList::findElem(const TElem & elem)
{
	ListIterator* listIterator = new ListIterator(this);
	listIterator->next();
	while (listIterator->getElement() != elem && !listIterator->finish()) {
		
		listIterator->next();
	}
	if (listIterator->getElement() != elem) {
		throw NoElemException();
	}
	return listIterator;
}
// итер на первый элемент
Iterator * BufferList::getIterator()
{
	return new ListIterator(this);
}
