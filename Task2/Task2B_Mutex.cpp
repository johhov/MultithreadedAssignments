//Task 2B Multithreaded Programming 2014
//Johannes Hovland - 101028

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>

const int THREADS = 3;

struct sharedThreadData {
	bool running;
	bool newInput;
	bool newResult;

	int input;
	int result;

	pthread_mutex_t inputMutex;
	pthread_mutex_t resultMutex;
};

void *inputThread(void *data) {
	sharedThreadData *sharedData = (struct sharedThreadData*)data;
	char charInput[100];
	int intInput;

	while(sharedData->running) {
		if(!sharedData->newInput) {
			scanf(" %100s", charInput);
			intInput = atoi(charInput);

			if (charInput[0] == 'q') {
				sharedData->running = false;
			} else if (intInput != 0) {
				printf("inputThread sending %i\n", intInput);

				pthread_mutex_lock(&sharedData->inputMutex);
				sharedData->input = intInput;
				sharedData->newInput = true;					
				pthread_mutex_unlock(&sharedData->inputMutex);
			}
		}
	}

	pthread_exit(NULL);
}

void *logicThread(void *data) {
	sharedThreadData *sharedData = (struct sharedThreadData*)data;
	int localInput;
	int localResult;

	while(sharedData->running) {
		if(sharedData->newInput && !sharedData->newResult) {
			pthread_mutex_lock(&sharedData->inputMutex);
			localInput = sharedData->input;
			sharedData->newInput = false;
			pthread_mutex_unlock(&sharedData->inputMutex);

			localResult = localInput * 3;
			printf("logicThread turning %d into %d\n",  localInput, localResult);

			pthread_mutex_lock(&sharedData->resultMutex);
			sharedData->result = localResult;
			sharedData->newResult = true;
			pthread_mutex_unlock(&sharedData->resultMutex);
		}
	}

	pthread_exit(NULL);
}

void *outputThread(void *data) {
	sharedThreadData *sharedData = (struct sharedThreadData*)data;
	int localResult;

	while(sharedData->running) {
		if(sharedData->newResult) {
			pthread_mutex_lock(&sharedData->resultMutex);
			localResult = sharedData->result;
			sharedData->newResult = false;
			pthread_mutex_unlock(&sharedData->resultMutex);

			printf("outputThread printing: %d\n", sharedData->result);
		}
	}

	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	pthread_t threadPool[THREADS];
	
	sharedThreadData data;	
		data.running = true;
		data.inputMutex = PTHREAD_MUTEX_INITIALIZER;
		data.resultMutex = PTHREAD_MUTEX_INITIALIZER;
		data.newInput = false;
		data.newResult = false;

	pthread_create(&threadPool[0], NULL, &inputThread, (void*)&data);
	pthread_create(&threadPool[1], NULL, &logicThread, (void*)&data);
	pthread_create(&threadPool[2], NULL, &outputThread, (void*)&data);
	
	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadPool[i], NULL);
	}

	return 0;
}