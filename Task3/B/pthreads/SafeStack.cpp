//Task 3B pThreads Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "SafeStack.hpp"


SafeStack::SafeStack() {
	sem_init(&semLock, 0, 1);
}

SafeStack::~SafeStack() {

}

void SafeStack::push(int data) {
	sem_wait(&semLock);
		dataStack.push(data);
	sem_post(&semLock);
}

int SafeStack::pop() {
	int data = -1;	//For debugging, not acceptable in production

	sem_wait(&semLock);
		if(!dataStack.empty()) {
			data = dataStack.top();
			dataStack.pop();
		}
	sem_post(&semLock);

	return data;
}

int SafeStack::top() {
	sem_wait(&semLock);
		if(!dataStack.empty()){
			return dataStack.top();
		}
	sem_post(&semLock);

	int data = -1; //For debugging, not acceptable in production
	return data;
}

bool SafeStack::empty() {
	bool temp = true;

	sem_wait(&semLock);
		temp = dataStack.empty();
	sem_post(&semLock);

	return temp;
}

int SafeStack::size() {
	int temp = -1;

	sem_wait(&semLock);
		temp = dataStack.size();
	sem_post(&semLock);

	return temp;
}