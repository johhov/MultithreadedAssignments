//Task 4C Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <queue>
#include <mutex>

class SafeQueue {
public:
	SafeQueue();
	~SafeQueue();
	void push(int data);
	int pop();
	int front();
	int back();
	bool empty();
	int size();

private:
	std::queue<int> dataQueue;
	std::mutex readLock;
	std::mutex writeLock;
};