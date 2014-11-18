//Task 2B Multithreaded Programming 2014
//Johannes Hovland - 101028

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <semaphore.h>

const int THREADS = 3;

struct sharedThreadData {
	bool running;
	bool newInput;
	bool newResult;

	int input;
	int result;

	sem_t inputSem;
	sem_t resultSem;
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

				sem_wait(&sharedData->inputSem);
				sharedData->input = intInput;
				sharedData->newInput = true;					
				sem_post(&sharedData->inputSem);
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
			sem_wait(&sharedData->inputSem);
			localInput = sharedData->input;
			sharedData->newInput = false;
			sem_post(&sharedData->inputSem);

			localResult = localInput * 3;
			printf("logicThread turning %d into %d\n",  localInput, localResult);

			sem_wait(&sharedData->resultSem);
			sharedData->result = localResult;
			sharedData->newResult = true;
			sem_post(&sharedData->resultSem);
		}
	}

	pthread_exit(NULL);
}

void *outputThread(void *data) {
	sharedThreadData *sharedData = (struct sharedThreadData*)data;
	int localResult;

	while(sharedData->running) {
		if(sharedData->newResult) {
			sem_wait(&sharedData->resultSem);
			localResult = sharedData->result;
			sharedData->newResult = false;
			sem_post(&sharedData->resultSem);

			printf("outputThread printing: %d\n", sharedData->result);
		}
	}

	pthread_exit(NULL);
}

int main (int argc, char* argv[]) {
	pthread_t threadPool[THREADS];
	
	sharedThreadData data;	
		data.running = true;
		data.newInput = false;
		data.newResult = false;
		sem_init(&data.inputSem, 0, 1);
		sem_init(&data.resultSem, 0, 1);


	pthread_create(&threadPool[0], NULL, &inputThread, (void*)&data);
	pthread_create(&threadPool[1], NULL, &logicThread, (void*)&data);
	pthread_create(&threadPool[2], NULL, &outputThread, (void*)&data);
	
	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadPool[i], NULL);
	}

	return 0;
}