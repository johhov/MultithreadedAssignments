//Task 5B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <iostream>
#include <pthread.h>
#include <semaphore.h>

#include "Callbacks.hpp"

const int THREADS = 3;

struct ThreadData {
	bool* running;
	std::string* callbackString;
	int* callbackStringLength;
	sem_t* newInput;
	sem_t* newLength;
	sem_t* finishedOutput;
};

//INPUT HANDLER------------------------------------------------------------------------
bool checkForInputError(char charInput) {
	if(charInput != ' ' && charInput != 'q' && (charInput < '0' || charInput > '5')) {
		printf("ERROR! Invalid input.\n");
		printf("ERROR! Exiting program.\n");
		printf("ERROR! Only the numbers 1->5  the letter 'q' and <space> is valid.\n");
		return true;
	}

	return false;
}

bool runCallback(int intInput, ThreadData* threadData, Callbacks* callbacks) {
	auto getString = callbacks->getCallbacks(intInput);

	if(getString == nullptr) {
		printf("ERROR! getCallbacks returned nullptr.\n");
		printf("ERROR! Exiting program.\n");
		return false;
	}

	*threadData->callbackString = (callbacks->*getString)();
	return true;
}

void *inputHandler(void* data) {
	ThreadData* threadData = (struct ThreadData*)data;
	Callbacks callbacks;
	char charInput;
	int intInput;

	while (*threadData->running) {
		charInput = getchar();

		//Consumes remainig chars and \n
		while (getchar() != '\n') {
		}

		if(checkForInputError(charInput)) {
			break;
		}

		if (charInput == 'q') {
			break;
		}

		if (charInput == ' ') {
			for(int i = 1; i <= 5; i ++) {	//Run for all valid numeric input, 1->5
				sem_wait(threadData->finishedOutput);
				if(!runCallback(i, threadData, &callbacks)){
					break;
				}
				sem_post(threadData->newInput);
			}
			
		}

		if(charInput !=  ' ') {
			intInput = charInput - '0';
			sem_wait(threadData->finishedOutput);
			if(!runCallback(intInput, threadData, &callbacks)){
				break;
			}		
			callbacks.changeOrder();
			sem_post(threadData->newInput);
		}
	}

	*threadData->running = false;
	sem_post(threadData->newInput);
	pthread_exit(NULL);
}

//LOGIC HANDLER-------------------------------------------------------------------------
void *logicHandler(void* data) {
	ThreadData* threadData = (struct ThreadData*)data;
	
	while(*threadData->running) {
		sem_wait(threadData->newInput);
		if(!(*threadData->running)) {
			break;
		}

		*threadData->callbackStringLength = threadData->callbackString->length();
		sem_post(threadData->newLength);
	}

	sem_post(threadData->newLength);
	pthread_exit(NULL);
}

//OUTPUT HANDLER------------------------------------------------------------------------
void *outputHandler(void* data) {
	ThreadData* threadData = (struct ThreadData*)data;
	
	while(*threadData->running) {
		sem_wait(threadData->newLength);
		if(!(*threadData->running)) {
			break;
		}
		
		std::cout << *threadData->callbackString << ", " << *threadData->callbackStringLength << std::endl;
		sem_post(threadData->finishedOutput);
	}

	sem_post(threadData->finishedOutput);
	pthread_exit(NULL);
}
	
//MAIN----------------------------------------------------------------------------------
int main (int argc, char* argv[]) {
	//Shared data
	bool running = true;
	std::string callbackString = "";
	int callbackStringLength = 0;
	
	sem_t newInput;
	sem_t newLength;
	sem_t finishedOutput;
	sem_init(&newInput, 0, 0);
	sem_init(&newLength, 0, 0);
	sem_init(&finishedOutput, 0, 1);

	pthread_t threadPool[THREADS];
	ThreadData threadData;
		threadData.running 				= &running;
		threadData.callbackString 		= &callbackString;
		threadData.callbackStringLength = &callbackStringLength;
		threadData.newInput 			= &newInput;
		threadData.newLength 			= &newLength;
		threadData.finishedOutput 		= &finishedOutput;	

	pthread_create(&threadPool[0], NULL, &inputHandler, (void*)&threadData);
	pthread_create(&threadPool[1], NULL, &logicHandler, (void*)&threadData);
	pthread_create(&threadPool[2], NULL, &outputHandler, (void*)&threadData);

	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadPool[i], NULL);
	}

	return 0;
}