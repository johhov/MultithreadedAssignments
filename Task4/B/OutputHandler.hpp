//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <stdio.h>

#include "SafeQueue.hpp"

class OutputHandler {
public:
	OutputHandler(bool* running, SafeQueue* outputQueue);
	~OutputHandler();

	void run();
private:
	bool* running;
	SafeQueue* outputQueue;
};