//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <iostream>
#include <thread>

#include "Barrier.hpp"

class OutputHandler {
public:
	OutputHandler(	bool* running,
					std::string* callbackString,
					int* callbackStringLength,
					Barrier* newLength,
					Barrier* finishedOutput);
	~OutputHandler();

	void run();
private:
	//External
	bool* running;
	Barrier* newLength;
	Barrier* finishedOutput;

	std::string* callbackString;
	int* callbackStringLength;

	//Internal
};