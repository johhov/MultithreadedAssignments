//Task 3B pThreads Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <pthread.h>
#include <stdio.h>
#include <assert.h>
#include <unistd.h>

#include "SafeStack.hpp"

const int THREADS = 10;
const int ITEMS = 10;

struct ThreadData {
	int threadNumber;
	SafeStack* safeStack;
	pthread_barrier_t* syncPush;
	pthread_barrier_t* syncPop;
};

void wait(int ms) {
	usleep(ms);
}

void pushStack(ThreadData* threadData) {
	// Push ITEMS ints to the stack. The ints are sequensial starting at threadNumber * ITEMS.
	for (int i = threadData->threadNumber * ITEMS; i < ((threadData->threadNumber * ITEMS) + ITEMS); i++) {
		threadData->safeStack->push(i);
	}
}

void popStack(ThreadData* threadData) {
	int temp;

	while(!threadData->safeStack->empty()) {
		temp = threadData->safeStack->pop();

		if (temp == -1) {
			printf("ERROR!\n");
		} else {
			printf("%d\n", temp);
		}
	}
}

void *processData(void* data) {
	ThreadData* threadData = (struct ThreadData*)data;
	
	pushStack(threadData);
	pthread_barrier_wait(threadData->syncPush);

	// Waiting for main to assert

	pthread_barrier_wait(threadData->syncPop);
	popStack(threadData);
	
	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	SafeStack safeStack;
	
	pthread_t threadPool[THREADS];
	ThreadData threadData[THREADS];
	
	pthread_barrier_t syncPush;
	pthread_barrier_t syncPop;
	pthread_barrier_init(&syncPush, NULL, THREADS+1);
	pthread_barrier_init(&syncPop, NULL, THREADS+1);

	for (int i = 0; i < THREADS; i++) {
		threadData[i].threadNumber = i;
		threadData[i].safeStack = &safeStack;
		threadData[i].syncPush = &syncPush;
		threadData[i].syncPop = &syncPop;
		pthread_create(&threadPool[i], NULL, &processData, (void*)&threadData[i]);
	}
	
	pthread_barrier_wait(&syncPush);
	assert(safeStack.size() == (THREADS*ITEMS));
	printf("Finished pushing %d items.\n", THREADS*ITEMS);
	pthread_barrier_wait(&syncPop);

	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadPool[i], NULL);
	}

	assert(safeStack.empty());

	return 0;
}