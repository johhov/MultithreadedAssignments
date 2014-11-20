//Task 3A Multithreaded Programming 2014
//Johannes Hovland - 101028

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "singleton.hpp"

const int THREADS = 4;

struct ThreadData {
	int threadNumber;
};

void *callSingleton(void *data) {
	ThreadData* threadData = (struct ThreadData*)data;

	Singleton* singleton = Singleton::getInstance();

	printf("%d = %p\n", threadData->threadNumber, singleton);

	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	pthread_t threadPool[THREADS];
	ThreadData threadData[THREADS];

	for (int i = 0; i < THREADS; i++) {
		threadData[i].threadNumber = i;
		pthread_create(&threadPool[i], NULL, &callSingleton, (void*)&threadData[i]);
	}

	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadPool[i], NULL);
	}

	return 0;
}