//Task 1B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <ctime>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>

void doWork(){
	usleep(50000);
}

int main (int argc, char* argv[]) {
	FILE *file = fopen("parallel.csv","w");
	
	if(file == NULL){
		printf("Error!!\n");
		return 0;
	}

	fprintf(file, "ParallelPercent;Threads;TimeInMs\n");
	
	for(int i = 10; i<100; i +=20){
		for(int j = 1; j <= 20; j++){
			omp_set_num_threads(j);

			auto startTime = std::chrono::high_resolution_clock::now();

			#pragma omp parallel for
			for(int k = 0; k < i; k++) {
				doWork();
			}

			for(int l = 0; l < 100-i; l++) {
				doWork();
			}

			auto endTime = std::chrono::high_resolution_clock::now();
			auto duration = endTime-startTime;
			auto msDuration = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
			
			printf("Amdahl's Law calculation with %d percent parallelisation and %d threads took %lums\n", i, j, msDuration);
			fprintf(file, "%d;%d;%lu\n",i,j,msDuration);
		}
	}

	fclose(file);
	return 0;
}