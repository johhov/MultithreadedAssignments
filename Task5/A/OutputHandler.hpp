//Task 5A Multithreaded Programming 2014
//Johannes Hovland - 101028
#pragma once

#include <string>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>

class OutputHandler {
public:
	OutputHandler(	bool* running,
					std::string* callbackString,
					int* callbackStringLength,
					std::mutex* lock,
					std::condition_variable* newLength);
	~OutputHandler();

	void run();
private:
	//External
	bool* running;
	std::mutex* lock;
	std::condition_variable* newLength;

	std::string* callbackString;
	int* callbackStringLength;

	//Internal
};