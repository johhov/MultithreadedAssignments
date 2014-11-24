//Task 3B pThreads Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "SafeStack.hpp"


SafeStack::SafeStack() {
	sem_init(&semLock, 0, 1);
	delay.tv_sec = 0;
	delay.tv_nsec = 100;
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

	sem_timedwait(&semLock, &delay);
		if(!dataStack.empty()) {
			data = dataStack.top();
			dataStack.pop();
			printf("Pop\n");
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
	sem_wait(&semLock);
		return dataStack.empty();
	sem_post(&semLock);
}

int SafeStack::size() {
	sem_wait(&semLock);
		return dataStack.size();
	sem_post(&semLock);
}

void SafeStack::clearLock() {
	sem_post(&semLock);
}