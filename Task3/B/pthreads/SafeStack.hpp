//Task 3B pThreads Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <stack>
#include <semaphore.h>
#include <stdio.h>

class SafeStack {
public:
	SafeStack();
	~SafeStack();
	void push(int data);
	int pop();
	int top();
	bool empty();
	int size();

private:
	std::stack<int> dataStack;
	sem_t semLock;
};