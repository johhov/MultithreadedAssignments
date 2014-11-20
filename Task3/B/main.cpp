//Task 3B Multithreaded Programming 2014
//Johannes Hovland - 101028
#include <omp.h>
#include <stdio.h>
#include <assert.h>

#include "SafeStack.hpp"

const int ITEMS = 100;

int main (int argc, char* argv[]) {
	SafeStack safeStack;

	#pragma omp parallel for
	for (int i = 0; i < ITEMS; i++) {
		safeStack.push(i);
	}

	assert(safeStack.size() == ITEMS);

	#pragma omp parallel for
	for (int i = 0; i < ITEMS; i++) {
		printf("%d\n", safeStack.pop());
	}

	assert(safeStack.empty());

	return 0;
}