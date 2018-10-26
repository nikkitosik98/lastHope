#include "stdafx.h"
#include "RingBuffer.h"


RingBuffer::RingBuffer(int size) {
	flag = true;
	arr = new double[size];
	this->size = size;
	firstPointer = 0;
	lastPointer = 0;

}
RingBuffer::RingBuffer(const RingBuffer &copy) {
	flag = copy.flag;
	this->size = copy.size;
	firstPointer = copy.firstPointer;
    lastPointer = copy.lastPointer;
	arr = new double[copy.size];
	for (int i = 0; i < size; i++) {
		arr[i] = copy.arr[i];
	}
}
void RingBuffer::addElement(double element) {
	if ((lastPointer + 1) % size == firstPointer) {
		throw SizeException();
	}
	if (flag) {
		arr[lastPointer] = element;
		flag = false;

	}
	else {
		lastPointer++;
		lastPointer = lastPointer%size;
		arr[lastPointer] = element;
	}
}
double RingBuffer::getElem() {
	if (flag) {
		throw EmptyException();
	}
	double res;
	if (firstPointer == lastPointer) {
		flag = true;
		res = arr[firstPointer];
	} else {
		res = arr[firstPointer];		
		firstPointer++;
		firstPointer = firstPointer%size;
	}
	return res;
}
double RingBuffer::seeElem() {
	if (flag) {
		throw EmptyException();
	}
	return arr[firstPointer];
}
int RingBuffer::getSize() {
	return size;
}
void RingBuffer::doEmptyQueue() {
	firstPointer = lastPointer;
	flag = true;

}

bool RingBuffer::checkEmpty() {
	return flag;
}
