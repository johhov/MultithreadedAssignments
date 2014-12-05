//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <thread>

#include "Barrier.hpp"

class LogicHandler {
public:
	LogicHandler(	bool* running,
					std::string* callbackString,
					int* callbackStringLength,
					Barrier* newInput,
					Barrier* newLength);
	~LogicHandler();

	void run();
private:
	//External
	bool* running;
	Barrier* newInput;
	Barrier* newLength;

	std::string* callbackString;
	int* callbackStringLength;

	//Internal
};