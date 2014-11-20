#pragma once

#include <pthread.h>
#include <omp.h>

class Stack{
public:
	Stack();
	void push(Data data);
	int pop();
	bool empty();

	struct Data {
		int x;
		int y;
	};

private:
	std::stack<Data> data;

};