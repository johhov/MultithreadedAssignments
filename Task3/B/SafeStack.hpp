//Task 3B Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <stack>
#include <omp.h>

class SafeStack{
public:
	SafeStack();
	void push(int data);
	int pop();
	int top();
	bool empty();
	int size();

private:
	std::stack<int> dataStack;
};