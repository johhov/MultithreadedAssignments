//Task 1A Multithreaded Programming 2014
//Johannes Hovland - 101028

#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void parallelForReduction(int iterations){
	int in = 0;
	double pi;
	auto startTime = std::chrono::high_resolution_clock::now();
    
	#pragma omp parallel for reduction(+:in)
	for (int i=0; i < iterations; i++) {
		double x = (double)rand() / (double)RAND_MAX; // Random number between 0.00 and 1.00
		double y = (double)rand() / (double)RAND_MAX;
	
		if (((x*x) + (y*y)) <= 1.0) {
			in++;
		}
	}

	pi = (4.0*in)/iterations;

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = endTime-startTime;
	auto msDuration = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	printf("Monte Carlo aproximation of PI given %d calculations is: %f.\n", iterations, pi);
	printf("The calculation took %lu milliseconds using 'parallel for reduction'.\n", msDuration);
	
}

void parallelForAtomic(int iterations){
	int in = 0;
	double pi;
	auto startTime = std::chrono::high_resolution_clock::now();
    
	#pragma omp parallel for
	for (int i=0; i < iterations; i++) {
		double x = (double)rand() / (double)RAND_MAX; // Random number between 0.00 and 1.00
		double y = (double)rand() / (double)RAND_MAX;
	
		if (((x*x) + (y*y)) <= 1.0) {
			#pragma omp atomic
			in++;
		}
	}

	pi = (4.0*in)/iterations;

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = endTime-startTime;
	auto msDuration = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	printf("Monte Carlo aproximation of PI given %d calculations is: %f.\n", iterations, pi);
	printf("The calculation took %lu milliseconds using 'parallel for' with 'atomic'.\n", msDuration);
	
}

void parallelForCritical(int iterations){
	int in = 0;
	double pi;
	auto startTime = std::chrono::high_resolution_clock::now();
    
	#pragma omp parallel for
	for (int i=0; i < iterations; i++) {
		double x = (double)rand() / (double)RAND_MAX; // Random number between 0.00 and 1.00
		double y = (double)rand() / (double)RAND_MAX;
	
		if (((x*x) + (y*y)) <= 1.0) {
			#pragma omp critical
			{
				in++;
			}
		}
	}

	pi = (4.0*in)/iterations;

	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = endTime-startTime;
	auto msDuration = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

	printf("Monte Carlo aproximation of PI given %d calculations is: %f.\n", iterations, pi);
	printf("The calculation took %lu milliseconds using 'parallel for' with 'critical'.\n", msDuration);
	
}

int main (int argc, char* argv[]) {
	int forLoopIterations = 10000000;
   
    parallelForReduction(forLoopIterations);
    parallelForAtomic(forLoopIterations);
    parallelForCritical(forLoopIterations);

	return 0;
}