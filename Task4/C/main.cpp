//Task 4C Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <stdlib.h>
#include <stdio.h>
#include <thread>
#include <atomic>

#include "SafeQueue.hpp"

const int THREADS = 16;
const int NUMBERS_TO_PROCESS = 255;
const int FINISHED_PRODUCING = -2;

struct ThreadData {
	int threadNumber;
	SafeQueue* inputQueue;
	std::mutex* lock;
	std::atomic<int>* counter;
};

void processData(ThreadData* threadData) {
	while (threadData->inputQueue->front() != FINISHED_PRODUCING) {
		std::lock_guard<std::mutex> lock(*threadData->lock);

		if(threadData->inputQueue->front() != FINISHED_PRODUCING && !threadData->inputQueue->empty()) {
			*threadData->counter += threadData->inputQueue->pop();
		}
	}
}

void produceData(SafeQueue* inputQueue) {
	//If queue has been used before, clear it.
	if (inputQueue->front() == FINISHED_PRODUCING) {
		inputQueue->pop();
	}

	//Reset random generator to get the same data on the queue
	srand(1);

	for (int i = 0; i <= NUMBERS_TO_PROCESS; i++) {
		inputQueue->push(rand() % 1000);
	}

	inputQueue->push(FINISHED_PRODUCING);
}

void waitForConsumers(SafeQueue* inputQueue) {
	while(inputQueue->front() != FINISHED_PRODUCING) {
		std::this_thread::yield();
	}
}

int main (int argc, char* argv[]) {
	SafeQueue inputQueue;
	std::mutex lock;
	std::atomic<int> counter(0);

	std::thread threadPool[THREADS];
	ThreadData threadData[THREADS];

	for (int i = 0; i < THREADS; i++) {
		threadData[i].threadNumber = i;
		threadData[i].inputQueue = &inputQueue;
		threadData[i].lock = &lock;
		threadData[i].counter = &counter;
		threadPool[i] = std::thread(processData, &threadData[i]);
	}

	produceData(&inputQueue);
	waitForConsumers(&inputQueue);
	printf("%d\n", (int)counter);
	
	for (auto& thread : threadPool) {
		thread.join();
	}

	produceData(&inputQueue);
	counter = 0;
	
	while (inputQueue.front() != FINISHED_PRODUCING) {
		counter += inputQueue.pop();
	}

	printf("%d\n", (int)counter);
	
	return 0;
}