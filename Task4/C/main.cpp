//Task 4C Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <thread>
#include <stdlib.h>
#include <stdio.h>
#include <functional>
#include <atomic>

#include "SafeQueue.hpp"

const int THREADS = 16;
const int NUMBERS_TO_PROCESS = 255;
const int FINISHED_PRODUCING = -2;

std::atomic<int> counter(0);

void processData(SafeQueue& inputQueue) {
	while (inputQueue.front() != FINISHED_PRODUCING) {
		counter += inputQueue.pop();
	}
}

void produceData(SafeQueue* inputQueue) {
	if (inputQueue->front() == FINISHED_PRODUCING) {
		inputQueue->pop();
	}

	for (int i = 0; i < NUMBERS_TO_PROCESS; i++) {
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

	std::thread threadPool[THREADS];

	for (int i = 0; i < THREADS; i++) {
		threadPool[i] = std::thread(processData, std::ref(inputQueue));
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