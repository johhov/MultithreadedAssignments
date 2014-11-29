//Task 4A Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <stdio.h>
#include <assert.h>
#include <thread>
#include <atomic>

#include "SafeQueue.hpp"

const int THREADS = 10;
const int ITEMS = 10;

std::atomic<int> waitForProduction(THREADS);
std::atomic<bool> waitForAssert(true);

struct ThreadData {
	int threadNumber;
	SafeQueue* safeQueue;
};

void pushStack(ThreadData* threadData) {
	// Push ITEMS ints to the queue. The ints are sequensial starting at threadNumber * ITEMS.
	for (int i = threadData->threadNumber * ITEMS; i < ((threadData->threadNumber * ITEMS) + ITEMS); i++) {
		threadData->safeQueue->push(i);
	}
}

void popStack(ThreadData* threadData) {
	int temp;

	while(!threadData->safeQueue->empty()) {
		temp = threadData->safeQueue->pop();

		if (temp == -1) {
			printf("ERROR! Return value was: ");
		}
		
		printf("%d\n", temp);
	}
}

void *processData(ThreadData* threadData) {
	pushStack(threadData);

	waitForProduction--;
	while(waitForAssert) {
		std::this_thread::yield();
	}

	popStack(threadData);
}

int main (int argc, char* argv[]) {
	SafeQueue safeQueue;
	
	std::thread threadPool[THREADS];
	ThreadData threadData[THREADS];

	for (int i = 0; i < THREADS; i++) {
		threadData[i].threadNumber = i;
		threadData[i].safeQueue = &safeQueue;
		threadPool[i] = std::thread(processData, &threadData[i]);
	}
	
	while(waitForProduction) {
		std::this_thread::yield();
	}

	assert(safeQueue.size() == (THREADS*ITEMS));
	printf("Finished pushing %d items.\n", THREADS*ITEMS);

	waitForAssert = false;

	for (auto& thread : threadPool) {
		thread.join();
	}

	assert(safeQueue.empty());
	printf("Finished popping.\n");

	return 0;
}