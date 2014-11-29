//Task 1B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

int START_PARALLEL_PERCENT = 10;
int PARALLEL_PERCENT_STEP = 20;
int MAX_PARALLEL_PERCENT = 90;

int MAX_NUMBER_OF_THREADS = 20;

void doWork() {
	usleep(50000);
}

int main (int argc, char* argv[]) {
	FILE *file = fopen("parallel.csv","w");
	
	if(file == NULL){
		printf("Error!!\n");
		return 0;
	}

	fprintf(file, "ParallelPercent;Threads;SpeedUp\n");
	
	for(int currentParallelPercent = START_PARALLEL_PERCENT; currentParallelPercent <= MAX_PARALLEL_PERCENT; currentParallelPercent += PARALLEL_PERCENT_STEP) {
		unsigned long msBaseTime;

		for(int currentNumberOfThreads = 1; currentNumberOfThreads <= MAX_NUMBER_OF_THREADS; currentNumberOfThreads++) {
			omp_set_num_threads(currentNumberOfThreads);

			auto startTime = std::chrono::high_resolution_clock::now();

			#pragma omp parallel for
			for(int i = 0; i < currentParallelPercent; i++) {
				doWork();
			}

			for(int i = 0; i < 100-currentParallelPercent; i++) {
				doWork();
			}

			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = endTime-startTime;
			unsigned long msDuration = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();

			if(currentNumberOfThreads == 1) {
				msBaseTime = msDuration;
			}

			double speedUp = (double)msBaseTime / (double)msDuration;
			
			printf("Amdahl's Law calculation with %d percent parallelisation and %d threads took %lums. It is %f times as fast as one thread.\n", currentParallelPercent, currentNumberOfThreads, msDuration, speedUp);
			fprintf(file, "%d;%d;%f\n",currentParallelPercent, currentNumberOfThreads, speedUp);
		}
	}

	fclose(file);
	return 0;
}