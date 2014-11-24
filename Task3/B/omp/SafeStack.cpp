//Task 3B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "SafeStack.hpp"

SafeStack::SafeStack() {

}

void SafeStack::push(int data) {
	//#pragma omp critical
	//{
		dataStack.push(data);
	//}
}

int SafeStack::pop() {
	int data = -1;	//For debugging, not acceptable in production

	#pragma omp critical
	{
		if(!dataStack.empty()){
			data = dataStack.top();
			dataStack.pop();
		}
	}

	return data;
}

int SafeStack::top() {
	int data = -1; //For debugging, not acceptable in production
	
	#pragma omp critical
	{
		if(!dataStack.empty()){
			data = dataStack.top();
		}
	}

	return data;
}

bool SafeStack::empty() {
	bool empty;

	#pragma omp critical
	{
		empty = dataStack.empty();
	}

	return empty;
}

int SafeStack::size() {
	int size;

	#pragma omp critical
	{
		size = dataStack.size();
	}
	return size;
}
