#include "stdafx.h"
#include "Iterator.h"

Iterator::Iterator(RingBuffer* &que) {
	this->index = que->firstPointer;
	this->queue = que;
}
void Iterator::start() {
	index = queue->firstPointer;

}
void Iterator::next() {
	index++;
	index = index%queue->size;
}

bool Iterator::finish() {
	if (queue->lastPointer != index && !queue->checkEmpty()) {
		return false;
	} return true;
}
int Iterator::getValue() {
	return queue->arr[index];
}
