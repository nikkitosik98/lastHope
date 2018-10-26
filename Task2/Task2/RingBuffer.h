#pragma once
#include "stdafx.h"

struct SizeException {};
struct EmptyException {};
class RingBuffer {
private:
	double *arr;
	int size;
	int firstPointer;
	int lastPointer;
	bool flag;
public:
	friend class Iterator;
	RingBuffer(int size);
	RingBuffer(const RingBuffer &copy);
	void addElement(double element);
	double getElem();
	double seeElem();
	void doEmptyQueue();
	int getSize();
	bool checkEmpty();
};

