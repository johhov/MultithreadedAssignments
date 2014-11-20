//Task 3A Multithreaded Programming 2014
//Johannes Hovland - 101028

#pragma once

#include <pthread.h>
#include <unistd.h>
#include <omp.h>

class Singleton {
public:
	static Singleton* getInstance();

private:
	static Singleton* instance;

	Singleton();

	void doWork();
};