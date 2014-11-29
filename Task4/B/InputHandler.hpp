//Task 4B Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <stdio.h>

#include "SafeQueue.hpp"

class InputHandler {
public:
	InputHandler(bool* running, SafeQueue* inputQueue);
	~InputHandler();

	void run();
private:
	bool* running;
	SafeQueue* inputQueue;
};