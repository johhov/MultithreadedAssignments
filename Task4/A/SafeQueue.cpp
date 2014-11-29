//Task 4A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include "SafeQueue.hpp"


SafeQueue::SafeQueue() {

}

SafeQueue::~SafeQueue() {

}

void SafeQueue::push(int data) {
	std::lock_guard<std::mutex> wLock(writeLock);
	std::lock_guard<std::mutex> rLock(readLock);

	dataQueue.push(data);
}

int SafeQueue::pop() {
	std::lock_guard<std::mutex> rlock(readLock);

	int data = -1;	//For debugging, not acceptable in production

	if(!dataQueue.empty()) {
		data = dataQueue.front();
		dataQueue.pop();
	}

	return data;
}

int SafeQueue::front() {
	std::lock_guard<std::mutex> rlock(readLock);

	int data = -1;	//For debugging, not acceptable in production

	if(!dataQueue.empty()){
		data =  dataQueue.front();
	}
	
	return data;
}

int SafeQueue::back() {
	std::lock_guard<std::mutex> rlock(readLock);

	int data = -1;	//For debugging, not acceptable in production

	if(!dataQueue.empty()){
		data =  dataQueue.back();
	}
	
	return data;
}

bool SafeQueue::empty() {
	std::lock_guard<std::mutex> wLock(writeLock);
	std::lock_guard<std::mutex> rLock(readLock);

	return dataQueue.empty();
}

int SafeQueue::size() {
	std::lock_guard<std::mutex> wLock(writeLock);
	std::lock_guard<std::mutex> rLock(readLock);

	return dataQueue.size();
}