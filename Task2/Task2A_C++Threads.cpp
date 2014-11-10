//Task 2A Multithreaded Programming 2014
//Johannes Hovland - 101028

//NOT FINISHED!!!!!
//NOT FINISHED!!!!!
//NOT FINISHED!!!!!
//NOT FINISHED!!!!!
//NOT FINISHED!!!!!

#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const int ITERATIONS = 10000000;
const int THREADS = 4;
int partialResults[THREADS];

void monteCarloPICalculation(int threadNumber){
	double x, y;

	for (int i = 0; i < ITERATIONS/THREADS; i++) {
		x = (double)rand() / (double)RAND_MAX; // Random number between 0 and 1
		y = (double)rand() / (double)RAND_MAX;
		
		if (((x*x) + (y*y)) <= 1.0) {
			partialResults[threadNumber]++;
		}
	}
}

int main (int argc, char* argv[]) {
	//Create threads

	auto startTime = std::chrono::high_resolution_clock::now();
	
	for (int i = 0; i < THREADS; i++) {
		//Start threads
	}

	for (int i = 0; i < THREADS; i++) {
		//Join threads
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
	printf("The calculations took %lu milliseconds using %d C++ 11 threads.\n", msDuration, THREADS);

	return 0;
}