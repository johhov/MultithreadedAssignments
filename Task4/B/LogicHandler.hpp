//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <omp.h>

#include "SafeQueue.hpp"

class LogicHandler {
public:
	LogicHandler(bool* running, SafeQueue* inputQueue, SafeQueue* outputQueue);
	~LogicHandler();

	void run();
private:
	bool* running;
	SafeQueue* inputQueue;
	SafeQueue* outputQueue;	
};