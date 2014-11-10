//Task 2A Multithreaded Programming 2014
//Johannes Hovland - 101028

#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int ITERATIONS = 10000000;
const int THREADS = 4;
int partialResults[THREADS];

void *monteCarloPICalculation(void *thrNum){
	double x, y;
	int threadNumber = (intptr_t)thrNum;

	for (int i = 0; i < ITERATIONS/THREADS; i++) {
		x = (double)rand() / (double)RAND_MAX; // Random number between 0 and 1
		y = (double)rand() / (double)RAND_MAX;
		
		if (((x*x) + (y*y)) <= 1.0) {
			partialResults[threadNumber]++;
		}
	}
	pthread_exit(NULL);	
}

int main (int argc, char* argv[]) {
	pthread_t threadPool[THREADS];

	auto startTime = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < THREADS; i++) {
		pthread_create(&threadPool[i], NULL, &monteCarloPICalculation, (void*)(intptr_t)i);
	}

	for (int i = 0; i < THREADS; i++) {
		pthread_join(threadPool[i], NULL);
	}

	int in = 0;
	for (int i = 0; i < THREADS; i++) {
		in += partialResults[i];
	}

	double pi = (4.0*in)/ITERATIONS;

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = endTime-startTime;
	auto msDuration = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	printf("Monte Carlo aproximation of PI given %d calculations is: %f.\n", ITERATIONS, pi);
	printf("The calculations took %lu milliseconds using %d pThreads.\n", msDuration, THREADS);

	return 0;
}